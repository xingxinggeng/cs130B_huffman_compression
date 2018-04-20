all: main

main: frequencies.cpp
	g++ -std=c++11 frequencies.cpp -o frequencies

clean:
	rm -f main
