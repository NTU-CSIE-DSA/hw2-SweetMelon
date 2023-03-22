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

void heap_pullup(int idx) {
  int stp = heap[idx].stp;
  int curr_id = heap[idx].sz;
  while (curr_id > 1) {
    int p = curr_id >> 1;
    if (heap_pool[stp + curr_id].c < heap_pool[stp + p].c) {
      swap_heap_node(stp + curr_id, stp + p);
    }
    curr_id = p;
  }
}

void heap_push (int idx, int c, int d) {
  heap[idx].sz++;
  heap_pool[heap[idx].stp + heap[idx].sz] = (HeapNode){c, d};
  heap_pullup(idx);
}

void heap_pulldown (int idx) {
  int stp = heap[idx].stp;
  int curr_id = 1;
  while (curr_id <= heap[idx].sz) {
    int lidx = curr_id << 1, ridx = (curr_id << 1) + 1;
    int bidx = 0;
    if (lidx <= heap[idx].sz && ridx <= heap[idx].sz) {
      bidx = heap_pool[stp + lidx].c < heap_pool[stp + ridx].c ? lidx : ridx;
    }
    else if (lidx <= heap[idx].sz) {
      bidx = lidx;
    }
    else {
      break;
    }
    if (heap_pool[stp + curr_id].c > heap_pool[stp + bidx].c)
      swap_heap_node (stp + curr_id, stp + bidx);
    curr_id = bidx;
  }
}

void heap_pop (int idx) {
  heap_pool[heap[idx].stp + 1] = heap_pool[heap[idx].stp + heap[idx].sz];
  heap[idx].sz--;
  heap_pulldown(idx);
}

Node dfs (int r, int* max) {
  int curr_id = tree[r].chd_head;
  Node ret = (Node){heap_pool[heap[r].stp + 1].c, 1};
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
      while (heap[j].sz && i > heap_pool[heap[j].stp + 1].d) {
        heap_pop(j);
      }
      heap_push(j, c, i + d);
    }

    int ret = 0;
    for (int i = 1; i <= n; ++i) {
      int max = 0;
      dfs (1, &max);
      if (max > ret) ret = max;
    }
    printf("%lld\n", ret);
  }

  return 0;
}

