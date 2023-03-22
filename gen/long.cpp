#include "testlib.h"
#include <bits/stdc++.h>

#define MAXNM 1000000
#define MAXC 1000000000
using namespace std ;

vector<int> tree[MAXNM + 1];
int tree_output[MAXNM + 1] = {};

void gen_tree (int n) {
  int degree[MAXNM + 1] = {};
  int seq[MAXNM + 1] = {};
  for (int i = 1; i <= n - 2; ++i) {
    seq[i] = rnd.next(1, n);
    degree[seq[i]]++;
  }

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 0) pq.push(i);
  }

  for (int i = 1; i <= n - 2; ++i) {
    int leaf = pq.top();
    tree[leaf].push_back(seq[i]);
    tree[seq[i]].push_back(leaf);
    pq.pop();

    degree[seq[i]]--;
    if (degree[seq[i]] == 0) pq.push(seq[i]);
  }

  int a = pq.top();
  pq.pop();
  int b = pq.top();
  pq.pop();

  tree[a].push_back(b);
  tree[b].push_back(a);
}

void dfs (int n, int p) {
  tree_output[n] = p;
  for (auto chd : tree[n]) {
    if (chd == p) continue;
    dfs(chd, n);
  }
}

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1) ;
  assert(argc >= 3);
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int C = rnd.next(1, MAXC);
  int rnd_time = atoi(argv[3]);

  cout << n << ' ' << m << ' ' << C << '\n';

  gen_tree(n);
  dfs(1 ,1);
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
      int c = rnd.next(1, min(maxc, C));
      int d = m;
      cout << c << ' ' << d << '\n';
    }
  }
}

