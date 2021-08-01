# nstm
C module to simplify making nanosecond-level timings. Portable across
Linux and Mac.


## Usage


## Notes

On my MacBook Air (Intel, 1.6 GHz, from early 2015):
* The resolution is microsecond (nanos are always 0).
* One call to nstm_get() takes about 87 nanoseconds (averaged over 1M calls).


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