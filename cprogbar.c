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

#include <math.h>

size_t cprogpct(size_t current_pct, size_t new_offset, size_t max_offset,
                size_t frac_digits) {
  float new_pct = ((float)(new_offset * 100)) / (float)max_offset;
  uint32_t new_val = (uint32_t)(new_pct * powf(10, (float)frac_digits));
  if (new_val > current_pct) {

    printf("\r%.*f", (int)frac_digits, (double)new_pct);

    fflush(stdout);
  }

  return (size_t)new_val;
}
