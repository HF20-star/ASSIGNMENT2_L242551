#include<iostream>
using namespace std;

class Process {
public:
	string name;
	int priority;
	int duration;
	Process* next;

	Process(string n, int p, int d)
	{
		name = n;
		priority = p;
		duration = d;
		next = nullptr;
	}
};

