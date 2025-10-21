#include <iostream>
#include <stack>
#include <cmath>
#include <string>
using namespace std;
#pragma GCC target("avx")
#pragma GCC optimize("O3")

struct Data
{
	struct number {
		int x;
		int min;
	};
	
	stack<number> right;
	stack<number> left;

	int insert_to_left(int x)
	{
		number num;
		num.x = x;
		num.min = left.empty() ? x : min(x, left.top().min);
		left.push(num);
		return CurrentMin();
	}

	int insert_to_right(int x)
	{
		number num;
		num.x = x;
		num.min = right.empty() ? x : min(x, right.top().min);
		right.push(num);
		return CurrentMin();
	}

	int left_pop()
	{
		if (left.empty())
			get_numb_from_right();
		left.pop();
		return CurrentMin();
	}

	int right_pop()
	{
		if (right.empty())
			get_numb_from_left();
		right.pop();
		return CurrentMin();
	}

	int CurrentMin()
	{
		if (left.empty() && right.empty()) {
			return -1;
		}
		else if (left.empty()) {
			return right.top().min;
		}
		else if (right.empty()) {
			return left.top().min;
		}
		else {
			return min(left.top().min, right.top().min);
		}
	}

	void get_numb_from_right()
	{
		stack<int> interim;
		int size = right.size() >> 1;
		for (int i = 0; i < size; i++)
		{
			interim.push(right.top().x);
			right.pop();
		}
		while (!right.empty())
		{
			insert_to_left(right.top().x);
			right.pop();
		}
		while (!interim.empty())
		{
			insert_to_right(interim.top());
			interim.pop();
		}
	}
	
	void get_numb_from_left()
	{
		stack<int> interim;
		int size = left.size() >> 1;
		for (int i = 0; i < size; i++)
		{
			interim.push(left.top().x);
			left.pop();
		}
		while (!left.empty())
		{
			insert_to_right(left.top().x);
			left.pop();
		}
		while (!interim.empty())
		{
			insert_to_left(interim.top());
			interim.pop();
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int q;
	cin >> q;
	Data data;
	string oper;
	int x;
	for (int i = 0; i < q; i++)
	{
		cin >> oper;
		if (oper == "+L" || oper == "+R")
		{
			cin >> x;
			if (oper == "+L")
				cout << data.insert_to_left(x) << "\n";
			else
				cout << data.insert_to_right(x) << "\n";
		}
		else
		{
			if (oper == "-L")
				cout << data.left_pop() << "\n";
			else 
				cout << data.right_pop() << "\n";
		}
	}
	return 0;
}