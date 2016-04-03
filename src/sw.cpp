#include <iostream>
#include <fstream>
#include <functional>
#include <random>
#include <ctime>
#include <stdint.h>
#include "options.h"

typedef std::function<void (const uint64_t u, const uint64_t v)> output_function;

uint64_t sw_gen(int scale, int degree, float ratio, int seed, output_function o) {
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<uint64_t> rewire(0, (1 << scale) * degree * ratio);
  std::uniform_int_distribution<uint64_t> rewire_to(0, (1 << scale) - 1);

  uint64_t d, u, v;
  uint64_t mask = (1 << scale) - 1;

  for (u = 0; u < (1 << scale); u++) {
    for (d = 1; d <= degree; d++) {
      if (rewire(gen) == 0) v = u + rewire_to(gen); else v = u + d;
      v &= mask;
      o(u, v);
    }
  }
}

int main (int argc, char* argv[]) {
  using namespace std;
  using namespace opt;

  if (chkOption(argv, argv + argc, "-h")) {
    cout
      << "sw [options]" << endl
      << " -h:\t ask for help" << endl
      << " -s:\t scale,  default: 8" << endl
      << " -d:\t degree, default: 8" << endl
      << " -t:\t ratio,  default: 0.01" << endl
      << " -r:\t srand,  default: current time" << endl
      << " -o:\t output, default: console" << endl;
    return 0;
  }

  int scale   = getValue(argv, argv + argc, "-s", 8);
  int degree  = getValue(argv, argv + argc, "-d", 8);
  float ratio = getValue(argv, argv + argc, "-t", 0.01);
  int seed    = getValue(argv, argv + argc, "-r", time(NULL));
  char* ofn   = getOption(argv, argv + argc, "-o");

  if (ofn) {
    ofstream ofile(ofn, ios::binary);
    sw_gen(scale, degree, ratio, seed, [&ofile](uint64_t u, uint64_t v) -> void {
      ofile.write((char *)&u, sizeof(uint64_t));
      ofile.write((char *)&v, sizeof(uint64_t));
    });
    ofile.close();
  } else {
    sw_gen(scale, degree, ratio, seed, [](uint64_t u, uint64_t v) -> void {
      cout << u << " " << v << endl;
    });
  }

  return 0;
}
