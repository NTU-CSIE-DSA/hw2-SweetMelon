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
HeapNode heap_pool[MAXNM + 1];
Heap heap[MAXNM + 1];
Node node_pool[MAXNM + 1];
TreeNode tree[MAXNM + 1];

void swap_heap_node (int a, int b) {
  HeapNode tmp = heap_pool[a];
  heap_pool[a] = heap_pool[b];
  heap_pool[b] = tmp;
}

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

void heap_push (int idx, int c, int d) {
  heap[idx].sz++;
  heap_pool[heap[idx].stp + heap[idx].sz] = (HeapNode){c, d};
}

Node dfs (int r, int* max, int curr_m) {
  int curr_id = tree[r].chd_head;
  Node ret = (Node){1000000000, 1};
  for (int i = 1; i <= heap[r].sz; ++i) {
    if (heap_pool[heap[r].stp + i].d < curr_m) continue;
    ret.idx = ret.idx > heap_pool[heap[r].stp + i].c ? heap_pool[heap[r].stp + i].c : ret.idx;
  }
  while (curr_id) {
    Node chd = dfs(node_pool[curr_id].idx, max, curr_m);
    ret.idx += chd.idx;
    ret.nxt += chd.nxt;
    curr_id = node_pool[curr_id].nxt;
  }

  if (ret.idx <= C) {
    *max = ret.nxt > *max ? ret.nxt : *max;
  }

  return ret;
}

signed main () {
  scanf("%lld%lld%lld", &n, &m, &C);

  heap[1].stp = 0;
  for (int i = 2; i <= n; ++i) {
    int p;
    scanf("%lld", &p);
    link(p, i);
    heap[i].stp = (i - 1) * m;
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int c, d;
      scanf("%lld%lld", &c, &d);
      heap_push(j, c, i + d);
    }

    int max = 0;
    dfs (1, &max, i);
    printf("%lld\n", max);
  }

  return 0;
}

