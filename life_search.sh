#!/bin/bash

rm output_file.csv
touch output_file.csv

for i in {0..3};
  do for j in {0,3};
    do root -q -b comb_128Cd.root "background.C($i ,$j )";
  done;
done;
