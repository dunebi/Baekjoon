#include <iostream>
#include <cstring>
using namespace std;

int arr[101][101]; //[y][x]
bool visited[101][101];
int N;

typedef struct Point {
	int y, x;
}Point;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

bool isRange(int y, int x) {
	if (y <= 0 || y > N || x <= 0 || x > N) return false;
	else return true;
}

void dfs(Point now, int rain) {
	int ny = now.y;
	int nx = now.x;

	visited[ny][nx] = true;

	Point temp;
	for (int i = 0; i < 4; i++) {
		int nexty = ny + dy[i];
		int nextx = nx + dx[i];
		if (isRange(nexty, nextx) == false) continue;
		if (arr[nexty][nextx] <= rain) continue;
		if (visited[nexty][nextx] == true) continue;

		temp.y = nexty;
		temp.x = nextx;
		dfs(temp, rain);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N;

	int max = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			cin >> arr[i][j];
			if (arr[i][j] > max) max = arr[i][j];
		}

	Point start;
	int ans = 0;
	for (int rain = 0; rain <= max; rain++) {
		memset(visited, false, sizeof(visited));
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (visited[i][j] == true || arr[i][j] <= rain) continue;
				start.y = i;
				start.x = j;
				dfs(start, rain);
				cnt++;
			}
		}
		if (cnt > ans) ans = cnt;
	}

	cout << ans << '\n';

	return 0;
}