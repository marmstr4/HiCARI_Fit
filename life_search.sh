#!/bin/bash

iso="128Cd"
rm output_file.csv
touch output_file.csv
cp lvldata/${iso}_old.lvldata lvldata/$.lvldata

UCHiCARI mac/${iso}.mac
SimCalculate -i dat/${iso}.dat -o calc/${iso}_calc.dat -s set/${iso}.set
Sim_histos -i calc/${iso}_calc.dat -o ${iso}_histos.root

for i in {0..10};
  do
  for j in {0..10};
    do
      sed -i "s+   1  -     645.8        1e-12     2.0   1+   1  -     645.8        ${i}e-12     2.0   1+g" lvldata/${iso}.lvldata
      sed -i "s+ 2  -     1430.39       1e-12+ 2  -     1430.39       ${j}e-12+g" lvldata/${iso}.lvldata

      UCHiCARI mac/${iso}.mac
      SimCalculate -i dat/${iso}.dat -o calc/${iso}_calc.dat -s set/${iso}.set
      Sim_histos -i calc/${iso}_calc.dat -o ${iso}_histos.root

      hadd -f comb.root ${iso}_histos.root say.root

      root -q -b comb.root "background.C($i ,$j )";

      sed -i "s+   1  -     645.8        ${i}e-12     2.0   1+   1  -     645.8        1e-12     2.0   1+g" lvldata/${iso}.lvldata
      sed -i "s+ 2  -     1430.39       ${j}e-12+ 2  -     1430.39       1e-12+g" lvldata/${iso}.lvldata
  done;
done;

python3 ChiPlot.py
