#include<iostream>
#include<map>
#include<string>
#include<stdio.h>
using namespace std;
int get_length(char* text) {
	int i = 0;
	while (text[i] != '\0') {
		i++;
	}
	return i;
}
map<char, char> list;
int* a = new int[26];
int main() {
	char* text = new char[1000];
	for (int i = 0; i < 26; i++) {
		a[i] = 0;
	}
	cout << "输入密钥，如果密钥长度大于26位，则只取前26位" << endl;
	cin >> text;
	if (get_length(text) > 26) {
		text[26] = '\0';
	}
	//全部改为小写 去重
	int t = 0;
	for (int i = 0; i < get_length(text); i++) {
		text[i] = tolower(text[i]);
		if (text[i] < 97 || text[i] > 122) {
			continue;
		}
		if (a[(int)(text[i] - 'a')]) {
			continue;
		}
		else {
			a[(int)(text[i] - 'a')] = 1;
			list[(char)('a' + t)] = text[i];
			t++;
		}
	}
	for (int j = t; j < 26; j++) {
		char temp = '\0';
		for (int k = 0; k < 26; k++) {
			if (a[k] == 0) {
				a[k] = 1;
				temp = (char)('a' + k);
				break;
			}
		}
		list[(char)('a' + j)] = temp;
	}
	cout << endl << "替换表为：  " << endl;
	for (int j = 0; j < 26; j++) {
		cout << (char)('a' + j) << " ";
	}
	cout << endl;
	for (int j = 0; j < 26; j++) {
		cout << list[(char)('a' + j)] << " ";
	}
	cout << endl;
	char* plaintext = new char[1000];
	char* ciphertext = new char[1000];
	cout << "您的密文为：  " << endl;
	cin.get();
	cin.getline(ciphertext, 1000);
	int len = get_length(ciphertext);
	for (int j = 0; j < len; j++) {
		ciphertext[j] = tolower(ciphertext[j]);
		if (ciphertext[j] < 97 || ciphertext[j] > 122) {
			plaintext[j] = ciphertext[j];
		}
		else {
			for (std::map<char, char>::iterator it = list.begin(); it != list.end(); it++) {
				if (it->second == ciphertext[j]) {
					plaintext[j] = it->first;
				}
			}
		}
	}
	plaintext[len] = '\0';
	cout << "您的明文为：  " << plaintext << endl;
	return 0;
}

//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<map>
//
//using namespace std;
//#define TEXT_LEN 512
//#define ALPHABET_LEN 26
////#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
//#define PLAIN "theseviolentdelights"
//
//#pragma warning(disable:4996)
//
//class substitute_cipher {
//public:
//	map<char, char> sub_table;
//	substitute_cipher() {};
//	char* substitute_table(char* generate);// funciton of generating table
//	char* substitute_encrypt(char* plain_txt, char* key); // function of encryption
//	char* substitute_decrypt(char* cipher_txt, char* key);// function fo decryption
//};
//
//char* substitute_cipher::substitute_table(char* g) {
//	char* key_res = new char[ALPHABET_LEN];
//	string key;
//	string generate = g;
//	sort(generate.begin(), generate.end()); // sort this string bc unique only works when the same chars are neighbors
//	generate.erase(unique(generate.begin(), generate.end()), generate.end()); // erase the repeated chars
//	string record = generate;
//	for (int j = 0; j < 26; j++) { // restore the orders of original char*
//		for (int i = 0; i < generate.length(); i++) {
//			if (g[j] == generate[i]) {
//				string tmp(1, generate[i]); // convert char to string
//				key += tmp;
//				generate[i] = NULL;
//			}
//		}
//	}
//	strcpy(key_res, key.c_str());
//	return key_res;
//}
//
//char* substitute_cipher::substitute_encrypt(char* p, char* k) {
//	char* cipher_txt = new char[TEXT_LEN];
//	return cipher_txt;
//}
//
//char* substitute_cipher::substitute_decrypt(char* c, char* k) {
//	char* plain_txt = new char[TEXT_LEN];
//	return plain_txt;
//}
//
//int main()
//{
//	while (true) {
//		cout << "begin" << endl;
//		char plain[TEXT_LEN];
//		strcpy_s(plain, PLAIN);
//		char* key = new char[TEXT_LEN];
//		cin >> key;
//		substitute_cipher test;
//		cout << "res: " << test.substitute_table(key)<<endl;
//	}
//	return 0;
//}