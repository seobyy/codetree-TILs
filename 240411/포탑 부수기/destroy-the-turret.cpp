#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
using namespace std;

struct INFO {
    int attack;
    int recent;
    int y, x;
};

struct POS { int y, x; };
struct POS2 { int y, x; vector <POS> route; };

struct cmp {
    bool operator()(INFO a, INFO b) {
        if (a.attack == b.attack) {
            if (a.recent == b.recent) {
                if (a.y + a.x == b.y + b.x)
                    return a.x < b.x;
                return a.y + a.x < b.y + b.x;
            }
            return a.recent < b.recent;
        }
        return a.attack > b.attack;
    }
};

struct cmp2 {
    bool operator()(INFO a, INFO b) {
        if (a.attack == b.attack) {
            if (a.recent == b.recent) {
                if (a.y + a.x == b.y + b.x)
                    return a.x > b.x;
                return a.y + a.x > b.y + b.x;
            }
            return a.recent > b.recent;
        }
        return a.attack < b.attack; 
    }
};

// 우부터 시계방향 
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int N, M, K;
int turn;
int attack_power;
int attack_y, attack_x;
int target_y, target_x;
int ans;

int Map[15][15];
int recent_attack[15][15];
bool is_destroyed[15][15];
bool is_related[15][15];
bool visited[15][15];

vector <POS> v;

void print_progress() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j)
            cout << Map[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void init() {
    memset(is_related, false, sizeof(is_related));
    attack_power = N + M;
}

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> Map[i][j];
            if (!Map[i][j]) is_destroyed[i][j] = true;
        }
    }
}

void sel_attacker() {
    
    priority_queue <INFO, vector<INFO>, cmp> pq;
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (is_destroyed[i][j] || !Map[i][j])
                continue;
            pq.push({Map[i][j], recent_attack[i][j], i, j});
        }
    }
    
    attack_y = pq.top().y; attack_x = pq.top().x;
    
    Map[attack_y][attack_x] += N + M;
    attack_power = Map[attack_y][attack_x];
    recent_attack[attack_y][attack_x] = turn;
    is_related[attack_y][attack_x] = true;
}

bool can_laser() {
    
    memset(visited, false, sizeof(visited));
    visited[attack_y][attack_x] = true;
    
    vector <POS> tmp;
    
    queue <POS2> q;
    q.push({attack_y, attack_x, tmp});
    
    while (!q.empty()) {
        
        int y = q.front().y;
        int x = q.front().x;
        vector <POS> r = q.front().route;
        q.pop();
        
        if (y == target_y && x == target_x) {
            v = r;
            return true;
        }
        
        for (int d = 0; d < 8; d += 2) {
            int ny = (y + dy[d] + N) % N;
            if (!ny) ny = N;
            int nx = (x + dx[d] + M) % M;
            if (!nx) nx = M;
            
            if (visited[ny][nx])
                continue;
                
            if (Map[ny][nx]) {
                visited[ny][nx] = true;
                vector <POS> r2 = r;
                r2.push_back({ny, nx});
                q.push({ny, nx, r2});
            }
        }
    }

    return false;
}

void bomb_attack() {
    
    Map[target_y][target_x] -= attack_power;
    is_related[target_y][target_x] = true;
    
    int y = target_y; int x = target_x;
    for (int d = 0; d < 8; ++d) {
        int ny = (y + dy[d] + N) % N;
        if (!ny) ny = N;
        int nx = (x + dx[d] + M) % M;
        if (!nx) nx = M;
        
        if (!is_destroyed[ny][nx] && Map[ny][nx]) {
            Map[ny][nx] -= attack_power / 2;
            is_related[ny][nx] = true;
        }
    }
}

void attack() {
    // 1. 공격 대상자 선정 
    priority_queue <INFO, vector<INFO>, cmp2> pq;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (is_destroyed[i][j] || !Map[i][j])
                continue;
            if (i == attack_y && j == attack_x)
                continue;
            pq.push({Map[i][j], recent_attack[i][j], i, j});
        }
    }
    
    target_y = pq.top().y; target_x = pq.top().x;
    
    // 2. 레이저 공격 확인  

    // 2-1. 가능하면 레이저 어택 
    if (can_laser()) {
        for (auto i : v) {
            int y = i.y; int x = i.x;
            is_related[y][x] = true;
            
            if (y == target_y && x == target_x) 
                Map[y][x] -= attack_power;
            else
                Map[y][x] -= attack_power / 2;
        }
    }
    
    // 2-2. 불가 하면 포탄 공격  
    else 
        bomb_attack();
    
}

void top_destroy() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (Map[i][j] <= 0) {
                Map[i][j] = 0;
                is_destroyed[i][j] = true;
            }
        }
    }
}

void top_repair() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (is_destroyed[i][j] || is_related[i][j])
                continue;
            Map[i][j]++;
        }
    }
}

void solve() {
    while (++turn <= K) {
        //cout << "turn: " << turn << '\n';
        init();
        sel_attacker();
        
        //print_progress();
        
        attack();
        
        //print_progress();
        
        top_destroy();
        
        //print_progress();        
        
        top_repair();
        
        //print_progress();
    }
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j)
            ans = max(ans, Map[i][j]);
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