#include <stdio.h>

#define int long long
#define MAXNM 1000000

// tree
#define TN(x) (tree[(x)]) // turn id to tree node
#define NXT_CHD(x) (TN(x).sibling) // get the next child
#define traverse_chd(x, y) for((y) = TN(x).chd; (y); (y) = NXT_CHD((y))) // traverse all child of a tree node

// heap
#define TOP(x) (heaps[(x)].heap[1]) // top of the heap
#define EMPTY(x) (!heaps[(x)].sz) // whether the heap is empty
#define SZ(x) (heaps[(x)].sz) // size of heap
#define LC_ID(x) ((x) << 1) // left child index
#define RC_ID(x) (((x) << 1) + 1) // right child index
#define PAR_ID(x) ((x) >> 1) // parent index

typedef struct HeapNode {
  int cost, exp_day;
} HeapNode;

typedef struct Heap {
  int sz;
  HeapNode *heap;
} Heap;

typedef struct TreeNode {
  int chd, sibling, hid, sum, cnt;
} TreeNode;

HeapNode h_pool[2 * MAXNM + 1];
TreeNode tree[MAXNM + 1];
Heap heaps[MAXNM + 1];

void insert(int par, int n) {
  TN(n).sibling = TN(par).chd;
  TN(par).chd = n;
}

void push_up(HeapNode *heap, int idx) {
  int par_id = 0;
  if ((par_id = PAR_ID(idx))) {
    if (heap[par_id].cost > heap[idx].cost) {
      HeapNode tmp = heap[idx];
      heap[idx] = heap[par_id];
      heap[par_id] = tmp;
      push_up(heap, idx >> 1);
    }
  }
}

void push_down(HeapNode *heap, int idx, int sz) {
  int sml_id = LC_ID(idx) < sz ? LC_ID(idx) : 0; // smallest child
  if (!sml_id) {
    return;
  }

  sml_id = RC_ID(idx) < sz ? RC_ID(idx) : LC_ID(idx);
  if (heap[sml_id].cost > heap[LC_ID(idx)].cost)
    sml_id = LC_ID(idx);
  if (heap[sml_id].cost > heap[idx].cost)
    sml_id = idx;

  if (sml_id == idx)
    return;

  HeapNode tmp = heap[idx];
  heap[idx] = heap[sml_id];
  heap[sml_id] = tmp;

  push_down(heap, sml_id, sz);
}

void pop(int hid) {
  HeapNode *heap = heaps[hid].heap;
  TOP(hid) = heap[--SZ(hid)];

  push_down(heap, 1, SZ(hid));
}

void push(int hid, int c, int d) {
  HeapNode *heap = heaps[hid].heap;
  heap[SZ(hid)++] = (HeapNode){c, d};

  push_up(heap, SZ(hid) - 1);
}

void dfs(int n, void(*fn)(int)) {
  int curr_chd;
  traverse_chd(n, curr_chd) {
    dfs(curr_chd, fn);
  }

  fn(n);
  return;
}

void print_tree(int n) {
  printf("%lld ", n);
}

void gen_cnt(int n) {
  int curr_chd;
  TN(n).cnt = 1;
  traverse_chd(n, curr_chd) {
    TN(n).cnt += TN(curr_chd).cnt;
  }
}

void update(int n) {
  int curr_chd;
  TN(n).sum = TOP(TN(n).hid).cost;
  traverse_chd(n, curr_chd) {
    TN(n).sum += TN(curr_chd).sum;
  }
}

void init_heap(int n, int m) {
  for (int i = 1; i <= n; ++i) {
    heaps[i].heap = h_pool + (1 + m) * i;
    heaps[i].sz = 1;
    TN(i).hid = i;
  }
}

signed main () {
  int n, m, C;
  scanf("%lld%lld%lld", &n, &m, &C);

  init_heap(n, m);
  for (int i = 2; i <= n; ++i) {
    int par;
    scanf("%lld", &par);
    insert(par, i);
  }

  dfs(1, gen_cnt);

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      int c, d;
      scanf("%lld%lld", &c, &d);

      push(j, c, i + d);
      while (TOP(j).exp_day < i)
        pop(j);
    }
    dfs(1, update);
    int ret = 0;
    for (int j = 1; j <= n; ++j)
      if (TN(j).sum <= C) ret = ret > TN(j).cnt ? ret : TN(j).cnt;

    printf("%lld\n", ret);
  }

  return 0;
}
