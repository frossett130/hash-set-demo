SHELL=/bin/bash -o pipefail

SRC_PATH = ./src/%.c
BLD_PATH = ./build/%.o
PRG_PATH = ./%.c
OUT_PATH = ./%
CHK_PATH = ./check/%.txt
TSS_PATH = ./test/%.c
TST_PATH = ./test/%.test
RPT_PATH = ./test/%.report.txt

SRC := $(wildcard ./src/*.c)
BLD := $(patsubst $(SRC_PATH), $(BLD_PATH), $(SRC))
LIB := $(wildcard ./lib/*.h)
PRG := $(wildcard ./*.c)
OUT := $(patsubst $(PRG_PATH), $(OUT_PATH), $(PRG))
CHK := $(wildcard ./check/*.txt)
TSS := $(patsubst $(CHK_PATH), $(TSS_PATH), $(CHK))
TST := $(patsubst $(CHK_PATH), $(TST_PATH), $(CHK))
RPT := $(patsubst $(CHK_PATH), $(RPT_PATH), $(CHK))

CFLAGS += -MMD -MP
DEP := $(BLD:.o=.d)


all: test $(OUT)

$(OUT): $(OUT_PATH): $(PRG_PATH) $(BLD)
	$(CC) $(CFLAGS) $< $(BLD) -o $@

$(BLD_PATH): $(SRC_PATH) $(LIB)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(RPT)

$(RPT_PATH): ERR_RPT = $@_FAILED.txt
$(RPT_PATH): $(TST_PATH)
	@echo "Testing $<..."
	@rm -f $(ERR_RPT)
	@./$< | tee $@ || { mv $@ $(ERR_RPT); exit 1; }

$(TST_PATH): $(TSS_PATH) $(BLD)
	$(CC) $(CFLAGS) $< $(BLD) -o $@ -lcheck

$(TSS_PATH): $(CHK_PATH)
	@command -v checkmk || { echo "checkmk is not available, please install it"; exit 1; }
	mkdir -p $(@D)
	checkmk $< > $@

clean:
	rm -rf $(OUT) build test *.d

-include $(DEP)

.PHONY: all test clean
