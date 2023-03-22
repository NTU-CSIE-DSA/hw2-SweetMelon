#include "testlib.h"
#include <bits/stdc++.h>

#define MAXNM 1000000
#define MAXC 1000000000
using namespace std ;

int tree_output[MAXNM + 1] = {};

void gen_tree (int n) {
  for (int i = 2; i <= n; ++i) {
    tree_output[i] = i - 1;
  }
}

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1) ;
  assert(argc >= 4);
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int C = rnd.next(1, MAXC);
  int rnd_time = atoi(argv[3]);

  cout << n << ' ' << m << ' ' << C << '\n';

  gen_tree(n);

  for (int i = 2; i <= n; ++i) {
    cout << tree_output[i] << ' ';
  }
  cout << '\n';

  int maxc = rnd.next(1, MAXC);
  for (int i = 0; i < rnd_time; ++i) {
    maxc = min(rnd.next(1, MAXC), maxc);
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int c = rnd.next(1, min(C, maxc));
      int d = rnd.next(0, m - i);
      cout << c << ' ' << d << '\n';
    }
  }
}

