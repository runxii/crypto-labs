#include<iostream>
#include<string>

using namespace std;
#define TEXT_LENGTH 128

class shift_cipher {
private:
	int offset;	// integer for shift offset in the shift cipher algorithm
				// this can >0, means shift backwards; if <0, means shift forwards.
				// offset would mod 26 later, so it's not neccessary to consider that
public:
	shift_cipher() { offset = 0; }
	shift_cipher(int offset) { this->offset = offset; }
	char* shift_encrypt(char* plain_txt, int offset);		// funciton of encryption
	char* shift_decrypt(char* cipher_txt, int offset);		// function fo decryption
	void brute_force(char* cipher_txt);						// brute force attack simulate
};
char* shift_cipher::shift_encrypt(char* plain_txt, int offset){
	int shft = offset % 26;									// because offset might be very large, but the space
															// of shift cipher is only 26 (the length of alphabet) 
															// in this case. (english ver.)
	string plain_str = plain_txt;							// convert char* into string in order to get len
	int plain_len = plain_str.length();						//get the length of plain text
	char* cipher_txt = new char[plain_len];
	for (int i = 0; i < plain_len; i++)
	{ // we would use ascii code to represent a-zA-Z in this case
		if (plain_txt[i] >= 65 && plain_txt[i] <= 90) {		// ascii code A-Z
			int now_pos = (plain_txt[i] - 65 + shft) % 26 + 65;	// get the right ascii
			cipher_txt[i] = (char)now_pos;					// ascii to char
			continue;
		}
		if (plain_txt[i] >= 97 && plain_txt[i] <= 122) {	// ascii code a-z
			int now_pos = (plain_txt[i] - 97 + shft) % 26 + 97; // get the right ascii
			cipher_txt[i] = (char)now_pos;					// ascii to char
			continue;
		}
		cipher_txt[i] = plain_txt[i];						// not in the alphabet
	}
	cipher_txt[plain_len] = '\0';							// the end of chars
	return cipher_txt;
}
char* shift_cipher::shift_decrypt(char* cipher_txt, int offset) {
	int shft = offset % 26;
	string cipher_str = cipher_txt;							// convert char* into string in order to get len
	int cipher_len = cipher_str.length();					//get the length of plain text
	char* plain_txt = new char[cipher_len];
	for (int i = 0; i < cipher_len; i++)
	{ // we would use ascii code to represent a-zA-Z in this case
		if (cipher_txt[i] >= 65 && cipher_txt[i] <= 90) {	// ascii code A-Z
			int now_pos = (cipher_txt[i] - 65 + (26 - shft)) % 26 + 65;	// get the right ascii
			plain_txt[i] = (char)now_pos;					// ascii to char
			continue;
		}
		if (cipher_txt[i] >= 97 && cipher_txt[i] <= 122) {	// ascii code a-z
			int now_pos = (cipher_txt[i] - 97 + (26 - shft)) % 26 + 97;	// get the right ascii
			plain_txt[i] = (char)now_pos;					// ascii to char
			continue;
		}
		plain_txt[i] = cipher_txt[i];						// not in the alphabet
	}
	plain_txt[cipher_len] = '\0';							// the end of chars
	return plain_txt;										// decyption fiished
}
void shift_cipher::brute_force(char* cipher_txt) {
	cout << "|    Cipher text is: \'" << cipher_txt << "\'    |" << endl;
	for (int i = 0; i < 26; i++) {							// space size for alphabet: 26	
		cout << "|    Offset is set to " << i << "; then the plain text is: \' "
			<< shift_decrypt(cipher_txt, i) << "\'    |" << endl;
	}
	cout << "|    Brute force decryption finished.    |" << endl;
}

int main() {
	// choose to encypt or decrypt; three modes in general
	int mode;
	// first we need to write a plaintext, then choose a key
	cout << "mode:1 is for encryption;\nmode:2 is for decryption;\nmode:3 is for brute force attack"
		<< endl << "Please choose your mode." << endl;
	while (true) {
		cin >> mode;
		if (mode == 1) {									// encryption mode
			cout << "|    Please input your plaintext.    |" << endl;
			char* plain_txt = new char[TEXT_LENGTH];
			cin >> plain_txt;
			cout << "|    Please input your password, integer only.    |" << endl;
			int key;
			cin >> key;
			shift_cipher encryption;
			cout <<"|    Cipher text is: \'" <<
				encryption.shift_encrypt(plain_txt,key) << "\'    |" << endl;

		}
		if (mode == 2) {									// decryption mode
			cout << "|    Please input your ciphertext.    |" << endl;
			char* cipher_txt = new char[TEXT_LENGTH];
			cin >> cipher_txt;
			cout << "|    Please input your password, integer only.    |" << endl;
			int key; cin >> key;
			shift_cipher decryption;
			cout << "|    Plain text is: \'" <<
				decryption.shift_decrypt(cipher_txt, key) << "\'    |" << endl;
		}
		if (mode == 3) {									// brute force attack mode
			cout << "|    Please input your ciphertext.    |" << endl;
			char* cipher_txt = new char[TEXT_LENGTH];
			cin >> cipher_txt;
			cout << "|    Brute force decryption begins.    |" << endl;
			shift_cipher brute;
			brute.brute_force(cipher_txt);
		}
	}
	return 0;
}