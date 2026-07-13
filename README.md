# Hashset demo

## Overview

This little project is aimed to showcase a simple example of a hash set. It
provides a build and test lightweight framework which can be reused for other C
projects as well, enjoy!

## Requirements

* The dev tools including a C compiler
* the `checkmk` library, is usually available in the `check` package, it can be
  installed typing the following

```bash
sudo apt install check
```

## Usage

To build the executable, simply type

```bash
make
```

This will run:

* The building of the linked `.o` files.
* The building of the test files.
* The execution of the tests.
* The execution of the main executable.

To run the executable, type

```bash
./hash-set-demo hello world world
```
