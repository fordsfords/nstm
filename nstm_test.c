/* nstm_test.c - test program for nstm.c
# For documentation, see https://github.com/fordsfords/nstm
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

#ifdef __MACH__
/* Mac */
#include <unistd.h>
#define Sleep(ms) usleep((ms)*1000)
#elif defined(_WIN32)
/* Windows */
#include <windows.h>
typedef unsigned __int64 uint64_t;
#else
/* Linux */
#include <unistd.h>
#define Sleep(ms) usleep((ms)*1000)
#endif

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
  uint64_t max_histo_diff, min_histo_diff;

  nstm = nstm_create(NSTM_CLOCK_MONOTONIC);
  nstm_raw = nstm_create(NSTM_CLOCK_MONOTONIC_RAW);
  nstm_rt = nstm_create(NSTM_CLOCK_REALTIME);
  nstm_best = nstm_create(NSTM_CLOCK_BEST);
  t1 = nstm_get(nstm);
  t1_raw = nstm_get(nstm_raw);
  t1_rt = nstm_get(nstm_rt);

  Sleep(1);
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

  printf("t1==%"PRIu64", t1_raw=%"PRIu64", t1_rt=%"PRIu64"\n",
    t1, t1_raw, t1_rt);
  printf("Sleep(1)=%"PRIu64", raw=%"PRIu64", rt=%"PRIu64"\n",
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

  /* Generate histogram of execution times. */
  {
    #define HISTO_SZ 10000
    int histo[HISTO_SZ];
    int i;
    for (i=0; i<HISTO_SZ; i++) histo[i] = 0;

    max_histo_diff = 0;
    min_histo_diff = -1;
    for (i=0; i<1000000; i++) {
      uint64_t t1;
      uint64_t t3;
      uint64_t diff;
      t1 = nstm_get(nstm_best);
      (void)nstm_get(nstm_best);
      t3 = nstm_get(nstm_best);
      diff = t3-t1;
      if (diff > max_histo_diff) {
        max_histo_diff = diff;
      }
      if (diff < min_histo_diff) {
        min_histo_diff = diff;
      }
      diff = diff / UINT64_C(10);
      if (diff >= HISTO_SZ) {
        diff = (HISTO_SZ - 1);
      }
      histo[diff]++;
    }

    for (i=0; i<HISTO_SZ; i++) {
      if (histo[i] > 0) {
        printf("histo[%d]=%d\n", i, histo[i]);
      }
    }
    printf("max_histo_diff=%"PRIu64", min_histo_diff=%"PRIu64"\n",
        max_histo_diff, min_histo_diff);
  }

  /* Get a series of calls. */
  {
    #define SERIES_SZ 100
    uint64_t series[SERIES_SZ];
    int i;
    uint64_t max_series_diff;

    /* Warm-up run. */
    for (i = 0; i < SERIES_SZ; i++) {
      series[i] = nstm_get(nstm_best);
    }

    /* Look for a run with pretty big outlier. */
    max_series_diff = 0;
    while (max_series_diff < (max_histo_diff / 3)) {
      for (i = 0; i < SERIES_SZ; i++) {
        series[i] = nstm_get(nstm_best);
      }
      max_series_diff = 0;
      for (i = 1; i < SERIES_SZ; i++) {
        if ((series[i] - series[i-1]) > max_series_diff) {
          max_series_diff = series[i] - series[i-1];
        }
      }
    }  /* while max_series_diff */
    for (i = 1; i < SERIES_SZ; i++) {
      printf("series diff %d=%"PRIu64"\n", i, series[i] - series[i-1]);
    }
  }

  nstm_delete(nstm);
  nstm_delete(nstm_raw);
  nstm_delete(nstm_rt);

  return 0;
}  /* main */
