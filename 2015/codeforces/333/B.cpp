#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> CalcB(vector<int> a, int rev) {
  vector<int> b, st;
  for (int i = 0; i < a.size(); ++i) {
    while (!st.empty() &&
           make_pair(a[st.back()], st.back() * rev) <
           make_pair(a[i], i * rev))
      st.pop_back();
    b.push_back(st.empty() ? -1 : st.back());
    st.push_back(i);
  }
  return b;
}

int main() {
#ifdef ssu1
  freopen("input.txt", "r", stdin);
#endif
  int n, q;
  cin >> n >> q;
  vector<int> h(n);
  for (int& hi : h) {
    cin >> hi;
  }

  vector<int> a(n - 1);
  for (int i = 0; i + 1 < n; ++i) {
    a[i] = abs(h[i + 1] - h[i]);
  }
  n--;

  vector<int> blf = CalcB(a, 1);
  reverse(a.begin(), a.end());
  vector<int> brg = CalcB(a, -1);
  reverse(a.begin(), a.end());
  reverse(brg.begin(), brg.end());
  for (int& i : brg) {
    i = n - 1 - i;
  }

  for (int qi = 0; qi < q; ++qi) {
    int l, r;
    cin >> l >> r;
    --l, --r, --r;

    long long ans = 0;
    for (int i = l; i <= r; ++i) {
      int leftCnt = min(i - blf[i], i - l + 1);
      int rightCnt = min(brg[i] - i, r - i + 1);
      ans += leftCnt * 1LL * rightCnt * 1LL * a[i];
    }

    cout << ans << endl;
  }
  return 0;
}

