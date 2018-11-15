#!/bin/bash

count=1
g++ -std=c++11 Sourse/function.cpp Sourse/main.cpp

for((; count<8; count++))
do
    input="Tests/Test$count.txt"
    if [ -f $input ]
    then
        echo -e "";
    else
        echo "No such input file which named \"$input\"! Aborting!";
	exit 1
    fi
    echo "[Test#$count]: "
    echo ""
    echo "Test hierarchial list: $(cat $input)"
    ./a.out < $input
    echo "__________________________________________";
done
echo "All values calculated"
rm ./a.out


