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

class Queue {
private:
	Process* front;
	Process* rear;
public:
	Queue()
	{
		front = nullptr;
		rear = nullptr;
	}

	bool isEmpty()
	{
		return front == nullptr;
	}


	void enqueue(Process* p)
	{
		if (rear == nullptr)
		{
			front = p;
			rear = p;
		}
		else
		{
			rear->next = p;
			rear = p;

		}

		p->next = nullptr;
	}

	Process* dequeue()
	{
		if (front == nullptr)
		{
			return nullptr;
		}
		Process* temp = front;
		front = front->next;
		if (front == nullptr)
		{
			rear = nullptr;
		}
		temp->next = nullptr;
		return temp;
	}

	void display()
	{
		cout << "Ready Queue " << endl;
		if (isEmpty())
		{
			cout << "Empty Queue" << endl;
		}
		else
		{
			Process* temp = front;
			while (temp != nullptr)
			{
				cout << "[ " << temp->name << " (P" << temp->priority << " ,D" << temp->duration << ")]";
				temp = temp->next;
			}
		}
		cout << endl;
	}

};

class Stack {
private:
	Process* top;
public:
	
	Stack()
	{
		top = nullptr;
	}

	bool isEmpty()
	{
		return top == nullptr;
	}

	void push(Process* p)
	{
		p->next = top;
		top = p;
	}

	Process* pop()
	{
		Process* temp = top;
		top = top->next;
		temp->next = nullptr;
		return temp;
	}

	void Last3TasksDisplay(string label)
	{
		cout << "Label is: " << label << endl;
		if (isEmpty())
		{
			cout << "Empty Stack" << endl;
		}
		else
		{
			Process* temp = top;
			int count = 0;
			while (temp != NULL && count < 3)
			{
				cout << "[" << temp->name << "]";
				temp = temp->next;
				count++;
			}
		}

		cout << endl;
	}


	
};

Process* ExecuteRoundRobin(Queue& q1, Stack& s1, int timeSlice)
{
	if (q1.isEmpty())
	{
		cout << "Found No Processes in Queue to Execute " << endl;
		return nullptr;
	}

	Process* curr = q1.dequeue();
	cout << "Currently Executing: " << curr->name << endl;

	int runTime = 0;
	if (curr->duration > timeSlice)
	{
		runTime = timeSlice;
	}
	else
	{
		runTime = curr->duration;
	}

	curr->duration = curr->duration - runTime;

	cout << "Simulated Run Time " << runTime << endl;

	if (curr->duration > 0)
	{
		cout << "Time slice complete. Remaining duration of Task is: " << curr->duration << endl;
		q1.enqueue(curr);
	}
	else
	{
		cout << "Process: " << curr->name << " completed." << endl;
		s1.push(curr);

	}

	return curr;

}



