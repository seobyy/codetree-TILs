#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_M 30
using namespace std;

struct POS { int dis; int y, x; };
struct POS2 { int dis; int dir; };
struct cmp {
    bool operator()(POS a, POS b) {
        if (a.dis == b.dis) {
            if (a.y == b.y)
                return a.x > b.x;
            return a.y > b.y;
        }
        return a.dis > b.dis;
    }
};
struct cmp2 {
    bool operator()(POS2 a, POS2 b) {
        if (a.dis == b.dis)
            return a.dir > b.dir;
        return a.dis > b.dis;
    }
};

POS P[MAX_M + 5];
POS M[MAX_M + 5];

// 상 좌 우 하   
const int dy[4] = {-1, 0, 0, 1};
const int dx[4] = {0, -1, 1, 0};

int n, m;
int turn;
int ans;
int Map[20][20];
bool blocked[20][20];
bool visited[20][20];
bool finished[MAX_M + 5];

void print_progress() {
    for (int i = 1; i <= m; ++i) {
        cout << i << ": " << M[i].y << ' ' << M[i].x << '\n'; 
    }
    cout << '\n';
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> Map[i][j];
        }
    }
    for (int i = 1; i <= m; ++i) {
        int y, x; cin >> y >> x;
        P[i] = { 0, y, x };
    }
}

int bfs(int y, int x, int target) {
    
    int res = 0;
    
    memset(visited, false, sizeof(visited));
    queue <POS> q;
    q.push({0, y, x});
    
    while (!q.empty()) {
        int d = q.front().dis;
        int sy = q.front().y;
        int sx = q.front().x;
        q.pop();
        
        if (sy == P[target].y && sx == P[target].x) {
            res = d;
            break;
        }
        
        for (int i = 0; i < 4; ++i) {
            int ny = sy + dy[i];
            int nx = sx + dx[i];
            if (ny < 1 || ny > n || nx < 1 || nx > n)
                continue;
            if (blocked[ny][nx] || visited[ny][nx])
                continue;
            
            visited[ny][nx] = true;
            q.push({d + 1, ny, nx});
        }
    }
    
    return res;
}

void people_move() {
    
    // 1. 이동
    
    vector <POS> v;
    
    for (int i = 1; i <= m; ++i) {
        if (!M[i].y && !M[i].x) continue;
        if (finished[i]) continue;
        
        priority_queue <POS2, vector<POS2>, cmp2> pq;
        for (int d = 0; d < 4; ++d) {
            
            int ny = M[i].y + dy[d];
            int nx = M[i].x + dx[d];
            
            if (ny < 1 || ny > n || nx < 1 || nx > n)
                continue;
            if (blocked[ny][nx])
                continue;
            
            int dis = bfs(ny, nx, i);
            pq.push({dis, d});
        }
        
        int dir = pq.top().dir;
        //cout << i << ' ' << dir << '\n';
        
        int ny = M[i].y + dy[dir];
        int nx = M[i].x + dx[dir];
        
        M[i].y = ny; M[i].x = nx;
        if (Map[ny][nx])
            v.push_back({0, ny, nx});
        else if (ny == P[i].y && nx == P[i].x)
            finished[i] = true;
    }
    
    // 2. 갈수 없는 곳 체크 
    for (auto i : v) {
        blocked[i.y][i.x] = true;
    }
    
}

void basecamp_move() {
    
    memset(visited, false, sizeof(visited));
    priority_queue <POS, vector<POS>, cmp> pq;
    pq.push({0, P[turn].y, P[turn].x});
    
    while (!pq.empty()) {
        
        int d = pq.top().dis;
        int y = pq.top().y;
        int x = pq.top().x;
        pq.pop();
        
        if (Map[y][x]) {
            blocked[y][x] = true;
            M[turn].y = y; M[turn].x = x;
            break;
        }
        
        for (int i = 0; i < 4; ++i) {
            
            int ny = y + dy[i];
            int nx = x + dx[i];
            
            if (ny < 1 || ny > n || nx < 1 || nx > n)
                continue;
            if (visited[ny][nx] || blocked[ny][nx])
                continue;
                
            visited[ny][nx] = true;
            pq.push({d + 1, ny, nx});
        }
    }
}

bool can_iter() {
    for (int i = 1; i <= m; ++i) {
        if (!finished[i])
            return true;
    }
    return false;
}


void solve() {
    while (++turn) {
        people_move();
        //print_progress();
        basecamp_move();
        //print_progress();
        
        // 종료 조건 확인
        if (!can_iter())
            break;
    }
    ans = turn;
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