#!/bin/bash

sourcename="sample_rates.cpp"
outname="sample_rates"

#g++ -fPIC -DLINUX -g -Wall -c -o $outname.o $sourcename
g++ -fPIC -DLINUX -g -Wall $(root-config --cflags) $(root-config --ldflags) -I$(root-config --incdir) -c -o $outname.o $sourcename
#g++ -Wall -o $outname  $outname.o 
g++ -Wall -o $outname  $outname.o -lm $(root-config --libs --glibs)
