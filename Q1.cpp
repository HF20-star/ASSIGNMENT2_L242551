#include<iostream>
#include<conio.h>
using namespace std;

class Node {
public:
	char data;
	Node* next;
	Node* prev;

	Node(char d)
	{
		this->data = d;
		next = nullptr;
		prev = nullptr;
	}

};

class QueueNode {
public:
	char data;
	QueueNode* next;

	QueueNode(char d)
	{
		this->data = d;
		next = nullptr;
	}
};
