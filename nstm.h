/* nstm.h - simple module for nanosecond-level timings.
# For documentation, see https://github.com/fordsfords/histo_pat
#
# This code and its documentation is Copyright 2002-2021 Steven Ford
# and licensed "public domain" style under Creative Commons "CC0":
#   http://creativecommons.org/publicdomain/zero/1.0/
# To the extent possible under law, the contributors to this project have
# waived all copyright and related or neighboring rights to this work.
# In other words, you can use this code for any purpose without any
# restrictions.  This work is published from: United States.  The project home
# is https://github.com/fordsfords/nstm
*/
#ifndef NSTM_H
#define NSTM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include <time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#define NSTM_CLOCKID_BEST -1

struct nstm_s {
  clockid_t clk_id;
  uint64_t start_ns;
  uint64_t cur_ns;
#ifdef __MACH__
  /* Mac */
#elif defined(_WIN32)
  /* Windows */
  uint64_t start_ticks;
  LARGE_INTEGER frequency;
#else
  /* Linux */
  struct timespec start_ts;
#endif
};
typedef struct nstm_s nstm_t;

nstm_t *nstm_create(clockid_t clk_id);
void nstm_delete(nstm_t *nstm);
uint64_t nstm_get(nstm_t *nstm);

#ifdef __cplusplus
}
#endif

#endif  /* NSTM_H */
