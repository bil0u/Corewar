#!/bin/bash

echo 'Running diff on > |' $3 '|' $4 '|' $5 '|' $6 '|'
echo 'Doing ' $1 ' cycles'
echo 'Diff of ' $2 ' first lines'
diff -C 3 -b <(./corewar -z -v 31 -d $1 $3 $4 $5 $6 | head -n $2) <(./tests/corewar_zaz -v 31 -d $1 $3 $4 $5 $6 | head -n $2)
