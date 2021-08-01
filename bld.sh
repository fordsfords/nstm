#!/bin/sh
# bld.sh - script to build nstm and its test program.

# gcc -std=c99 -o nstm_test nstm.c nstm_test.c
gcc -o nstm_test nstm.c nstm_test.c
