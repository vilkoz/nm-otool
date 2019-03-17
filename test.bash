#!/bin/bash
#make

bins=$@
echo $bins

for name in $bins; do
	echo $name;
	nm $name > a;
	./nm $name > b;
	diff a b;
	rm a b;
	echo "end $name coparison";
done
