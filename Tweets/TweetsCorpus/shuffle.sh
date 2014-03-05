#!/bin/bash

shuf annotated_data >shuffled_data
cat shuffled_data | head -n 100 | sed -e 's/\(.\)$/\n\1/g' > ../data_1
cat shuffled_data | head -n 200 | tail -n 100 | sed -e 's/\(.\)$/\n\1/g' > ../data_2
cat shuffled_data | head -n 300 | tail -n 100 | sed -e 's/\(.\)$/\n\1/g' > ../data_3
cat shuffled_data | head -n 400 | tail -n 100 | sed -e 's/\(.\)$/\n\1/g' > ../data_4
cat shuffled_data | tail -n 100 | sed -e 's/\(.\)$/\n\1/g' > ../data_5



