#!bin/bash

mkdir d0s_4s

for i in {0..599}
do
    mkdir d0s_4s/d0_${i}
    echo d0s_4s/d0_${i} created
done