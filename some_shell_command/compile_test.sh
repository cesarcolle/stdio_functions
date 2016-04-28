#!/bin/bash

echo clean repository
make clean
echo \n
echo $1

if [ "$1" == "test_cp" ]; then
    rm -r ./dirr
    mkdir -p ./test/on/LS/FUNCTION
    mkdir dirr
    echo "fic 1" > ./test/on/LS/FUNCTION/fic1.txt
    echo "fic 2"  > ./test/on/fic2.txt
    echo "fic 3" > ./test/fic3.txt
    make res_cp
    echo "test reccursif"
    ./res_cp.exe -r ./test ./dirr/
    echo "cp non reccursif"
    ./res_cp.exe ./makefile ./test
    
else
    echo "usage: revelation \n
 test_cp       Use the test on cp_recc i.e cp -r and cp .."
 
fi;
