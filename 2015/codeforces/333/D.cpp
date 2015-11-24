#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int kMaxN = 330000;
const int kAlphabetSize = 30;

int n, tree[kMaxN][kAlphabetSize], tree_size[kMaxN], m;
string s;
vector<int> g[kMaxN];

void UpdateSize(int v) {
  tree_size[v] = 1;
  for (int c = 0; c < kAlphabetSize; ++c) {
    int u = tree[v][c];
    if (u != -1) {
      tree_size[v] += tree_size[u];
    }
  }
}

int MergeTree(int v1, int v2) {
  if (v1 == -1 || v2 == -1) {
    return v1 == -1 ? v2 : v1;
  }
  int result = v1;
  for (int c = 0; c < kAlphabetSize; ++c) {
    int u1 = tree[v1][c], u2 = tree[v2][c];
    if (u1 == -1 && u2 == -1) continue;
    if (u1 == -1 && u2 != -1) tree[result][c] = u2;
    if (u1 != -1 && u2 == -1) tree[result][c] = u1;
    if (u1 != -1 && u2 != -1) tree[result][c] = MergeTree(u1, u2);
  }
  UpdateSize(result);
  return result;
}

int c[kMaxN];

int BuildTrie(int v, int parent) {
  int tree_v = m++;
  for (int u : g[v]) {
    if (u == parent) {
      continue;
    }
    int& current = tree[tree_v][s[u] - 'a'];
    current = MergeTree(current, BuildTrie(u, v));
  }
  UpdateSize(tree_v);
  c[v] += tree_size[tree_v];
  return tree_v;
}

int main() {
#ifdef ssu1
  freopen("input.txt", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
  }
  cin >> s;
  for (int i = 0; i < n - 1; ++i) {
    int v, u;
    scanf("%d%d", &v, &u);
    --v, --u;
    g[v].push_back(u);
    g[u].push_back(v);
  }

  memset(tree, -1, sizeof tree);
  BuildTrie(0, -1);
  
  int maxv = *max_element(c, c + n), cntmax = 0;
  for (int i = 0; i < n; ++i) {
    if (c[i] == maxv) {
      cntmax++;
    }
  }

  cout << maxv << " " << cntmax << endl;
  return 0;
}
