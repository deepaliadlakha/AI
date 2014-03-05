#!/bin/bash

shuf IRIS-data >shuffled_data
cat shuffled_data | head -n 30  > data_1
cat shuffled_data | head -n 60 | tail -n 30 > data_2
cat shuffled_data | head -n 90 | tail -n 30  > data_3
cat shuffled_data | head -n 120 | tail -n 30  > data_4
cat shuffled_data | tail -n 30 > data_5



