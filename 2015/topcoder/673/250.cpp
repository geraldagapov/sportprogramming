#include <vector>
#include <algorithm>

using namespace std;

const int kmod = int(1e9) + 7;

struct BearCavalry {
  int countAssignments(vector <int> w, vector <int> h) {
    int ans = 0;
    for (int i = 0; i < h.size(); ++i) {
      int maxs = w[0] * h[i];
      vector<int> hh;
      for (int j = 0; j < h.size(); ++j) {
        if (j != i) {
          hh.push_back(h[j]);
        }
      }
      vector<int> r;
      for (int j = 1; j < w.size(); ++j) {
        int cnt = 0;
        for (int k = 0; k < hh.size(); ++k) {
          if (maxs > hh[k] * w[j]) {
            cnt++;
          }
        }
        r.push_back(cnt);
      }
      sort(r.begin(), r.end());
      int curans = 1, sub = 0;
      for (const int& cnt : r) {
        curans = (curans * 1ll * (cnt - sub)) % kmod;
        sub++;
      }
      ans = (ans + curans) % kmod;
    }
    return ans;
  }
};
