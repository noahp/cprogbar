//! Header for cprogbar.c
//!
//! The functions here should all be called in the same way, example:
//! ```c
//!  const size_t max_offset = 100;  //< max iteration count
//!  const size_t fractional_digits = 2;
//!  size_t progbar = 0;  //< cumulative progress
//!  for (size_t i = 0; i < max_offset; i++) {
//!    // do something here...
//!    progbar = cprogpct_and_bar(progbar, i, max_offset, fractional_digits);
//!  }
//! ```

#pragma once

#include <stdlib.h>

//! This enables using the bar form
#if !defined(CPROGBAR_ENABLE_BAR)
#define CPROGBAR_ENABLE_BAR 1
#endif

//! This enables using half-increment steps in the bar "▌"
//! About 32 bytes extra for it.
#if !defined(CPROGBAR_ENABLE_PARTIAL_BAR)
#define CPROGBAR_ENABLE_PARTIAL_BAR 1
#endif

//! Percentage and/or bar
size_t cprog_pct_or_bar(size_t current_pct, size_t new_offset,
                        size_t max_offset, size_t frac_digits, int show_pct
#if CPROGBAR_ENABLE_BAR
                        ,
                        int show_bar
#endif
);

//! Percentage only display
#define cprogpct(current_pct, new_offset, max_offset, frac_digits)             \
  cprog_pct_or_bar(current_pct, new_offset, max_offset, frac_digits, 1, 0)

#if CPROGBAR_ENABLE_BAR
//! Bar only display
#define cprogbar(current_pct, new_offset, max_offset, frac_digits)             \
  cprog_pct_or_bar(current_pct, new_offset, max_offset, frac_digits, 0, 1)

//! Percentage and bar display
#define cprogpct_and_bar(current_pct, new_offset, max_offset, frac_digits)     \
  cprog_pct_or_bar(current_pct, new_offset, max_offset, frac_digits, 1, 1)
#endif
