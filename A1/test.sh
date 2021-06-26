#!/bin/bash

COUNT=0

for test in tests/*.in; do
    name=$(basename $test .in)
    expected=tests/$name.out
    args=tests/$name.args
    actual=tests/$name.txt
    echo "Test $name"
    cat $args | ./timetable `xargs` < $test &> $actual
    # check difference between actual and expected output
    diff $actual $expected || echo "FAIL"
    let COUNT=COUNT+1

done

echo $COUNT tests finished
