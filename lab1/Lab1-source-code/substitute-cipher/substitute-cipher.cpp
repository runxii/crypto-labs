#include<iostream>
#include<string>
#include<map>

using namespace std;
#define TEXT_LEN 512
#define ALPHABET_LEN 26

#pragma warning(disable:4996)

class substitute_cipher {
private:
	map<char, char> sub_list;
	int* alphabet = new int[26];
public:
	substitute_cipher() { 
		for (int i = 0; i < ALPHABET_LEN; i++) 
		alphabet[i] = 0; 
	};
	int len(char* text);									// function of getting length
	void substitute_table(char* generate);					// funciton of generating table
	void print_subtable();									// function of printing the table
	char* substitute_encrypt(char* plain_txt);				// function of encryption
	char* substitute_decrypt(char* cipher_txt);				// function of decryption
};

int substitute_cipher::len(char* text)
{
	int res = 0;
	while (text[res] != '\0') {res++;}						// 未遇到终止符之前，全部都记为字符串，长度++
	return res;
}

void substitute_cipher::substitute_table(char* g) {			// 生成替换表
	if (len(g) > ALPHABET_LEN) {							// 如果输入字符串>26，只取前26位
		g[ALPHABET_LEN] = '\0';
	}
	int pos = 0;											// 现在替换列表中的位置指针
	for (int i = 0; i < len(g); i++) {
		g[i] = tolower(g[i]);								// 全部改为小写字母
		if (g[i] < 97 || g[i]>122)							// 不是小写字母的char不做处理
		{
			continue;
		}
		if (alphabet[(int)(g[i] - 'a')]) {					// 已被替换，继续循环
			continue;
		}
		else {
			alphabet[(int)(g[i] - 'a')] = 1;				// 设置该字母已被使用
			sub_list[(char)('a' + pos)] = g[i];				// 将该字母g[i]放入替换列表当中
			pos++;
		}
	}
	for (int j = pos; j < ALPHABET_LEN; j++) {				// 从现在的位置指针处开始补全替换表
		char first_unused = '\0';
		for (int k = 0; k < ALPHABET_LEN; k++) {
			if (alphabet[k] == 0) {
				alphabet[k] = 1;
				first_unused = (char)('a' + k);				// 按字母表顺序，第一个未被使用过的字母
				break;
			}
		}
		sub_list[(char)('a' + j)] = first_unused;			// 把找到的字母按顺序放入替换列表中
	}
}

void substitute_cipher::print_subtable()
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

char* substitute_cipher::substitute_encrypt(char* p) {
	cout << "[SUBSTITUTE ENCRYPTION BEGINS]\n" << "[The plain text is: ]\n" << p << endl;
	char* cipher_txt = new char[TEXT_LEN];
	int plain_len = len(p);
	for (int i = 0; i < plain_len; i++) {
		p[i] = tolower(p[i]);
		if (p[i] < 97 || p[i]>122) {
			cipher_txt[i] = p[i];
		}
		else {
			for (map<char, char>::iterator it = sub_list.begin(); it != sub_list.end(); it++) {
				if (it->first == p[i])
					cipher_txt[i] = it->second;
			}
		}
	}
	cipher_txt[plain_len] = '\0';
	cout << "[The cipher text is: ]\n" << cipher_txt << endl;
	return cipher_txt;
}

char* substitute_cipher::substitute_decrypt(char* c) {
	cout << "[SUBSTITUTE DECRYPTION BEGINS]\n" << "[The cipher text is: ]\n" << c << endl;
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
	cout << "[The plain text is: ]\n" << plain_txt<< endl;
	return plain_txt;
}

int main()
{
	cout << "[Begin, input your password.]" << endl;
	substitute_cipher test; 
	char* plain=new char[TEXT_LEN];
	char* key = new char[TEXT_LEN];
	char* cipher = new char[TEXT_LEN];
	cin >> key;
	test.substitute_table(key);
	test.print_subtable();
		
	cout << "[Then input your plain text.]" << endl;
	cin.get();
	cin.getline(plain, TEXT_LEN);
	test.substitute_encrypt(plain);

	cout << "[Then input your cipher text.]" << endl;
	cin.get();
	cin.getline(cipher, TEXT_LEN);
	test.substitute_decrypt(cipher);
	system("pause");
	return 0;
}