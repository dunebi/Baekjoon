#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

int n, m;

//왼쪽 원소부터 반시계로 돌리기
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int scoreboard[9] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };
bool visited[4][4];

int char_to_int(char c) {
	return (int)c - 'A'; //자식 노드의 index를 추출할 때 사용
}

struct Trie {
	bool isTerminal;
	Trie* children[26]; //알파벳 대문자 26개인 점을 이용

	Trie() {
		memset(children, NULL, sizeof(children));
		this->isTerminal = false;
	}
	~Trie() {
		for (int i = 0; i < 26; i++)
			if (children[i] != NULL) delete children[i];
	}

	void insert(const char* key) {
		if (*key == '\0') this->isTerminal = true;
		else {
			int index = char_to_int(*key);
			if (children[index] == NULL) {
				children[index] = new Trie();
			}
			children[index]->insert(key + 1);
		}
	}

	bool canSearch(const char* key) {
		if (*key == '\0') return true;
		int index = char_to_int(*key);

		if (children[index] != NULL) return children[index]->canSearch(key + 1);
		else return false;
	}


	bool check_Terminal(const char* key) {
		if (this->isTerminal == true && *key == NULL) return true;
		if (this->isTerminal == false && *key == NULL) return false;

		int index = char_to_int(*key);
		if (children[index] != NULL) return children[index]->check_Terminal(key + 1);
		else return false;
	}
};

bool inRange(int y, int x) {
	if (y < 0 || y >= 4 || x < 0 || x >= 4) return false;
	else return true;
}

void dfs(Trie* root, string* board, int y, int x, map<string, int>& found, string now) {
	string temp = now;
	temp.push_back(board[y][x]);
	if (!root->canSearch(temp.c_str()) || temp.size() > 8) return;
	if (root->check_Terminal(temp.c_str())) {
		found[temp] = 1;
	}

	visited[y][x] = true;

	for (int i = 0; i < 8; i++) {
		int nextY = y + dy[i];
		int nextX = x + dx[i];
		if (!inRange(nextY, nextX)) continue;
		if (visited[nextY][nextX] == true) continue;
		dfs(root, board, nextY, nextX, found, temp);
	}

	visited[y][x] = false;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	Trie* words_root = new Trie();
	cin >> n;
	for (int i = 0; i < n; i++) {
		char temp[10];
		cin >> temp;

		words_root->insert(temp);
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		string board[4];
		for (int j = 0; j < 4; j++) {
			cin >> board[j];
		}
		map<string, int> found;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				dfs(words_root, board, i, j, found, "");
			}
		}

		int cnt = 0, score = 0;
		string longest = "";
		for (auto it = found.begin(); it != found.end(); it++) {
			cnt++;
			if (longest.size() < it->first.size()) longest = it->first;
			score += scoreboard[it->first.size()];
		}
		cout << score << ' ' << longest << ' ' << cnt << '\n';
	}

	return 0;
}