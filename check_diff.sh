#!/bin/bash

v_level=31

dump="-d $1"
head="head -n $2"
verb="-v $v_level"
champs="$3 $4 $5 $6"

diff_cmd="diff -C 1 -b"
our_corewar="./corewar -z $verb $dump $champs"
zaz_corewar="./tests/corewar_zaz $verb $dump $champs"

echo "+-------------------------------------------"
echo "| Testing diff on the first" $2 "lines"
echo "+-------------------------------------------"
echo "| Verb level >" $v_level "|" $1 "cycles" 
echo "+-------------------------------------------"
echo "| " $3
echo "| " $4
echo "| " $5
echo "| " $6
echo "+-------------------------------------------"
echo "$diff_cmd <($our_corewar | $head) <($zaz_corewar | $head)"
echo "--------------------------------------------"

$diff_cmd <($our_corewar | $head) <($zaz_corewar | $head)
