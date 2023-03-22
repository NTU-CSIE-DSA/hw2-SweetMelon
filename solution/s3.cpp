#include <stdio.h>

#define MAXNM 1000000
#define int long long

typedef struct Node {
  int idx, nxt;
} Node;

typedef struct TreeNode {
  int chd_head, chd_tail;
} TreeNode;

typedef struct Heap {
  int sz, stp;
} Heap;

typedef struct HeapNode {
  int c, d;
} HeapNode;

int n, m, C;
int node_min[MAXNM + 1];
Node node_pool[MAXNM + 1];
TreeNode tree[MAXNM + 1];

int gen_node (int idx) {
  static int pool_id = 0;
  pool_id++;
  node_pool[pool_id].idx = idx;
  return pool_id;
}

void link (int p, int c) {
  int new_node = gen_node(c);
  if (tree[p].chd_head) {
    node_pool[tree[p].chd_tail].nxt = new_node;
    tree[p].chd_tail = new_node;
  }
  else {
    tree[p].chd_head = tree[p].chd_tail = new_node;
  }
}

Node dfs (int r, int* max) {
  int curr_id = tree[r].chd_head;
  Node ret = (Node){node_min[r], 1};
  while (curr_id) {
    Node chd = dfs(node_pool[curr_id].idx, max);
    ret.idx += chd.idx;
    ret.nxt += chd.nxt;
    curr_id = node_pool[curr_id].nxt;
  }

  if (ret.idx <= C) {
    *max = ret.nxt > *max ? ret.nxt : *max;
  }

  return ret;
}

signed main (int argc, char** argv) {
  scanf("%lld%lld%lld", &n, &m, &C);

  node_min[1] = 1e9;
  for (int i = 2; i <= n; ++i) {
    int p;
    scanf("%lld", &p);
    link(p, i);
    node_min[i] = 1e9;
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int c, d;
      scanf("%lld%lld", &c, &d);

      if (c < node_min[j]) node_min[j] = c;
    }

    int max = 0;
    dfs (1, &max);
    printf("%lld\n", max);
  }

  return 0;
}

