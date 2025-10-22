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

class Queue {
public:
	QueueNode* front;
	QueueNode* rear;

	Queue()
	{
		front = nullptr;
		rear = nullptr;
	}

	bool isEmpty()
	{
		return (front == nullptr);
	}

	void enqueue(char d)
	{
		QueueNode* temp = new QueueNode(d);
		if (!rear)
		{
			front = rear = temp;
			rear = temp;
		}
		else
		{
			rear->next = temp;
			rear = temp;
		}
	}


	char dequeue()
	{
		if (isEmpty())
		{
			return '\0';
		}
		QueueNode* temp = front;
		char d = temp->data;
		front = front->next;
		if (!front)
		{
			rear = nullptr;
		}
		delete temp;
		return d;
	}


};




