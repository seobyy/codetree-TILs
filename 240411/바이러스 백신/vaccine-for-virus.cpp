#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 50
#define INF 2'147'000'000
using namespace std;

struct POS { int y, x; };
struct POS2 { int elapsed_time; int y, x; };

// 상 하 좌 우 
const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int N, M;
int ans = INF;
int Map[MAX_N + 5][MAX_N + 5];
bool visited[MAX_N + 5][MAX_N + 5];

int target[15];
vector <POS> hospital;

void input() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> Map[i][j];
            if (Map[i][j] == 2) hospital.push_back({i, j});
        }
    }
}

void bfs() {
    
    memset(visited, false, sizeof(visited));
    queue <POS2> q;
    
    for (int i = 0; i < M; ++i) {
        int y = hospital[target[i]].y; int x = hospital[target[i]].x;
        q.push({0, y, x});
        visited[y][x] = true;
    }
    
    int max_t = 0;
    
    while (!q.empty()) {
        int et = q.front().elapsed_time;
        int y = q.front().y;
        int x = q.front().x;
        q.pop();
        
        max_t = max(max_t, et);
        
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            
            if (ny < 0 || ny >= N || nx < 0 || nx >= N)
                continue;
            if (visited[ny][nx])
                continue;
            
            if (!Map[ny][nx]) {
                visited[ny][nx] = true;
                q.push({et + 1, ny, nx});
            }
        }
    }
    
    bool can_bfs = true;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!Map[i][j] && !visited[i][j]) 
                can_bfs = false;
        }
    }
    
    if (can_bfs) ans = min(ans, max_t);
    
}

void sel_hospital(int index, int cnt) {
    if (cnt == M) {
        bfs();
        return;
    }
    
    for (int i = index; i < hospital.size(); ++i) {
        target[cnt] = i;
        sel_hospital(i + 1, cnt + 1);
    }
}

void solve() {
    sel_hospital(0, 0);
}

void output() {
    if (ans == INF) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main() {
    
    fastio;
    input();
    solve();
    output();
    
    return 0;
}