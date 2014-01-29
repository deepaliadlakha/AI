#!/bin/bash
rm -rf results/*
for i in {10..100..10}
  do
     for j in {5..95..5}
		do
			./neural $i $j  >> results/output-lr$i < input
		done
 done


for i in {5..95..5}
  do
     for j in {10..100..10}
		do
			./neural $j $i  >> results/output-m$i < input
		done
 done
