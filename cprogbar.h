//! Header for cprogbar.c
//!

#pragma once

#include <stdlib.h>

//! Percentage and/or bar
void cprog_pct_or_bar(size_t new_offset, size_t max_offset, size_t frac_digits);
