#include <iostream>
#include <fstream>
#include <functional>
#include <random>
#include <ctime>
#include <stdint.h>
#include "options.h"

typedef std::function<void (const uint64_t u, const uint64_t v)> output_function;

uint64_t ba_gen(int scale, int degree, int seed, output_function o) {
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<uint64_t> ud(0, 0xffffffffffffffff);

  uint64_t d, r, u, v;
  uint8_t bits_per_rand = 64 / scale, nbits = 0;
  uint64_t mask = (1 << scale) - 1;

  for (u = 0; u < degree; u++)
    for (v = 0; v < degree; v++)
      o(u, v);
  for (u = degree; u < (1 << scale); u++) {
    for (d = 0; d < degree; d++) {
      if (nbits == 0) { r = ud(gen); nbits = bits_per_rand; }
      v = r % u;
      r >>= scale; nbits--;
      o(u, v);
    }
  }
}

int main (int argc, char* argv[]) {
  using namespace std;
  using namespace opt;

  if (chkOption(argv, argv + argc, "-h")) {
    cout
      << "ba [options]" << endl
      << " -h:\t ask for help" << endl
      << " -s:\t scale,  default: 8" << endl
      << " -d:\t degree, default: 8" << endl
      << " -r:\t srand,  default: current time" << endl
      << " -o:\t output, default: console" << endl;
    return 0;
  }

  int scale  = getValue(argv, argv + argc, "-s", 8);
  int degree = getValue(argv, argv + argc, "-d", 8);
  int seed   = getValue(argv, argv + argc, "-r", time(NULL));
  char* ofn  = getOption(argv, argv + argc, "-o");

  if (ofn) {
    ofstream ofile(ofn, ios::binary);
    ba_gen(scale, degree, seed, [&ofile](uint64_t u, uint64_t v) -> void {
      ofile.write((char *)&u, sizeof(uint64_t));
      ofile.write((char *)&v, sizeof(uint64_t));
    });
    ofile.close();
  } else {
    ba_gen(scale, degree, seed, [](uint64_t u, uint64_t v) -> void {
      cout << u << " " << v << endl;
    });
  }

  return 0;
}
