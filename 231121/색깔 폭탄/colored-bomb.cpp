#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 20
using namespace std;

typedef pair<int, int> pii;

struct POS { int area; int redCnt; int y, x; };
struct cmp {
    bool operator()(POS a, POS b) {
        if (a.area == b.area) {
            if (a.redCnt == b.redCnt) {
                if (a.y == b.y)
                    return a.x > b.x;
                return a.y < b.y;
            }
            return a.redCnt > b.redCnt;
        }
        return a.area < b.area;
    }
};

int n, m;
int score;
int cnt, rCnt;
int maxY, minX;
int map[MAX_N + 5][MAX_N + 5];
bool visited[MAX_N + 5][MAX_N + 5];
vector <pii> red;

const int dy[4] = { -1, 0, 1, 0 };
const int dx[4] = { 0, 1, 0, -1 };

void resetRed() {
    for (auto i : red)
        visited[i.first][i.second] = false;
}

void dfs(int y, int x, int val) {

    visited[y][x] = true;

    if (map[y][x] == val) {
        if (y > maxY) {
            maxY = y; minX = x;
        }
        else if (y == maxY) {
            if (x < minX)
                minX = x;
        }
    }

    for (int i = 0; i < 4; ++i) {

        int ny = y + dy[i];
        int nx = x + dx[i];

        if (ny < 0 || ny >= n || nx < 0 || nx >= n)
            continue;
        if (visited[ny][nx])
            continue;

        if (!map[ny][nx]) {
            cnt++; rCnt++;
            visited[ny][nx] = true;
            dfs(ny, nx, val);
        }
        else if (map[ny][nx] == val) {
            cnt++;
            visited[ny][nx] = true;
            dfs(ny, nx, val);
        }

    }
}

void dfs2(int y, int x, int val) {

    map[y][x] = -2;
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (ny < 0 || ny >= n || nx < 0 || nx >= n)
            continue;

        if (!map[ny][nx] || map[ny][nx] == val)
            dfs2(ny, nx, val);

    }
}

void gravity() {
    for (int j = 0; j < n; ++j) {
        for (int i = n - 1; i >= 0; --i) {
            if (map[i][j] == -2 || map[i][j] == -1)
                continue;
            int last = i;
            for (int k = i + 1; k < n; ++k) {
                if (map[k][j] != -2)
                    break;
                last = k;
            }
            if (last == i)
                continue;
            map[last][j] = map[i][j];
            map[i][j] = -2;
        }
    }
}

void turn() {
    int tmp[MAX_N + 5][MAX_N + 5];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tmp[n - 1 - j][i] = map[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            map[i][j] = tmp[i][j];
        }
    }
}

void solve() {

    while (1) {
        priority_queue <POS, vector<POS>, cmp> pq;
        memset(visited, false, sizeof(visited));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (map[i][j] != -1 && map[i][j] != 0 && map[i][j] != -2 && !visited[i][j]) {
                    cnt = 1; rCnt = 0;
                    maxY = -1; minX = 21;
                    resetRed();
                    dfs(i, j, map[i][j]);
                    if (cnt >= 2)
                        pq.push({ cnt, rCnt, maxY, minX });
                }
            }
        }
        if (pq.empty())
            break;

        int a = pq.top().area;
        int Y = pq.top().y; int X = pq.top().x;
        dfs2(Y, X, map[Y][X]);

        gravity();
        turn();
        gravity();

        score += a * a;
    }
}

int main() {

    fastio;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
            if (!map[i][j])
                red.push_back({ i, j });
        }
    }

    solve();

    cout << score << '\n';

    return 0;
}