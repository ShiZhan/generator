CC = g++

CXXFLAGS = --std=c++0x -O3

all:
	make rmat er

rmat: rmat.cpp
	$(CC) rmat.cpp $(CXXFLAGS) -o rmat

er:   er.cpp
	$(CC) er.cpp $(CXXFLAGS) -o er

test:
	make all
	echo "rmat generat:"
	./rmat -s 8 -d 8 | wc -l
	echo "er   generat:"
	./er   -s 8 -d 8 | wc -l

clean:
	rm *.exe *.o rmat er
