#!/bin/bash

v_level=31

dump="-d $1"
head="head -n $2"
verb="-v $v_level"
champs="$3 $4 $5 $6"

diff_cmd="diff -C 1 -b"
our_corewar="../corewar -z $verb $dump $champs"
zaz_corewar="./corewar_zaz $verb $dump $champs"

if (($# < 3))
then
	echo "> Usage:"
	echo "./vm_diff.sh [dump cycles] [nb_lines to cmp] ./path/to/champ.cor [...]"
elif (($1 < 1))
then
	echo "Please enter a positive dump cycles number ( >= 1 )"
elif (($2 < 1))
then
	echo "Please enter a positive lines number ( >= 1 )"
else
	echo "+-------------------------------------------"
	echo "| WARNING : Having diffs with Zaz's VM"
	echo "| does not mean you're wrong"
	echo "+-------------------------------------------"
	echo "| Doing diff on the first" $2 "lines"
	echo "+-------------------------------------------"
	echo "| Verb level >" $v_level "|" $1 "cycles"
	echo "+-------------------------------------------"
	echo "| " $3
	echo "| " $4
	echo "| " $5
	echo "| " $6
	echo "+-------------------------------------------"
	echo ">> COMMAND <<"
	echo ""
	echo "$diff_cmd <($our_corewar | $head) <($zaz_corewar | $head)"
	echo ""
	echo "--------------------------------------------"
	$diff_cmd <($our_corewar | $head) <($zaz_corewar | $head)
fi
