#!/bin/sh
# tst.sh - script to build nstm and its test program.

gcc -Wall -o nstm_test nstm.c nstm_test.c
if [ $? -ne 0 ]; then exit 1; fi

./nstm_test
