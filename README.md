# nstm
C module to simplify making nanosecond-level timings. Portable across
Linux, Mac, and Windows.


## Usage

````
#include "nstm.h"
...
  nstm_t *nstm = nstm_create(NSTM_CLOCKID_BEST);
  uint64_t t1, t2;
...
  t1 = nstm_get(nstm);
... code to be timed
  t2 = nstm_get(nstm);

  printf("Duration = %"PRIu64"\n", t2 - t1);
````


## nstm_test.c

nstm_test.c is a test program that exercises the nstm module and also
measures the execution time of a few interesting things (like nstm itself).
Look at the code for details.


## Portability

I use "Sleep()" to sleep for milliseconds (and on Mac/Linux define it
in terms of "usleep()").

I use "uint64_t" and define it on Windows in terms of "unsigned __int64".


## Notes

See https://github.com/fordsfords/fordsfords.github.io/wiki/Timing-software


## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.  But "public domain" does not have an internationally agreed upon definition, so I use CC0:

Copyright 2020 Steven Ford http://geeky-boy.com and licensed
"public domain" style under
[CC0](http://creativecommons.org/publicdomain/zero/1.0/):
![CC0](https://licensebuttons.net/p/zero/1.0/88x31.png "CC0")

To the extent possible under law, the contributors to this project have
waived all copyright and related or neighboring rights to this work.
In other words, you can use this code for any purpose without any
restrictions.  This work is published from: United States.  The project home
is https://github.com/fordsfords/nstm

To contact me, Steve Ford, project owner, you can find my email address
at http://geeky-boy.com.  Can't see it?  Keep looking.
