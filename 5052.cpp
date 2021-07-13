#include <iostream>
#include <cstring>
using namespace std;

int char_to_index(char c) {
	return c - '0';
}

struct Trie {
	bool is_terminal; //������ ǥ��
	Trie* children[10]; //0~9�� �����̹Ƿ� 10���� �ڽ�

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
			if (children[index] == NULL) { //������� ������
				children[index] = new Trie();
			}
			children[index]->insert(key + 1); //���� ���ڿ� �ֱ�
		}
	}

	bool find(const char* key) {
		if (*key == '\0') return true;

		//�������� ���ξ ��ġ�ϸ� �� �ȴ� �Ͽ����Ƿ�
		//is_terminal�� keyŽ���� ������ �ʾ��� �� ������ false
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