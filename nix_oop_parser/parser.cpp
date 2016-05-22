#include <iostream>
#include <cmath>
using namespace std;

class Token {
public:
	char symb;
	double value;
	Token(char c) : symb(c), value(0) {}
	Token(char c, double val) : symb(c), value(val) {}
};

class Processor {
private:
	bool flag;
	Token buff;

public:
	Processor() : flag(false), buff(0) {}
	Token get() {
		if (flag) {
			flag = false;
			return buff;
		}
		char c;
		cin >> noskipws >> c;
		switch (c) {
		case '\n': case ' ':
		case '(': case ')': case '+': case '-': case '*': case '/': case '^':
			return Token(c);
		case '.': case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': {
			cin.putback(c);
			double val;
			cin >> val;
			return Token('8', val);
		}
		}
	}
	void putback(Token token) {
		buff = token;
		flag = true;
	}
	double sum() {
		double left = mult();
		Token token = get();
		while (true) {
			switch (token.symb) {
			case ' ':
				token = get();
				break;
			case '+':
				left += mult();
				token = get();
				break;
			case '-':
				left -= mult();
				token = get();
				break;
			default:
				putback(token);
				return left;
			}
		}
	}
	double mult() {
		double left = power();
		Token token = get();
		while (true) {
			switch (token.symb) {
			case ' ':
				token = get();
				break;
			case '*':
				left *= power();
				token = get();
				break;
			case '/':
				left /= power();
				token = get();
				break;
			default:
				putback(token);
				return left;
			}
		}
	}
	double power() {
		double left = brackets();
		Token token = get();
		while (true) {
			switch (token.symb) {
			case ' ':
				token = get();
				break;
			case '^':
				left = pow(left, brackets());
				token = get();
				break;
			default:
				putback(token);
				return left;
			}
		}
	}
	double brackets() {
		Token token = get();
		while (true) {
			switch (token.symb) {
			case ' ':
				token = get();
				break;
			case '(':
			{
				double d = sum();
				token = get();
				return d;
			}
			case '8':
				return token.value;
			case '-':
				return -brackets();
			case '+':
				return brackets();
			}
		}
	}
	void process() {
		cout << sum() << '\n';
	}
};



int main() {
	Processor proc;
	proc.process();
	system("pause");
	return 0;
}
