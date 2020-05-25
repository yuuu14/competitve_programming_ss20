#!/bin/bash

# We expect the tests to be in a directory structure
# .
# |- tests/
#    |- 1.in
#    |- 1.out
#    |- 2.in
#    |- 2.out
#
# in order to compare the .out files with the output generated from running ./a.out with the input from the .in files
#

for inputfile in tests/*.in; do
    solfile=$( echo $inputfile | sed 's/in/out/')
    echo -ne "$inputfile\t"
    cat $inputfile | ./a.out | diff -Z "$solfile" - >> /dev/null
    if [[ $? == 0 ]]; then
        echo -e "passed"
    else
        echo -e "output differs"
    fi
done
