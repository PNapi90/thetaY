#!bin/bash

for i in {0..599}
do
    ./MergeD12 -d ${i} -s 4
done