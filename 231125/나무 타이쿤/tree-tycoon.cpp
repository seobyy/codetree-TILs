#include <iostream>
#include <vector>
#include <memory.h>
#define fasio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 15
using namespace std;

struct POS { int y, x; };

int n, m;
int d, p;
int map[MAX_N + 5][MAX_N + 5];
bool nutrition[MAX_N + 5][MAX_N + 5];
bool isUsed[MAX_N + 5][MAX_N + 5];

const int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};

void getNutri() {
    
    memset(isUsed, false, sizeof(isUsed));
    vector <POS> v_s;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (nutrition[i][j]) 
                v_s.push_back({i, j});
        }
    }
    
    vector <POS> v_e;
    for (auto i : v_s) {
        int y = i.y;
        int x = i.x;
        
        int ny = ((y + dy[d - 1] * p) + n) % n;
        int nx = ((x + dx[d - 1] * p) + n) % n;
        
        map[ny][nx]++;
        v_e.push_back({ny, nx});
    }

    for (auto i : v_e) {
        int y = i.y;
        int x = i.x;
        isUsed[y][x] = true;
        
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            int k = 2 * j + 1;
            int ny = y + dy[k];
            int nx = x + dx[k];
            
            if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                continue;
            if (map[ny][nx] >= 1)
                cnt++;
        }
        map[y][x] += cnt;
    }
    
    memset(nutrition, false, sizeof(nutrition));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] >= 2 && !isUsed[i][j]) {
                map[i][j] -= 2;
                nutrition[i][j] = true;
            }
        }
    }
}

int main() {
    
    fasio;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
        }
    }
    for (int i = n - 2; i < n; ++i) {
        for (int j = 0; j < 2; ++j)
            nutrition[i][j] = true;
    }
    
    for (int i = 0; i < m; ++i) {
        cin >> d >> p;
        getNutri();
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) 
            ans += map[i][j];
    }
    
    cout << ans << '\n';
    
    return 0;
}