#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;

string trans(const string &s) {
	map<char, short int> symtonum = { {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'(', 2}, {'[', 3}, {'{', 4} };
	string out;
	vector<char> stack;
	for (auto &x : s) {
		if (x >= '0' && x <= '9')
			out += x;
		else {
			if (stack.empty())
				stack.push_back(x);
			else if (symtonum[x] > symtonum[stack.back()])
				stack.push_back(x);
			else if (x == ')' || x == ']' || x == '}') {
				while (stack.back() != '(' && stack.back() != '[' && stack.back() != '{') {
					out += stack.back();
					stack.pop_back();
				}
				stack.pop_back();
			}
			else {
				while (symtonum[x] <= symtonum[stack.back()] && stack.back() != '(' && stack.back() != '[' && stack.back() != '{') {
					out += stack.back();
					stack.pop_back();
					if (stack.empty())
						break;
				}
				stack.push_back(x);
			}
		}
	}
	while (!stack.empty()){
		out += stack.back();
		stack.pop_back();
	}
	return out;
}

int culc(const string &s) {
	vector<int> stack;
	string out = trans(s);
	int a, b;
	for (auto &x : out) {
		if (x >= '0' && x <= '9')
			stack.push_back(x - '0');
		else {
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			switch (x)
			{
			case'+':
				stack.push_back(a + b);
				break;
			case'-':
				stack.push_back(a - b);
				break;
			case'*':
				stack.push_back(a * b);
				break;
			case'/':
				stack.push_back(a / b);
				break;
			default:
				break;
			}
		}
	}
	return stack.back();
}

int main()
{
	string s = "1+2*3+(4*5+6)*9";
	cout << culc(s) << endl;
	return 0;
}