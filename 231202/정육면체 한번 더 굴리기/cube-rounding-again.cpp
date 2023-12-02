#include <iostream>
#include <queue>
#include <memory.h>
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define MAX_N 20
using namespace std;

struct POS { int y, x; };

int n, m;
int curY, curX;
int dir;
int score;
int dice[7];    // 1.아래 2.북 3.동 4.서 5.남 6.위
int map[MAX_N + 5][MAX_N + 5];
bool visited[MAX_N + 5][MAX_N + 5];

const int dy[4] = { 0, 1, 0, -1 };
const int dx[4] = { 1, 0, -1, 0 };

int adjCnt(int sy, int sx) {

    int cnt = 0;
    memset(visited, false, sizeof(visited));
    visited[sy][sx] = true;
    int val = map[sy][sx];
    queue <POS> q;
    q.push({ sy, sx });

    while (!q.empty()) {

        int y = q.front().y;
        int x = q.front().x;
        q.pop();
        cnt++;

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                continue;

            if (map[ny][nx] == val && !visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({ ny, nx });
            }
        }
    }

    return cnt;
}

void Move() {

    int tmp = dice[1];
    switch (dir) {
    case 0:
        dice[1] = dice[3];
        dice[3] = dice[6];
        dice[6] = dice[4];
        dice[4] = tmp;
        break;

    case 1:
        dice[1] = dice[5];
        dice[5] = dice[6];
        dice[6] = dice[2];
        dice[2] = tmp;
        break;

    case 2:
        dice[1] = dice[4];
        dice[4] = dice[6];
        dice[6] = dice[3];
        dice[3] = tmp;
        break;

    case 3:
        dice[1] = dice[2];
        dice[2] = dice[6];
        dice[6] = dice[5];
        dice[5] = tmp;
        break;

    default: break;
    }
}

void rollTheDice() {

    if (curY + dy[dir] < 0 || curY + dy[dir] >= n ||
        curX + dx[dir] < 0 || curX + dx[dir] >= n)
        dir = (dir + 2) % 4;

    curY += dy[dir]; curX += dx[dir];
    Move();

    score += map[curY][curX] * adjCnt(curY, curX);

    if (dice[1] > map[curY][curX])
        dir = (dir + 1) % 4;

    else if (dice[1] < map[curY][curX])
        dir = (dir + 3) % 4;

}

int main() {

    fastio;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
        }
    }

    dice[1] = 6; dice[2] = 5; dice[3] = 3;
    dice[4] = 4; dice[5] = 2; dice[6] = 1;

    for (int i = 0; i < m; ++i) {
        rollTheDice();
    }

    cout << score << '\n';

    return 0;
}