#include<iostream>
#include<map>

using namespace std;
#define ALPHABET_LEN 26
#define TEXT_LEN 1000

map<char, char> sub_list;

int len(char* text) {
	int res = 0;
	while (text[res] != '\0')
		res++;
	return res;
}

void generate_subtable(char* a) {
	for (int i = 0; i < ALPHABET_LEN; i++) {
		sub_list[(char)('a' + i)] = a[i];				// 将该字母g[i]放入替换列表当中
	}
}

void print_subtable()
{
	cout << "[The substitute table is: ]" << endl;
	for (int i = 0; i < ALPHABET_LEN; i++) {
		cout << (char)('a' + i) << " ";
	}
	cout << endl;
	for (int i = 0; i < ALPHABET_LEN; i++) {
		cout << sub_list[(char)('a' + i)] << " ";
	}
	cout << endl;
}

char* decrypt(char* c) {
	char* plain_txt = new char[TEXT_LEN];
	int cipher_len = len(c);
	for (int i = 0; i < cipher_len; i++) {
		c[i] = tolower(c[i]);
		if (c[i] < 97 || c[i]>122) {
			plain_txt[i] = c[i];
		}
		else {
			for (map<char, char>::iterator it = sub_list.begin(); it != sub_list.end(); it++) {
				if (it->second == c[i])
					plain_txt[i] = it->first;
			}
		}
	}
	plain_txt[cipher_len] = '\0';
	cout << "[The plain text is: ]\n" << plain_txt << endl;
	return plain_txt;
}

int main() {
	char* key = new char[ALPHABET_LEN];
	char* text = new char[TEXT_LEN];

	cout << "[Begin, input your cipher text.]" << endl;
	cin.get();
	cin.getline(text, TEXT_LEN);

	cout << "[Then input your password.]" << endl;
	while (true) {
		cin >> key;
		generate_subtable(key);
		print_subtable();
		char* plain = decrypt(text);
		cout << "[If not right, you can try a new password.]" << endl;
	}

	system("pause");
	return 0;
}