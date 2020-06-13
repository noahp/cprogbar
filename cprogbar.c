//! Micro progress bar implementation.
//!
//! Features:
//! - integer math only
//! - percentage display and/or bar display
//!
//! Requires functioning printf + stdout on the host system.

#include "cprogbar.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! https://stackoverflow.com/a/18581693
static const size_t pow10arr[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
static size_t quick_pow10(size_t n) { return pow10arr[n]; }

size_t cprog_pct_or_bar(size_t current_pct, size_t new_offset,
                        size_t max_offset, size_t frac_digits, int show_pct

#if CPROGBAR_ENABLE_BAR
                        ,
                        int show_bar
#endif
) {
#if CPROGBAR_ENABLE_BAR
// bar width is fixed to 50 characters, to simplify math
#define bar_width 50
#endif

  // spend some stack to limit the number of calls to printf. frac_digits is
  // practically limited here, TODO verify correctness in these assumptions
  char outbuf[sizeof("100.") - 1 + sizeof("000000000") - 1
#if CPROGBAR_ENABLE_BAR
              + (sizeof("▌") - 1) * bar_width
#endif
              + 1];
  size_t outbuf_idx = 0;

  size_t new_pct = (new_offset * quick_pow10(frac_digits + 2)) / max_offset;

  if (new_pct > current_pct) {
    size_t pow10 = quick_pow10(frac_digits);
    // integer part of the pct display
    size_t intpct = new_pct / pow10;

    // assume either show_pct || show_bar
    outbuf[outbuf_idx++] = '\r';

    if (show_pct) {
      if (frac_digits > 0) {
        outbuf_idx +=
            (size_t)sprintf(&outbuf[outbuf_idx], "%3zu.%0*zu%%", intpct,
                            (int)frac_digits, new_pct % pow10);
      } else {
        outbuf_idx += (size_t)sprintf(&outbuf[outbuf_idx], "%3zu%%", intpct);
      }
    }

#if CPROGBAR_ENABLE_BAR
    if (show_bar) {
      outbuf[outbuf_idx++] = ' ';

      size_t i = 0;
      for (; i < (intpct) / 2; i++) {
        memcpy(&outbuf[outbuf_idx], "█", strlen("█"));
        outbuf_idx += strlen("█");
      }
      if ((intpct)&1U) {
        memcpy(&outbuf[outbuf_idx], "▌", strlen("▌"));
        outbuf_idx += strlen("▌");
        i++;
      }
      // move cursor to the end
      for (; i < bar_width; i++) {
        outbuf[outbuf_idx++] = ' ';
      }
    }
#endif

    outbuf[outbuf_idx] = '\0';
    printf("%s", outbuf);
    fflush(stdout);
  }

  return new_pct;
}
