#!/usr/local/bin/fish
make

set bins $argv

for name in $bins
	#if file $name | head -1 | grep -qo "Mach-O 64-bit executable x86_64"
		if file $name | head -1 | grep -qo "Mach-O universal binary with"
			echo "FAT BINARY NOT SUPPORTED"
		else
			echo $name
			nm $name > a;
			./nm $name > b;
			diff a b;
			rm a b
			echo "end $name coparison"
		end
	#end
end
