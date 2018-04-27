#!/bin/bash
prefix="./cor/"

ls -1 cor > ./tmp
nb_champ=`cat ./tmp | wc -l`

i=0;
tab[$i]=""
i=$(( i + 1 ))
while [ $i -le $nb_champ ]; do
    tab[$i]=`sed -n ${i}p ./tmp`
    tab[$i]=${prefix}${tab[$i]}
    i=$(( i + 1 ))
done

rm ./tmp


echo ${#tab[@]}
echo ""
i=0

while [ $i -lt ${#tab[@]} ]; do
    echo "|${tab[$i]}|"
    i=$(( i + 1 ))
done

if [ $1 == "reset" ]
    then
    echo "0" > ./log
    echo "0" >> ./log
    echo "0" >> ./log
    echo "1" >> ./log
    echo "0" >> ./log
    exit
fi

i=`sed -n 1p ./log`
j=`sed -n 2p ./log`
k=`sed -n 3p ./log`
l=`sed -n 4p ./log`
nb_fight=`sed -n 5p ./log`
dump=$1
news=10000

while [ $i -le $nb_champ ]; do
    while [ $j -le $nb_champ ]; do
        while [ $k -le $nb_champ ]; do
            while [ $l -le $nb_champ ]; do
                ./my_corewar -dump $dump ${tab[$i]} ${tab[$j]} ${tab[$k]} ${tab[$l]} > my_test
                ./corewar -d $dump ${tab[$i]} ${tab[$j]} ${tab[$k]} ${tab[$l]} > true_test
                diff my_test true_test > test_diff
                if [ $? != 0 ]
                    then
                    echo "${tab[$i]} ${tab[$j]} ${tab[$k]} ${tab[$l]} : KO"
                    echo "nombre de combat reussi : `sed -n 5p ./log`" > ./mail_content
                    ECHO "" >> ./mail_content
                    echo "echec du combat ${tab[$i]} ${tab[$j]} ${tab[$k]} ${tab[$l]}" >> ./mail_content
                    ARG=`sh ./FIGHT.sh ${tab[$i]} ${tab[$j]} ${tab[$k]} ${tab[$l]} 3000 $dump 1 | grep "KO" | cut -d: -f1`
                    # ARG=`echo $ARG | grep "KO" | cut -d: -f1`
                    echo "" >> ./mail_content
                    echo "au tour : $ARG" >> ./mail_content
                    cat ./mail_content | mail -s "YOU HAVE FAILED (THIS CITY)" ugo.popee@me.com
                    exit
                fi
                echo "${tab[$i]} ${tab[$j]} ${tab[$k]} ${tab[$l]} : OK"
                echo "$i" > ./log
                echo "$j" >> ./log
                echo "$k" >> ./log
                echo "$l" >> ./log
                echo "$nb_fight" >> ./log
                nb_fight=$(( nb_fight + 1 ))
                l=$(( l + 1 ))
                if [ `echo "$nb_fight % $news" | bc` -eq 0 ]
                    then
                    echo "nombre de combat reussi : $nb_fight" > ./mail_content
                    cat ./mail_content | mail -s "COREWAR NEWS" ugo.popee@me.com
                fi
            done
            echo "$i" > ./log
            echo "$j" >> ./log
            echo "$k" >> ./log
            echo "$l" >> ./log
            echo "$nb_fight" >> ./log
            l=1
            k=$(( k + 1 ))
        done
        echo "$i" > ./log
        echo "$j" >> ./log
        echo "$k" >> ./log
        echo "$l" >> ./log
        echo "$nb_fight" >> ./log
        k=1
        j=$(( j + 1 ))
    done
    echo "$i" > ./log
    echo "$j" >> ./log
    echo "$k" >> ./log
    echo "$l" >> ./log
    echo "$nb_fight" >> ./log
    j=1
    i=$(( i + 1 ))
done

rm test_diff
rm my_test
rm true_test
echo "you're really the best ta ta tatata !!!" | mail -s "IT'S OVER NOW, EVERYTHING GONNA BE ALRIGHT SON" ugo.popee@me.com
