CC = g++

CXXFLAGS = --std=c++0x -O3

all:
	make rmat er sw ba

rmat: rmat.cpp
	$(CC) rmat.cpp $(CXXFLAGS) -o rmat

er:   er.cpp
	$(CC) er.cpp $(CXXFLAGS) -o er

sw:   sw.cpp
	$(CC) sw.cpp $(CXXFLAGS) -o sw

ba:   ba.cpp
	$(CC) ba.cpp $(CXXFLAGS) -o ba

test:
	make all
	echo "rmat generate:"
	./rmat -s 8 -d 8 | wc -l
	echo "er   generate:"
	./er   -s 8 -d 8 | wc -l
	echo "sw   generate:"
	./sw   -s 8 -d 8 -t 0.01 | wc -l
	echo "ba   generate:"
	./ba   -s 8 -d 8 | wc -l

clean:
	rm *.exe *.o rmat er sw ba
