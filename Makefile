all: main

main: frequencies.cpp huffman.cpp
	g++ -std=c++11 frequencies.cpp -o frequencies
	g++ -std=c++11 huffman.cpp -o huffman

clean:
	rm -f main
