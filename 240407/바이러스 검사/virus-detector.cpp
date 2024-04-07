#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 1'000'000
#define ll long long
using namespace std;

ll n;
ll ans;
ll C[MAX_N + 5];

ll L, M;

void input() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> C[i];
    }
    cin >> L >> M;
}

void solve() {
    for (int i = 0; i < n; ++i) {
        C[i] -= L;
        ans++;
        
        if (C[i] <= 0) continue;
        
        if (!(C[i] % M)) ans += C[i] / M;
        else ans += (C[i] / M + 1);
    }
}

void output() {
    cout << ans << '\n';
}

int main() {
    
    fastio;
    input();
    solve();
    output();
    
    return 0;
}