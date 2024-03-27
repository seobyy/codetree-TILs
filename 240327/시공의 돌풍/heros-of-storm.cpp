#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

int n, m, t;
int ans;
int tornado_y;
int Map[55][55];

// 상 하 좌 우
const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

void input() {
    cin >> n >> m >> t;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> Map[i][j];
            if (Map[i][j] == -1 && !tornado_y)
                tornado_y = i;
        }
    }
}

void dust_move() {
    
    int tmp[55][55];
    memmove(tmp, Map, sizeof(tmp));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (Map[i][j] && Map[i][j] != -1) {
                
                int move = Map[i][j] / 5;
                
                for (int k = 0; k < 4; ++k) {
                    
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                    
                    if (ny < 0 || ny >= n || nx < 0 || nx >= m)
                        continue;
                    if (Map[ny][nx] == -1)
                        continue;
                    
                    tmp[ny][nx] += move;
                    tmp[i][j] -= move;
                    
                }
            }
        }
    }
    
    memmove(Map, tmp, sizeof(Map));
}

void tornado_move() {
    
    // 위: 왼쪽 변
    for (int i = tornado_y - 1; i > 0; --i) {
        Map[i][0] = Map[i - 1][0];
    }
    // 위: 윗변 
    for (int j = 0; j < m - 1; ++j) {
        Map[0][j] = Map[0][j + 1];
    }
    // 위: 오른쪽 변
    for (int i = 0; i < tornado_y; ++i) {
        Map[i][m - 1] = Map[i + 1][m - 1];
    }
    // 위 : 아랫변
    for (int j = m - 1; j > 0; --j) {
        if (j == 1) Map[tornado_y][j] = 0;
        else Map[tornado_y][j] = Map[tornado_y][j - 1];
    }
    
    // 아래: 왼쪽 변  
    for (int i = tornado_y + 2; i < n - 1; ++i) {
        Map[i][0] = Map[i + 1][0];
    }
    // 아래: 아랫 변   
    for (int j = 0; j < m - 1; ++j) {
        Map[n - 1][j] = Map[n - 1][j + 1];
    }
    // 아래: 오른쪽 변
    for (int i = n - 1; i > tornado_y + 1; --i) {
        Map[i][m - 1] = Map[i - 1][m - 1];
    } 
    // 아래: 윗변 
    for (int j = m - 1; j > 0; --j) {
        if (j == 1) Map[tornado_y + 1][j] = 0;
        else Map[tornado_y + 1][j] = Map[tornado_y + 1][j - 1];
    }
}
/*
void print_array() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}
*/
void solve() {
    while (t--) {
        dust_move();
        //print_array();
        tornado_move();
        //print_array();
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (Map[i][j] != -1)
                ans += Map[i][j];
        }
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