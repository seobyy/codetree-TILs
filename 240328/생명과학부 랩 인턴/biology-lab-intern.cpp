#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_b 10'000
using namespace std;

struct BACTERIA { int s, d, b; };
BACTERIA bpool[MAX_b + 5];

// 1 위 2 아래 3 오 4 왼
const int dy[5] = {0, -1, 1, 0, 0};
const int dx[5] = {0, 0, 0, 1, -1};

int n, m, k;
int ans;

int Map[105][105];

void input() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) {
        int y, x, s, d, b;
        cin >> y >> x >> s >> d >> b;
        bpool[i] = { s, d, b };
        Map[y][x] = i;
    }
}

void bacteria_move() {
    
    vector <int> tmp[105][105];
    
    //move
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (Map[i][j]) {
                
                int bn = Map[i][j];
                int s = bpool[bn].s;
                int d = bpool[bn].d;
                
                int ny = i + dy[d] * s;
                int nx = j + dx[d] * s;
                
                if (ny < 1 || ny > n || nx < 1 || n > m) {
                    
                    int sy = (n - 1) * 2;
                    int sx = (m - 1) * 2;
                    
                    if (ny > n) {
                        int index = (ny - 1) % sy;
                        if (index < n) 
                            tmp[index + 2][j].push_back(bn);
                        else {
                            bpool[bn].d = 1;
                            int gap = index - (n - 1);
                            tmp[n - gap][j].push_back(bn);
                        }
                    }
                    
                    else if (ny < 1) {
                        ny *= -1;
                        int index = ny % sy;
                        if (index < n) { 
                            tmp[index + 2][j].push_back(bn);
                            bpool[bn].d = 2;
                        }
                        else {
                            int gap = index - (n - 1);
                            tmp[n - gap][j].push_back(bn);
                        }
                    }
                    
                    else if (nx > m) {
                        int index = (nx - 1) % sx;
                        if (index < m)  
                            tmp[i][index + 2].push_back(bn);
                        else {
                            int gap = index - (m - 1);
                            tmp[i][m - gap].push_back(bn);
                        }
                    }
                    
                    else {
                        nx *= -1;
                        int index = nx % sx;
                        if (index < m) { 
                            tmp[i][index + 2].push_back(bn);
                            bpool[bn].d = 3;
                        }
                        else {
                            int gap = index - (n - 1);
                            tmp[n - gap][j].push_back(bn);
                        }
                    }
                }
                
                else 
                    tmp[ny][nx].push_back(bn);
                
            }
        }
    }
    
    //eat
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            
            if (!tmp[i][j].size())
                Map[i][j] = 0;
            else if (tmp[i][j].size() == 1) 
                Map[i][j] = tmp[i][j][0];
            else {
                int max_b = 0;
                int max_num = 0;
                for (auto k : tmp[i][j]) {
                    if (bpool[k].b > max_b) {
                        max_b = bpool[k].b;
                        max_num = k;
                    }
                }
                Map[i][j] = max_num;
            }
        }
    }

}

void print_map() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            cout << bpool[Map[i][j]].b << ' ';
        cout << '\n';
    }
    cout << '\n';
}


void solve() {
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) {
            
            if (Map[i][j]) {
                int num = Map[i][j];
                ans += bpool[num].b;
                Map[i][j] = 0;
                break;
            }
            
        }
        //cout << "turn : " << j << '\n';
        //print_map();
        //cout << ans << '\n';
        bacteria_move();
        //print_map();
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