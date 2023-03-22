#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define pb push_back
#define MAXNM 1000000

using namespace std;

vector<int> tree[MAXNM + 1];
priority_queue<pii, vector<pii>, greater<pii>> pq[MAXNM + 1];
int n, m, C;
int ans;

pii dfs (int r, int p) {
  pii ret = {pq[r].top().first, 1};
  for (int chd : tree[r]) {
    if (chd == p) continue;
    pii chd_ret = dfs(chd, r);
    ret.first += chd_ret.first;
    ret.second += chd_ret.second;
  }

  if (ret.first <= C) {
    ans = max(ans, ret.second);
  }

  return ret;
}

signed main () {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m >> C;

  for (int i = 2; i <= n; ++i) {
    int a;
    cin >> a;
    tree[a].pb(i);
  }

  // for (int i = 1; i <= n; ++i) {
  //   for (auto chd : tree[i]) {
  //     cout << chd << ' ';
  //   }
  //   cout << '\n';
  // }

  for (int i = 0; i < m; ++i) {
    ans = 0;
    for (int j = 1; j <= n; ++j) {
      int c, d;
      cin >> c >> d;
      pq[j].push({c, i + d});

      while (!pq[j].empty() and pq[j].top().second < i) {
        pq[j].pop();
      }
    }

    dfs(1, 1);
    cout << ans << '\n';
  }

  return 0;
}
