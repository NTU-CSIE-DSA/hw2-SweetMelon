#include <bits/stdc++.h>
#include <cassert>
#include "testlib.h"

#define MAXNM 1000000
#define MAXC 1000000000

using namespace std;

signed main (signed argc, char** argv) {
  registerValidation(argc, argv);
  int n = inf.readInt(2, MAXNM, "n");
  inf.readSpace();
  int m = inf.readInt(1, MAXNM, "m");
  inf.readSpace();
  assert(n * m <= MAXNM);
  int C = inf.readInt(1, MAXC);
  inf.readEoln();

  for (int i = 2; i <= n; ++i) {
    inf.readInt(i - 1, i - 1, "node");
    inf.readSpace();
  }
  inf.readEoln();

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int c = inf.readInt(1, C, "c");
      inf.readSpace();
      int d = inf.readInt(0, m, "d");
      inf.readEoln();
    }
  }

  inf.readEof();

  return 0;
}


