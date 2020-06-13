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

void cprog_pct_or_bar(size_t new_offset, size_t max_offset,
                      size_t frac_digits) {

  printf("\r%3.*f%%", (int)frac_digits,
         ((float)new_offset * 100.0f) / (float)max_offset);

  fflush(stdout);
}
