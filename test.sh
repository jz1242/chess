#!/bin/sh                                                                                               

#Last gives us the number of end to end tests we have
if [[ $# < 1 ]]; then
    echo "Usage: $0 num_of_tests"
    exit 1
fi

PASS=true
for ((i=1;i<=$1;i++)); do
    ./chess < in"$i".txt > out"$i".txt 
    DIFF=$(diff realout"$i".txt out"$i".txt)
    if [ "$DIFF" != "" ]; then
       echo "FAILED test $i!"
       PASS=false
       break
    fi
done
if [ $PASS = true ]; then
    echo "PASSED all tests"
fi