#include <iostream>
#include <ctime>
#include <stdint.h>
#include "options.h"

int main (int argc, char* argv[]) {
	using namespace std;
	using namespace opt;

	if (chkOption(argv, argv + argc, "-h")) {
		cout << "rmat [options]" << endl
			<< " -h:\t ask for help" << endl
			<< " -s:\t scale,  default: 8" << endl
			<< " -d:\t degree, default: 8" << endl
			<< " -r:\t srand,  default: current time" << endl;
		return 0;
	}

	int scale  = getValue(argv, argv + argc, "-s", 8);
	int degree = getValue(argv, argv + argc, "-d", 8);
	uint32_t seed = getValue(argv, argv + argc, "-r", (uint32_t)time(NULL));

	srand(seed);

	int r = RAND_MAX, b4 = 0, b4_per_rand = 0, nb4 = 0;
	while ((r & 0xf) == 0xf) { b4_per_rand++; r >>= 4; }
	
	for (uint64_t e = (1 << scale) * degree; e > 0; e--) {
		uint64_t u = 0, v = 0;
		for (int i = 0; i < scale; i++) {
			if (nb4 == 0) { r = rand(); nb4 = b4_per_rand; }
			b4 = r & 0xf;
			u <<= 1; v <<= 1;
			if (b4 == 0) { u++; v++; }
			else if (b4 <= 3) u++;
			else if (b4 <= 6) v++;
			r >>= 4; nb4--;
		}
		cout << u << " " << v << endl;
	}

	return 0;
}
