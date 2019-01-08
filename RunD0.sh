#!bin/bash

for i in {0..599}
do
	if [ $(( $i % 4 )) -eq 0 ];
	then
		./D0_Merge -d ${i} -s 4
		echo d12 $i done 	
	fi
done
