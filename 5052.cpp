#include <iostream>
#include <cstring>
using namespace std;

int char_to_index(char c) {
	return c - '0';
}

struct Trie {
	bool is_terminal; //끝임을 표시
	Trie* children[10]; //0~9의 숫자이므로 10개의 자식

	Trie() : is_terminal(false) { //Constructor
		memset(children, NULL, sizeof(children));
	}

	~Trie() {
		for (int i = 0; i < 10; i++)
			if (children[i] != NULL) delete children[i];
	}

	void insert(const char* key) {
		if (*key == '\0')
			is_terminal = true;
		else {
			int index = char_to_index(*key);
			if (children[index] == NULL) { //비었으면 노드생성
				children[index] = new Trie();
			}
			children[index]->insert(key + 1); //다음 문자열 넣기
		}
	}

	bool find(const char* key) {
		if (*key == '\0') return true;

		//문제에서 접두어가 일치하면 안 된다 하였으므로
		//is_terminal이 key탐색이 끝나지 않았을 때 나오면 false
		if (is_terminal) return false;

		int index = char_to_index(*key);
		return children[index]->find(key + 1);
	}

};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t, n;
	char phone_nums[10000][11];
	cin >> t;

	for (int i = 0; i < t; i++) {
		cin >> n;
		Trie* root = new Trie();
		bool goodList = true;
		for (int j = 0; j < n; j++) {
			char num[11];
			cin >> phone_nums[j];
			root->insert(phone_nums[j]);
		}

		for (int j = 0; j < n; j++) {
			if (root->find(phone_nums[j]) == false) {
				goodList = false;
				break;
			}
		}

		delete root;
		if (goodList) cout << "YES" << '\n';
		else cout << "NO" << '\n';
	}


	return 0;
}