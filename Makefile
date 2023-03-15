F = -std=c++20 -ggdb -Wall -Wextra -Werror -pedantic -Wfatal-errors
P = mapset
Z = HW9.zip

def: $P

mapset: SetList.h MapArray.h mapset.cpp
	g++ $F mapset.cpp -o mapset

clean:
	/bin/rm -rf $P frequency.txt *.dSYM $Z

zip: clean
	zip $Z *.h *.cpp *.txt Makefile

mem_linux: $P
	valgrind -s $P

mem_mac: $P
	leaks --atExit -- $P