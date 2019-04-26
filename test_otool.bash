#!/bin/bash
#make

bins=$@
echo $bins

for name in $bins; do
	echo $name;
	otool -t $name > a;
	./ft_otool $name > b;
	res=$(diff a b)
	if [[ "$res" != "" ]]; then
		vimdiff a b;
	fi
	rm a b;
	if [[ "$res" != "" ]]; then
		exit
	fi
	echo "end $name coparison";
done
