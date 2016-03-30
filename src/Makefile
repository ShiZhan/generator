CC = g++

CXXFLAGS = --std=c++11 -O3

all:
	make rmat

rmat: rmat.cpp
	$(CC) rmat.cpp $(CXXFLAGS) -o rmat

test:
	make rmat
	./rmat -s 8 -d 8 | wc -l

clean:
	rm *.exe *.o rmat
