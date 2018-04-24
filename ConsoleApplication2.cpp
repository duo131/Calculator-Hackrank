// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <map> //using unordered_map would be better cus order does not matter here
#include<iostream>
using namespace std;
map<string, int> ope_dic;//store operator wight 
						 //+ = 0, * = 1 , |=2, &=2
bool compareOperator(string a, string b) {//compare the operator weight
	int k = ope_dic[a];
	int j = ope_dic[b];
	return (k > j);
}
double cal(double a, double b, string s)
{
	if (s == "+")
		return a + b;
	else if (s == "*")
		return a*b;
	else if (s == "|")
		return min(a, b);
	else if (s == "&")
		return max(a, b);
	return 0;
}
float calculator(string input_str) {
	ope_dic["+"] = 0;
	ope_dic["*"] = 1;
	ope_dic["|"] = 2;
	ope_dic["&"] = 2;

	float res = 0;//might have mantissa
	stack<string> num_stack;
	stack<string> ope_stack;
	bool isNum = false;
	bool preCal = false;
	bool isEnd = false;
	for (int i = 0; i < input_str.size(); ++i)
	{
		//head of number
		if (((input_str[i] - '0') >= 0 && (input_str[i] - '0') <= 9 && isNum == false) || (input_str[i] == '-'))
		{
			string s(1, input_str[i]);
			num_stack.push(s);
			isNum = true;
			isEnd = false;
		}
		//number
		else if (((input_str[i] - '0') >= 0 && (input_str[i] - '0') <= 9 && isNum == true) || (input_str[i] == '.'))
		{
			string temp = num_stack.top();
			num_stack.pop();
			temp += input_str[i];
			num_stack.push(temp);
			isEnd = false;
		}
		//space
		else if (input_str[i] == ' ')
		{
			isEnd = true;
		}
		//operator
		else if ((input_str[i] == '+' || input_str[i] == '*' || input_str[i] == '&' || input_str[i] == '|') && !num_stack.empty())
		{
			string s(1, input_str[i]);
			isEnd = true;
			
			if (preCal&&isNum&&isEnd&&num_stack.size()>1&&(!compareOperator(s, ope_stack.top())))//if the former has higher priority
			{
				while (num_stack.size() > 1 && (!compareOperator(s, ope_stack.top())))
				{
					string s_pre = ope_stack.top();
					ope_stack.pop();
					double a = stod(num_stack.top());
					num_stack.pop();
					double b = stod(num_stack.top());
					num_stack.pop();
					num_stack.push(to_string(cal(a, b, s_pre)));
				}

			}

			if (ope_stack.empty())
			{
				ope_stack.push(s);
				if (ope_dic[ope_stack.top()] != 0)
				{
					preCal = true;
				}
				else
				{
					preCal = false;
				}
			}
			else if (ope_dic[ope_stack.top()] == 2 || compareOperator(s, ope_stack.top()))
			{

				ope_stack.push(s);
				preCal = true;
			}
			else
			{
				ope_stack.push(s);
				preCal = false;

			}
			


			

			isNum = false;

		}
		else
		{
			return 0;
		}

	}
	//cal final value
	while ((num_stack.size()>1) && (!ope_stack.empty()))
	{
		string s = ope_stack.top();
		ope_stack.pop();
		double a = stod(num_stack.top());
		num_stack.pop();
		double b = stod(num_stack.top());
		num_stack.pop();
		num_stack.push(to_string(cal(a, b, s)));
	}
	res = stod(num_stack.top());
	return res;
}



int main()
{
	//cout<<calculator("15 +8 & 10 *-2 ") << endl;
	//cout << calculator("1 & 2 | 3 * 4 * 5 + 6")<<endl;
	//cout << calculator("1 & 2 | 3 * 4 * 5 + 61 & 2 | 3 * 4 * 5 + 6")<<endl;
	cout << calculator("3 * 4 * 2 + 3 & 2 * 2 * 2 | 5 + 6") << endl;//24+12+6
    return 0;
}

