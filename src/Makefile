CC = g++

CXXFLAGS = --std=c++0x -O3

all:
	make rmat er sw

rmat: rmat.cpp
	$(CC) rmat.cpp $(CXXFLAGS) -o rmat

er:   er.cpp
	$(CC) er.cpp $(CXXFLAGS) -o er

sw:   sw.cpp
	$(CC) sw.cpp $(CXXFLAGS) -o sw

test:
	make all
	echo "rmat generat:"
	./rmat -s 8 -d 8 | wc -l
	echo "er   generat:"
	./er   -s 8 -d 8 | wc -l
	echo "sw   generat:"
	./sw   -s 8 -d 8 -r 0.01 | wc -l

clean:
	rm *.exe *.o rmat er sw
