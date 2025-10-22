#include<iostream>
#include<conio.h>
#include<cstdlib>
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

	void pushFront(char d) 
	{
		QueueNode* temp = new QueueNode(d);
		if (!front) 
		{
			front = rear = temp;
		}
		else 
		{
			temp->next = front;
			front = temp;
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

class Notepad {
public:
	Node* head;
	Node* tail;
	Node* cursor;
	Queue redoQueue;

	Notepad()
	{
		head = nullptr;
		tail = nullptr;
		cursor = nullptr;
	}

	void insertChar(char d)
	{
		Node* newNode = new Node(d);
		if (!head)
		{
			head = tail = newNode;
			cursor = nullptr;
		}
		else if (cursor == head)
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;	
		}
		else if (!cursor)
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		else
		{
			newNode->prev = cursor->prev;
			newNode->next = cursor;
			cursor->prev->next = newNode;
			cursor->prev = newNode;
		}
	}

	void deleteChar()
	{
		if (!head || cursor == head)
		{
			return;
		}

		Node* toDelete = nullptr;

		if (!cursor)
		{
			toDelete = tail;
			tail = tail->prev;
			if (tail)
			{
				tail->next = nullptr;
			}
			else
			{
				head = nullptr;
			}
		}

		else
		{
			toDelete = cursor->prev;
			if (toDelete->prev)
			{
				toDelete->prev->next = cursor;
			}
			else
			{
				head = cursor;
			}
			cursor->prev = toDelete->prev;
		}

		redoQueue.pushFront(toDelete->data);

		delete toDelete;

	}

	void moveCursorLeft()
	{
		if (!head)
		{
			return;
		}
		if (!cursor)
		{
			cursor = tail;
		}
		else
		{
			cursor = cursor->prev;
		}
	}

	void moveCursorRight()
	{
		if (!head) return;
		if (!cursor)
		{
			return;
		}
		cursor = cursor->next;
	}

	void redoDeletedChars()
	{
		if (redoQueue.isEmpty()) return;


		char d = redoQueue.dequeue();
		insertChar(d);
	}

	void display()
	{
		cout << "\033[2J\033[H"; 
		cout << "		NOTEPAD" << endl;
		cout << endl;
		Node* temp = head;
		bool cursurShown = false;

		while (temp)
		{
			if (temp == cursor)
			{
				cout << "|";
				cursurShown = true;
			}
			cout << temp->data;
			temp = temp->next;
			
		}

		if (!cursor)
		{
			cout << "|";
			
		}


		cout << endl;
		cout << "Keys: leftarrow symbol,rightarrow symbol, Backspace delete, Ctrl+Z redo,ESC exit  " << endl;

	}

	void run()
	{
		display();
		while (true)
		{
			int ch = _getch();
			if (ch == 27)
			{
				break;
			}
			if (ch == 0 || ch == 24)
			{
				int arrow = _getch();
				if (arrow == 75) moveCursorLeft();
				else if (arrow == 77) moveCursorRight();
			}
			else if (ch == 8)
			{
				deleteChar();
			}
			else if (ch == 26)
			{
				redoDeletedChars();
			}
			else if (ch >= 32 && ch <= 126)
			{
				insertChar((char)ch);
			}

			else
			{
				continue;
			}

			display();
		}
	}
};

int main()
{
	Notepad pad;
	pad.run();
	return 0;
}






