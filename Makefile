all: main

main: frequencies.cpp huffman.cpp
	g++ -std=c++11 frequencies.cpp -o frequencies
	g++ -std=c++11 huffman.cpp -o huffman
	g++ -std=c++11 encode.cpp -o encode
	g++ -std=c++11 decode.cpp -o decode
clean:
	rm -f main
