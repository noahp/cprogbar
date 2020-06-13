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
`CFLAGS='-DCPROGBAR_ENABLE_BAR=0'` when compiling. This saves about 108 bytes
when targeting Cortex-M4:

```bash
# Bar enabled
❯ CC=arm-none-eabi-gcc CFLAGS='-mcpu=cortex-m4 -Os' make clean cross-build
   text    data     bss     dec     hex filename
    296       0       0     296     128 cprogbar-cross.o
    296       0       0     296     128 (TOTALS)

# Bar disabled
❯ CC=arm-none-eabi-gcc CFLAGS='-mcpu=cortex-m4 -Os -DCPROGBAR_ENABLE_BAR=0' make clean cross-build
   text    data     bss     dec     hex filename
    188       0       0     188      bc cprogbar-cross.o
    188       0       0     188      bc (TOTALS)
```

See the example bars by running `make`.

## Design

Originally (see f526bd4bdccb70fbb6c7bdb62052bef80fd0aa92) `printf` was called
for each segment of the progress indicator; with `CPROGBAR_ENABLE_BAR=0`,
gcc-arm for cortex-m4 was 152 bytes text.

But the multiple `printf` calls is pretty costly cpu <sup>[1](#footnote1)</sup>,
so this version loads the progress indicator into a stack buffer and issues 1
`printf` call at the end, trading off .text:

|version|CPROGBAR_ENABLE_BAR=0 .text (bytes)|CPROGBAR_ENABLE_BAR=1|
|---|---|---|
|1|152|232|
|2|188 (+36)|296 (+64)|

<a name="footnote1">1</a>: I should actually measure this in qemu instead of
making outlandish claims 😔

A very simple floating-point math version of this function could be:

```c
printf("\r%3.*f%%", (int)frac_digits,
        ((float)new_offset * 100.0f) / (float)max_offset);

fflush(stdout);
```

That has nice code size properties: 82/89 bytes for Cortex-M0+/Cortex-M4. It
however is calling printf on every interation, even if the fractional part will
not change. Also I haven't measured the cpu usage when using soft float/double.

Enabling a check to only print when the fractional part changes brings the size
up to ~150 bytes.

## Testing

Helper script to run some test compilation + lint commands in Docker:

```bash
./test.sh
```

## TODO

- some tests would be nice :eyes:
