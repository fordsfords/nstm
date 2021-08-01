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
#include "nstm.h"

int main(int argc, char **argv)
{
  nstm_t *nstm;

  nstm = nstm_create();
#ifdef __MACH__
  printf("start_ns=%"PRIu64"\n", nstm->start_ns);
#else
  printf("start_ns=%"PRIu64", start_ts.tv_sec=%jd\n",
      nstm->start_ns, (intmax_t)nstm->tart_ts.tv_sec);
#endif
}  /* main */
