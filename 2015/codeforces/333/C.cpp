#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int kMaxSum = 101000;

void InitSumArray(const vector<double>& a, vector<double>& sum) {
  sum.assign(a.size(), 0);
  for (int i = 0; i < a.size(); ++i) {
    sum[i] = a[i];
    if (i > 0)
      sum[i] += sum[i - 1];
  }
}

double CalcSum(const vector<double>& sum, int l, int r) {
  double ans = sum[r];
  if (l > 0)
    ans -= sum[l - 1];
  return ans;
}

int main() {
#ifdef ssu1
  freopen("input.txt", "r", stdin);
#endif
  int n, m;
  cin >> n >> m;
  vector<int> x(n);
  int sumx = 0;
  for (int& xi : x) {
    cin >> xi;
    sumx += xi;
  }

  if (m == 1) {
    puts("1");
    return 0;
  }

  vector<double> nd(kMaxSum), d(kMaxSum), sumd(kMaxSum);
  d[0] = 1.0;
  for (int i = 0; i < n; ++i) {
    InitSumArray(d, sumd);
    double p = 1.0 / (m - 1);
    for (int sum = 1; sum < kMaxSum; ++sum) {
      int l = max(sum - m, 0), r = sum - 1;
      nd[sum] = CalcSum(sumd, l, r);
      if (sum - x[i] >= 0)
        nd[sum] -= d[sum - x[i]];
      nd[sum] *= p;
    }
    d = nd;
  }
  double ans = 0;
  for (int i = 0; i < sumx; ++i) {
    ans += d[i];
  }
  printf("%.10f\n", ans * (m - 1) + 1.0);
  return 0;
}
