#!/bin/bash

BINARY=$1

if [ -z "$BINARY" ]; then
    echo "Error: No executable provided to test script."
    exit 1
fi

for f in test/data/*.in; do
    # Check if files actually exist (handles cases where glob finds nothing)
    [ -e "$f" ] || continue

    echo "Testing $f..."
    pre=${f%.in}
    out=$pre.out
    ans=$pre.expected
    
    # Execute the compiled binary with the input file
    $BINARY < $f > $out
    
    DIFF=$(diff -w $ans $out)
    if [ "$DIFF" == "" ]
    then 
        echo "Correct!"
    else
        echo "$f Incorrect!"
        exit 1
    fi
done
