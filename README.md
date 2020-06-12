# ⏳ cprogbar

Yet Another simple progress indicator in C.

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

## TODO

- some tests would be nice :eyes:
