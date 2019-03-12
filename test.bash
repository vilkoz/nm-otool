#!/bin/bash
#make

bins=$@
echo $bins

for name in $bins; do
	if file $name | head -1 | grep -qo "Mach-O universal binary with"; then
		echo "FAT BINARY NOT SUPPORTED";
	else
		echo $name;
		nm $name > a;
		./nm $name > b;
		diff a b;
		rm a b;
		echo "end $name coparison";
	fi
done
