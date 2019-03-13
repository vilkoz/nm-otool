#!/usr/local/bin/fish
make

set bins $argv

for name in $bins
	echo $name
	nm $name > a;
	./nm $name > b;
	diff a b;
	rm a b
	echo "end $name coparison"
end
