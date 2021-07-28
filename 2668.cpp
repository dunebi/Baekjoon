#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N;
int arr[101];
bool visited[101];

bool dfs(int start, int idx, bool flag) {
	visited[idx] = true;
	int next_idx = arr[idx];
	
	if (next_idx == start && flag == false) return true;
	if (flag == true && next_idx == start) return true;

	if (visited[next_idx] == false)
		return dfs(start, next_idx, false);

	return false;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}

	vector<int> ans;

	for (int i = 1; i <= N; i++) {
		memset(visited, false, sizeof(visited));
		if (dfs(i, i, true) == true) ans.push_back(i);
	}

	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << '\n';

	return 0;
}