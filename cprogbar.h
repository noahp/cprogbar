//! Header for cprogbar.c
//!

#pragma once

#include <stdlib.h>

//! Percentage and/or bar
size_t cprogpct(size_t current_pct, size_t new_offset, size_t max_offset,
                size_t frac_digits);
