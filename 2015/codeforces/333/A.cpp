#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

const int kMaxN = 500;

int road[kMaxN][kMaxN], n, m;
vector<int> g[kMaxN];

int main() {
#ifdef ssu1
  freopen("input.txt", "r", stdin);
#endif
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int v, u;
    cin >> v >> u;
    --v, --u;
    road[v][u] = road[u][v] = 1;
  }
  for (int v = 0; v < n; ++v) {
    for (int u = 0; u < n; ++u) {
      if (road[0][n - 1] ^ road[v][u]) {
        g[v].push_back(u);
      }
    }
  }
  queue<int> q;
  vector<int> d(n, kMaxN);
  q.push(0);
  d[0] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : g[v]) {
      if (d[u] > d[v] + 1) {
        d[u] = d[v] + 1;
        q.push(u);
      }
    }
  }
  if (d[n - 1] == kMaxN)
    puts("-1");
  else
    cout << d[n - 1] << endl;
  return 0;
}
