[![GitHub Workflow
Status](https://img.shields.io/github/workflow/status/noahp/cprogbar/main-ci?style=for-the-badge)](https://github.com/noahp/cprogbar/actions)
[![License:
MIT](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

<!-- omit in toc -->
# ⏳ cprogbar

- [Usage](#usage)
- [Design](#design)
- [Testing](#testing)
- [TODO](#todo)

Yet Another simple progress indicator in C.

![example](./example.gif)

## Usage

```c
#include "cprogbar.h"

const size_t max_offset = 100;  //< max iteration count
const size_t fractional_digits = 2;
size_t progbar = 0;  //< cumulative progress
for (size_t i = 0; i < max_offset; i++) {
    // do something here...

    // update progress bar
    progbar = cprogpct_and_bar(progbar, i, max_offset, fractional_digits);
}
```

If you're really tight on code space, and don't need the bar output, you can set
`CFLAGS='-DCPROGBAR_ENABLE_BAR=0'` when compiling. This saves about 80 bytes
when targeting Cortex-M4:

```bash
# Bar enable
❯ CC=arm-none-eabi-gcc CFLAGS="-mcpu=cortex-m4 -Os -DCPROGBAR_ENABLE_BAR=1" make cross-build
arm-none-eabi-gcc -mcpu=cortex-m4 -Os -DCPROGBAR_ENABLE_BAR=1 -Wall -Wextra -Wpedantic -Werror -c cprogbar.c -o cprogbar-cross.o
size -t cprogbar-cross.o
   text    data     bss     dec     hex filename
    232       0       0     232      e8 cprogbar-cross.o
    232       0       0     232      e8 (TOTALS)

❯ CC=arm-none-eabi-gcc CFLAGS="-mcpu=cortex-m4 -Os -DCPROGBAR_ENABLE_BAR=0" make cross-build
arm-none-eabi-gcc -mcpu=cortex-m4 -Os -DCPROGBAR_ENABLE_BAR=0 -Wall -Wextra -Wpedantic -Werror -c cprogbar.c -o cprogbar-cross.o
size -t cprogbar-cross.o
   text    data     bss     dec     hex filename
    152       0       0     152      98 cprogbar-cross.o
    152       0       0     152      98 (TOTALS)
```

See the example bars by running `make`.

## Design

Originally (see f526bd4bdccb70fbb6c7bdb62052bef80fd0aa92) `printf` was called
for each segment of the progress indicator; with `CPROGBAR_ENABLE_BAR=0` gcc-arm
for cortex-m4 was 152 bytes text.

But the multiple `printf` calls is pretty costly cpu <sup>[1](#footnote1)</sup>,
so this version loads the progress indicator into a stack buffer and issues 1
`printf` call at the end, trading off .text:

|version|CPROGBAR_ENABLE_BAR=0 .text (bytes)|CPROGBAR_ENABLE_BAR=1|
|---|---|---|
|1|152|232|
|2|195 (+43)|319 (+87)|

<a name="footnote1">1</a>: I should actually measure this in qemu instead of
making outlandish claims 😔


## Testing

Helper script to run some test compilation + lint commands in Docker:

```bash
./test.sh
```

## TODO

- some tests would be nice :eyes:
