#!/usr/bin/env bash

# Set of test commands, normally run in Docker

set -ex

# build with gcc
CC=gcc-10 make clean example

# build with clang
CC=clang-10 make clean example

# build with gcc-arm for cortex-m4
CC=arm-none-eabi-gcc CFLAGS='-mcpu=cortex-m4 -Os' make clean cross-build

# same but with bar disabled
CC=arm-none-eabi-gcc CFLAGS='-mcpu=cortex-m4 -Os -DCPROGBAR_ENABLE_BAR=0' make clean cross-build

# same but with clang cross compiling
# NB the apt-installed arm-none-eabi-gcc returns nothing from `-print-sysroot`,
# so fall back on hard coded lib dir (which is installed as an apt package
# dependency)
ARM_NONE_EABI_SYSROOT=$(arm-none-eabi-gcc -print-sysroot)
ARM_NONE_EABI_SYSROOT=${ARM_NONE_EABI_SYSROOT:-/usr/lib/arm-none-eabi}
CC=clang-10 \
  CFLAGS="--target=arm-none-eabi -mcpu=cortex-m4 --sysroot=$ARM_NONE_EABI_SYSROOT -Oz" \
  make clean cross-build

# same but disable progress bar
CC=clang-10 \
  CFLAGS="--target=arm-none-eabi -mcpu=cortex-m4 --sysroot=$ARM_NONE_EABI_SYSROOT -Oz -DCPROGBAR_ENABLE_BAR=0" \
  make clean cross-build

# same but targeting cortex-m0+
CC=clang-10 \
  CFLAGS="--target=arm-none-eabi -mcpu=cortex-m0+ --sysroot=$ARM_NONE_EABI_SYSROOT -Oz -DCPROGBAR_ENABLE_BAR=0" \
  make clean cross-build

# same but targeting cortex-m35p what the heck
CC=clang-10 \
  CFLAGS="--target=arm-none-eabi -mcpu=cortex-m35p --sysroot=$ARM_NONE_EABI_SYSROOT -Oz -DCPROGBAR_ENABLE_BAR=0" \
  make clean cross-build

# some linting
make clean
clang-format-10 -style=file $(find . -name '*.[ch]' | awk NF=NF RS=) --dry-run -Werror
clang-tidy-10 -checks='*' cprogbar.c -- -I./
scan-build-10 --status-bugs make test
