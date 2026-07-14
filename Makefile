SHELL=/bin/bash -o pipefail

SRC_PATH = ./src/%.c
BLD_PATH = ./build/%.o
BLT_PATH = ./test/%.o
PRG_PATH = ./%.c
OUT_PATH = ./%
CHK_PATH = ./check/%.txt
CCK_PATH = ./check/%.c
TSS_PATH = ./test/%.c
TST_PATH = ./test/%.test
RPT_PATH = ./test/%.report.txt
CHK_LIBS = $(shell pkg-config --libs check)
CHK_FLAG = $(shell pkg-config --cflags check)

SRC := $(wildcard ./src/*.c)
BLD := $(patsubst $(SRC_PATH), $(BLD_PATH), $(SRC))
CCK := $(wildcard ./check/*.c)
BLT := $(patsubst $(CCK_PATH), $(BLT_PATH), $(CCK))
PRG := $(wildcard ./*.c)
OUT := $(patsubst $(PRG_PATH), $(OUT_PATH), $(PRG))
CHK := $(wildcard ./check/*.txt)
TSS := $(patsubst $(CHK_PATH), $(TSS_PATH), $(CHK))
TST := $(patsubst $(CHK_PATH), $(TST_PATH), $(CHK))
RPT := $(patsubst $(CHK_PATH), $(RPT_PATH), $(CHK))

DEP := $(BLD:.o=.d)

all: test $(OUT)

$(OUT): $(OUT_PATH): $(PRG_PATH) $(BLD)
	$(CC) $(CFLAGS) $^ -o $@

$(BLD_PATH): CFLAGS += -DLINK_BUILD -MMD -MP
$(BLD_PATH): $(SRC_PATH)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(RPT)

$(RPT_PATH): ERR_RPT = $(@:.txt=_FAILED.txt)
$(RPT_PATH): $(TST_PATH)
	@echo "Testing $^..."
	@rm -f $(ERR_RPT)
	@./$^ | tee $@ || { mv $@ $(ERR_RPT); exit 1; }

$(TST_PATH): CFLAGS += $(CHK_FLAG)
$(TST_PATH): $(TSS_PATH) $(BLD) $(BLT)
	$(CC) $(CFLAGS) $^ -o $@ $(CHK_LIBS)

$(BLT_PATH): $(CCK_PATH)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TSS_PATH): $(CHK_PATH)
	@echo "Creating test source code $@..."
	@command -v checkmk > /dev/null || { echo "checkmk is not available, please install it"; exit 1; }
	@mkdir -p $(@D)
	@checkmk $^ > $@

clean:
	rm -rf $(OUT) build test

-include $(DEP)

.PHONY: all test clean
