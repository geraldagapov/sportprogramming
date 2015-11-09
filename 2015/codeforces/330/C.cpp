#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

struct Point {
  int x, y;
};

bool operator < (const Point& p1, const Point& p2) {
  return p1.y < p2.y;
}

int main() {
#ifdef ssu1
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<Point> a;
  std::vector<long long> x, y;
  for (int i = 0; i < n; ++i) {
    int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    a.push_back(Point{x1 + x2, y1 + y2});
    x.push_back(a[i].x);
    y.push_back(a[i].y);
  }
  std::sort(a.begin(), a.end());
  std::sort(x.begin(), x.end());
  x.erase(std::unique(x.begin(), x.end()), x.end());
  std::sort(y.begin(), y.end());
  y.erase(std::unique(y.begin(), y.end()), y.end());
  std::vector<long long> ys;
  long long ans = -1;
  for (int xl = 0; xl <= 10; ++xl) {
    for (int xr = 0; xr <= 10; ++xr) {
      if (xl >= x.size()) continue;
      if (xr >= x.size()) continue;

      const long long& x1 = x[xl];
      const long long& x2 = x[x.size() - xr - 1];

      if (x1 > x2) continue;

      ys.clear();
      for (const auto& p : a) {
        if (x1 <= p.x && p.x <= x2) {
          ys.push_back(p.y);
        }
      }

      for (int yl = 0; yl <= 10; ++yl) {
        for (int yr = 0; yr <= 10; ++yr) {
          if (yl >= y.size()) continue;
          if (yr >= y.size()) continue;

          const long long& y1 = y[yl];
          const long long& y2 = y[y.size() - yr - 1];

          if (y1 > y2) continue;

          auto startit = lower_bound(ys.begin(), ys.end(), y1);
          auto endit = lower_bound(ys.begin(), ys.end(), y2 + 1);
          if (endit - startit >= n - k) {
            long long difx = x2 - x1;
            if (difx == 0) difx = 1;
            if (difx % 2 == 1) difx++;
            long long dify = y2 - y1;
            if (dify == 0) dify = 1;
            if (dify % 2 == 1) dify++;
            long long area = difx * dify;
            if (ans == -1) ans = area;
            ans = std::min(ans, area);
          }
        }
      }
    }
  }
  assert(ans >= 4);
  printf("%lld\n", ans / 4);
  return 0;
}
