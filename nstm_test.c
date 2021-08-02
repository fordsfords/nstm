/* nstm_test.c - test program for nstm.c
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
#include <inttypes.h>
#include <unistd.h>
#include "nstm.h"

#define M 10
#define N (M*1000000)

int main(int argc, char **argv)
{
  nstm_t *nstm;
  nstm_t *nstm_raw;
  nstm_t *nstm_rt;
  nstm_t *nstm_best;
  int i;
  uint64_t t1, t2, t3, t4, t5, t6, t7, t_ignore;
  uint64_t t1_raw, t2_raw, t3_raw, t4_raw, t5_raw, t6_raw, t7_raw;
  uint64_t t1_rt, t2_rt, t3_rt, t4_rt, t5_rt, t6_rt, t7_rt;

  nstm = nstm_create(CLOCK_MONOTONIC);
  nstm_raw = nstm_create(CLOCK_MONOTONIC_RAW);
  nstm_rt = nstm_create(CLOCK_REALTIME);
  nstm_best = nstm_create(NSTM_CLOCKID_BEST);
  t1 = nstm_get(nstm);
  t1_raw = nstm_get(nstm_raw);
  t1_rt = nstm_get(nstm_rt);

  usleep(100);
  t2 = nstm_get(nstm);
  t2_raw = nstm_get(nstm_raw);
  t2_rt = nstm_get(nstm_rt);

  t3 = nstm_get(nstm);
  t3_raw = nstm_get(nstm_raw);
  t3_rt = nstm_get(nstm_rt);

  for (i = 0; i < N; i++) {
    t_ignore = nstm_get(nstm);
  }
  t4 = nstm_get(nstm);
  t4_raw = nstm_get(nstm_raw);
  t4_rt = nstm_get(nstm_rt);

  for (i = 0; i < N; i++) {
    t_ignore = nstm_get(nstm_raw);
  }
  t5 = nstm_get(nstm);
  t5_raw = nstm_get(nstm_raw);
  t5_rt = nstm_get(nstm_rt);

  for (i = 0; i < N; i++) {
    t_ignore = nstm_get(nstm_rt);
  }
  t6 = nstm_get(nstm);
  t6_raw = nstm_get(nstm_raw);
  t6_rt = nstm_get(nstm_rt);

  for (i = 0; i < N; i++) {
    t_ignore = nstm_get(nstm_best);
  }
  t7 = nstm_get(nstm);
  t7_raw = nstm_get(nstm_raw);
  t7_rt = nstm_get(nstm_rt);

/* Print some internal fields. */
#ifdef __MACH__
  printf("start_ns=%"PRIu64"\n", nstm->start_ns);

#elif defined(_WIN32)
  printf("frequency=%"PRIu64", start_ticks=%"PRIu64"\n",
      nstm->frequency, nstm->start_ticks);

#else
  printf("start_ns=%"PRIu64", start_ts.tv_sec=%jd\n",
      nstm->start_ns, (intmax_t)nstm->start_ts.tv_sec);
#endif

  printf("t1==%"PRIu64"\n", t1);
  printf("usleep(100)=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
      t2-t1, t2_raw-t1_raw, t2_rt-t1_rt);
  printf("null=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
      t3-t2, t3_raw-t2_raw, t3_rt-t2_rt);
  printf("%dM nstm_get calls=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
      M, t4-t3, t4_raw-t3_raw, t4_rt-t3_rt);
  printf("%dM nstm_get raw calls=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
      M, t5-t4, t5_raw-t4_raw, t5_rt-t4_rt);
  printf("%dM nstm_get rt calls=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
      M, t6-t5, t6_raw-t5_raw, t6_rt-t5_rt);
  printf("%dM nstm_get best calls=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
      M, t7-t6, t7_raw-t6_raw, t7_rt-t6_rt);

  nstm_delete(nstm);
  nstm_delete(nstm_raw);
  nstm_delete(nstm_rt);

  return 0;
}  /* main */
