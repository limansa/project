#!/bin/bash
gcc -o test  -I ../../src ../../src/bcm2835.c cc2500.c main.c -D_PI2_
