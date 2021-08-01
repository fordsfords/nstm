/* nstm.c - simple module for nanosecond-level timings.
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

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#ifdef __MACH__
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#include "nstm.h"


/* Simple assert - print to stderr and abort (generate core file).
 * A "real" program typically does something different than this. */
#define ASSRT(cond_) do { \
  if (! (cond_)) { \
    fprintf(stderr, "\n%s:%d, ERROR: '%s' not true\n", \
      __FILE__, __LINE__, #cond_); \
    abort(); \
  } \
} while (0)


nstm_t *nstm_create(clockid_t clk_id)
{
  kern_return_t kstat;
  nstm_t *nstm = (nstm_t *)malloc(sizeof(nstm_t));
  ASSRT(nstm != NULL);

  nstm->clk_id = clk_id;

#ifdef __MACH__
  nstm->start_ns = clock_gettime_nsec_np(clk_id);
  nstm->cur_ns = nstm->start_ns;
#else
  clock_gettime(clk_id, &nstm->start_ts);
  nstm->cur_ns = nstm->start_ts.tv_nsec;
#endif

  return nstm;
}  /* nstm_create */


void nstm_delete(nstm_t *nstm)
{
  free(nstm);
}  /* nstm_delete */


uint64_t nstm_get(nstm_t *nstm)
{
#ifdef __MACH__
  nstm->cur_ns = clock_gettime_nsec_np(nstm->clk_id);
#else
  clock_gettime(nstm->clk_id, &nstm->cur_ts);
  nstm->cur_ns = (uint64_t)(nstm->cur_ts.tv_sec - nstm->start_ts.tv_sec)
      * UINT64_C(1000000000) + (uint64_t)nstm->cur_ts.tv_nsec;
#endif

  return nstm->cur_ns;
}  /* nstm_get */