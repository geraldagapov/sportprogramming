#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
#ifdef ssu1
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  std::vector<int> a, x(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x[i]);
  }
  std::sort(x.begin(), x.end());
  for (int i = 0; i + 1 < n; ++i) {
    a.push_back(x[i + 1] - x[i]);
  }
  int cnt = (n - 2) / 2 + (n % 2);
  std::vector<int> pref(a.size() + 1);
  for (int i = 1; i < pref.size(); ++i) {
    pref[i] = pref[i - 1] + a[i - 1];
  }
  int sumsuf = 0, ans = 0;
  for (int cntsuf = 0; cntsuf <= cnt; ++cntsuf) {
    if (cntsuf > 0) {
      sumsuf += a[a.size() - cntsuf];
    }
    ans = std::max(ans, sumsuf + pref[cnt - cntsuf]);
  }
  printf("%d\n", pref.back() - ans);
  return 0;
}
