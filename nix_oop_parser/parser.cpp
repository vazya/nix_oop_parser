#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Token {
public:
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
};

class Token_stream {
private:
	bool full;
	Token buffer;

public:
	Token_stream() : full(false), buffer(0) {}
	Token get() {
		if (full) {
			full = false;
			return buffer;
		}
		char ch;
		cin >> noskipws >> ch;
		switch (ch) {
		case '\n': case ' ':
		case '(': case ')': case '+': case '-': case '*': case '/': case '^':
			return Token(ch);
		case '.': case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': {
			cin.putback(ch);
			double val;
			cin >> val;
			return Token('8', val);
		}
		}
	}
	void putback(Token t) {
		buffer = t;
		full = true;
	}
};

Token_stream ts;
double fifth_expression();
double fourth_expression();
double third_expression();
double second_expression();

// + -
double fifth_expression() {
	double left = fourth_expression();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case ' ':
			t = ts.get();
			break;
		case '+':
			left += fourth_expression();
			t = ts.get();
			break;
		case '-':
			left -= fourth_expression();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

// * /
double fourth_expression() {
	double left = third_expression();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case ' ':
			t = ts.get();
			break;
		case '*':
			left *= third_expression();
			t = ts.get();
			break;
		case '/':
			left /= third_expression();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

// ^
double third_expression() {
	double left = second_expression();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case ' ':
			t = ts.get();
			break;
		case '^':
			left = pow(left, second_expression());
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

// - ()
double second_expression() {
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case ' ':
			t = ts.get();
			break;
		case '(':
		{
			double d = fifth_expression();
			t = ts.get();
			return d;
		}
		case '8':
			return t.value;
		case '-':
			return -second_expression();
		case '+':
			return second_expression();
		}
	}
}


int main() {
	cout << fifth_expression() << '\n';
	system("pause");
	return 0;
}
