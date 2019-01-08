#!bin/bash

DIRECTORY9="d0_Folder"
DIRECTORY1="d0_tmp"

DIRECTORY2="d0_Raw"

if [ ! -d "$DIRECTORY1" ]
then
    mkdir $DIRECTORY1
    for i in {0..599}
    do
        if [ $(($i % 1)) -eq 0 ]
        then
            mkdir d0_tmp/d0_${i}
            echo d0_tmp/d0_${i} created
        fi
    done
fi

if [ ! -d "$DIRECTORY9" ]
then
    mkdir $DIRECTORY9
    for k in {1..5}
    do
        mkdir d0_Folder/d0s_${k}_4
        for i in {0..599}
        do
            if [ $(($i % 4)) -eq 0 ]
            then
                mkdir d0_Folder/d0s_${k}_4/d0_${i}
                echo d0_Folder/d0s_${k}_4/d0_${i} created
            fi
        done
    done
fi


if [ ! -d "$DIRECTORY2" ]
then
    mkdir $DIRECTORY2
    for k in {1..5}
    do
        mkdir d0_Raw/d0s_${k}
        for i in {0..599}
        do
            if [ $(($i % 1)) -eq 0 ]
            then
                mkdir d0_Raw/d0s_${k}/d0_${i}
                echo d0_Raw/d0s_${k}/d0_${i} created
            fi
        done
    done
fi