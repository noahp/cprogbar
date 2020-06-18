//! Example progress bars

#include "cprogbar.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr, "args should be <iteration count> <fractional digits to "
                    "display> <us delay>\n");
    return -1;
  }

  unsigned long max_offset = strtoul(argv[1], NULL, 0);
  unsigned long fractional_digits = strtoul(argv[2], NULL, 0);
  unsigned int us_delay = (unsigned int)strtoul(argv[3], NULL, 0);

// hide cursor
#define CSI "\x1B["
  fputs(CSI "?25l", stdout);

  printf("Percent only:\n");
  size_t progbar = 0;
  for (size_t i = 0; i < max_offset; i++) {
    progbar = cprogpct(progbar, i, max_offset, fractional_digits);
    usleep(us_delay);
  }
  printf("\n");

  // show cursor
  fputs(CSI "?25h", stdout);

  return 0;
}
