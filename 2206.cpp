#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 987654321

int n, m;
char map[1001][1001];
bool visited[1001][1001][2];

//»óÇÏÁÂ¿ì
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

int char_to_int(char ch) {
	return ch - '0';
}

bool inRange(int y, int x) {
	if (y < 1 || y > n || x < 1 || x > m) return false;
	else return true;
}

int bfs() {
	queue<pair<pair<int, int>, int>> q; //(y,x),flag
	visited[1][1][0] = true;
	q.push(make_pair(make_pair(1, 1), 0));
	int cnt = 0;
	
	while (!q.empty()) {
		int qsize = q.size();
		for (int k = 0; k < qsize; k ++) {
			pair<pair<int, int>, int> now = q.front();
			if (now.first.first == n && now.first.second == m) return cnt + 1;
			int flag = now.second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nextY = now.first.first + dy[i];
				int nextX = now.first.second + dx[i];
				if (!inRange(nextY, nextX)) continue;

				if (map[nextY][nextX] == '0' && !visited[nextY][nextX][flag]) {
					q.push(make_pair(make_pair(nextY, nextX), flag));
					visited[nextY][nextX][flag] = true;
				}
				else if (map[nextY][nextX] == '1' && flag == 0) {
					q.push(make_pair(make_pair(nextY, nextX), 1));
					visited[nextY][nextX][1] = true;
				}
			}
		}
		cnt++;
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> map[i][j];

	cout << bfs() << '\n';

	return 0;
}