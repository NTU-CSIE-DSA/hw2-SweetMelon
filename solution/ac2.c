#include <stdio.h>

#define ll long long
#define MAXNM 1000000

// heap
#define ROOT(x) (heaps[(x)].heap[1]) // root of the heap, one index heap
#define EMPTY(x) (!heaps[(x)].sz) // whether the heap is empty
#define SZ(x) (heaps[(x)].sz) // size of heap
#define LEFT(x) ((x) << 1) // left child index
#define RIGHT(x) (((x) << 1) + 1) // right child index
#define PARENT(x) ((x) >> 1) // parent index

typedef struct HeapNode {
  ll cost, exp_day;
} HeapNode;

typedef struct Heap {
  int sz;
  HeapNode *heap;
} Heap;

typedef struct TreeNode {
  int chd, sibling, hid;
  ll sum, cnt;
} TreeNode;

HeapNode h_pool[2 * MAXNM + 1];
TreeNode tree[MAXNM + 1];
Heap heaps[MAXNM + 1];

void insert(int par, int n) {
  tree[n].sibling = tree[par].chd;
  tree[par].chd = n;
}

void push_up(HeapNode *heap, int idx) {
  int parent = 0;
  if ((parent = PARENT(idx))) {
    if (heap[parent].cost > heap[idx].cost) {
      HeapNode tmp = heap[idx];
      heap[idx] = heap[parent];
      heap[parent] = tmp;
      push_up(heap, idx >> 1);
    }
  }
}

void push_down(HeapNode *heap, int idx, int sz) {
  int sml_id = LEFT(idx) < sz ? LEFT(idx) : 0; // smallest child
  if (!sml_id) {
    return;
  }

  sml_id = RIGHT(idx) < sz ? RIGHT(idx) : LEFT(idx);
  if (heap[sml_id].cost > heap[LEFT(idx)].cost)
    sml_id = LEFT(idx);
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
  ROOT(hid) = heap[--SZ(hid)];

  push_down(heap, 1, SZ(hid));
}

void push(int hid, ll c, ll d) {
  HeapNode *heap = heaps[hid].heap;
  heap[SZ(hid)++] = (HeapNode){c, d};

  push_up(heap, SZ(hid) - 1);
}

void dfs(int n, void(*fn)(int)) {
  for (int cur = tree[n].chd; cur; cur = tree[cur].sibling) {
    dfs(cur, fn);
  }

  fn(n);
  return;
}

void print_tree(int n) {
  printf("%d ", n);
}

void gen_cnt(int n) {
  tree[n].cnt = 1;
  for (int cur = tree[n].chd; cur; cur = tree[cur].sibling) {
    tree[n].cnt += tree[cur].cnt;
  }
}

void update(int n) {
  tree[n].sum = ROOT(tree[n].hid).cost;
  for (int cur = tree[n].chd; cur; cur = tree[cur].sibling) {
    tree[n].sum += tree[cur].sum;
  }
}

void init_heap(int n, int m) {
  for (int i = 1; i <= n; ++i) {
    heaps[i].heap = h_pool + (1 + m) * i;
    heaps[i].sz = 1;
    tree[i].hid = i;
  }
}

int main () {
  int n, m;
  ll C;
  scanf("%d%d%lld", &n, &m, &C);

  init_heap(n, m);
  for (int i = 2; i <= n; ++i) {
    int par;
    scanf("%d", &par);
    insert(par, i);
  }

  dfs(1, gen_cnt);

  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      ll c, d;
      scanf("%lld%lld", &c, &d);

      push(j, c, i + d);
      while (ROOT(j).exp_day < i)
        pop(j);
    }
    dfs(1, update);
    ll ret = 0;
    for (int j = 1; j <= n; ++j)
      if (tree[j].sum <= C) ret = ret > tree[j].cnt ? ret : tree[j].cnt;

    printf("%lld\n", ret);
  }

  return 0;
}
