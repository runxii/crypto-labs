#include<iostream>
#include<string>

using namespace std;
#define TEXT_LEN 1000
#define ALPHABET_LEN 26

#pragma warning(disable:4996)
using namespace std;
int len(char* text) {
	int res = 0;
	while (text[res] != '\0')
		res++;
	return res;
}
class letter { // 将每一个字母看作一个类
private:
	int frequnce;	// 出现的次数
	char letter_old;//
	char letter_new;
public:
	letter() {frequnce = 0;letter_old = '\0';letter_new = '\0';} // 构造，初始化，空的
	letter(char a) {frequnce = 0;letter_old = a;letter_new = '\0';} // 带参数的构造
	void set_new(char a) {letter_new = a; }
	void set_old(char a) {letter_old = a;}	//之前的字母
	void set_frequnce(int no) {frequnce = no;}// 手动设置字母的出现的次数
	void frequnce_plus() {frequnce++;}// 出现次数+1
	char get_old() {return letter_old;}
	char get_new() {return letter_new;}
	int get_frequnce() {return frequnce;}
};

void letter_sort(letter* a) {
	for (int i = 1; i < ALPHABET_LEN; i++) { // 使用双重循环，对字母表进行排序，降序;其实就是swap排序
		for (int j = 0; j < ALPHABET_LEN - i; j++) {
			if (a[j].get_frequnce() < a[j + 1].get_frequnce()) { // 如果后一个字母出现的次数更多
				char tmp1 = a[j].get_old();
				a[j].set_old(a[j + 1].get_old()); // 就把前一个位置的old字设为后一个位置的old字
				a[j + 1].set_old(tmp1); // 实现位置对换
				int tmp2 = a[j].get_frequnce(); // 同样的，两者出现的次数frequnce也要对换
				a[j].set_frequnce(a[j + 1].get_frequnce());
				a[j + 1].set_frequnce(tmp2);
			}
		}
		
	}
}

letter* letter_ratio (char* text) {
	int length = len(text);
	letter* text_alphabet=new letter[ALPHABET_LEN];
	for (int i = 0; i < 26; i++) {
		text_alphabet[i].set_old('a' + i); // 先初始化为顺序字母表
	}
	double sum = 0;	// 总的字母个数
	for (int i = 0; i < length; i++) { // 只记入大小写字母
		if (text[i] >= 65 && text[i] <= 90) {
			text_alphabet[(int)(text[i] - 'A')].frequnce_plus();// 主要完成对每个字母类frequence的初始化
			sum++;
		}
		if (text[i] >= 97 && text[i] <= 122) {
			text_alphabet[(int)(text[i] - 'a')].frequnce_plus();// 主要完成对每个字母类frequence的初始化
			sum++;
		}
	}
	cout << "[The occurence ratios of each letter are: ]" << endl;
	for (int i = 0; i < ALPHABET_LEN; i++) {
		text_alphabet[i].set_old('a' + i);
		cout << (char)('a' + i) << "     " << (double)(text_alphabet[i].get_frequnce() / sum) << endl;
	}
	return text_alphabet;
}

int main() {
	char sub_list[ALPHABET_LEN+1];
	memset(sub_list, '\0', ALPHABET_LEN + 1);
	
	cout << "[Please input your text. ]" << endl;
	char* text = new char[TEXT_LEN];
	cin.getline(text, TEXT_LEN); // 使用getline主要是text中可能会出现空格
	letter* text_alphabet = letter_ratio(text);

	char real_freq[ALPHABET_LEN] = { 'e','t','o','i','a','n','s','r','h','l','d','u','c','m','p','y','f','g','w','b','v','k','x','j','q','z' };
	letter_sort(text_alphabet);
	for (int i = 0; i < ALPHABET_LEN; i++) {
		text_alphabet[i].set_new(real_freq[i]);

	}
	for (int j = 0; j < ALPHABET_LEN; j++) {
		sub_list[text_alphabet[j].get_new() - 'a'] = text_alphabet[j].get_old();
	}
	sub_list[ALPHABET_LEN] = '\0';
	cout << "[The substitute list result is: ] "<<endl;
	for (int i = 0; i < ALPHABET_LEN; i++) {
		cout << sub_list[i]<<"  ";
	}
	cout << endl;

	system("pause");
	return 0;
}