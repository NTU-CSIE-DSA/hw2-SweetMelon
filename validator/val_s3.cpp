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

  int degree[MAXNM + 1] = {};
  int p[MAXNM + 1] = {};
  for (int i = 2; i <= n; ++i) {
    p[i] = inf.readInt(1, n, "node");
    inf.readSpace();
    degree[p[i]]++;
  }
  inf.readEoln();

  queue<int> buffer;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 0) buffer.push(i);
  }

  while (buffer.front() != 1) {
    degree[p[buffer.front()]]--;
    if (degree[p[buffer.front()]] == 0) buffer.push(p[buffer.front()]);
    buffer.pop();
  }

  assert(buffer.size() == 1);
  for (int i = 1; i <= n; ++i) {
    assert(degree[i] == 0);
  }

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int c = inf.readInt(1, C, "c");
      inf.readSpace();
      int d = inf.readInt(m, m, "d");
      inf.readEoln();
    }
  }
  inf.readEof();

  return 0;
}


