i=0
while [ $i -lt 4 ]; do
	tab[$i]=""
	i=$(( i + 1 ))
done

tmp="coucou"
i=0

while [ "${tmp}" != "" ]; do
	tmp=`echo "$1" | rev | cut -d. -f1 | rev`
	# echo "tmp = $tmp"
	if [ "$tmp" == "cor" ];	then
		tab[$i]="$1"
		i=$(( i + 1 ))
		shift
	else
		tmp=""
	fi
done

start=$1
end=$2
ecart=$3

echo "start = $start"
echo "end = $end"
echo "ecart = $ecart"
echo "champ_1 = ${tab[0]}"
echo "champ_2 = ${tab[1]}"
echo "champ_3 = ${tab[2]}"
echo "champ_4 = ${tab[3]}"

while [[ $start -lt $end ]]; do
	./my_corewar -dump $start ${tab[0]} ${tab[1]} ${tab[2]} ${tab[3]} > ./my_result
	./corewar -d $start ${tab[0]} ${tab[1]} ${tab[2]} ${tab[3]} > ./true_result
	diff ./my_result ./true_result
	if [ $? != 0 ];	then
		echo $start : KO
		break
	fi
	# echo $start : OK
	start=$(($start + $ecart))
	# echo start : $start
done

# echo "$start : KO"
