#include <iostream>
using namespace std;

class Node {
public:
	Node(int value, Node* nextptr = NULL, Node* prevptr = NULL, int currentPriority = 0) {
		val = value;
		next = nextptr;
		prev = prevptr;
		priority = currentPriority;
	}

	int getVal() {
		return val;
	}

	// GETTERS
	Node* getNext() { return next; }
	Node* getPrev() { return prev; }
	int getPriority() { return priority; }

	// SETTERS
	void setPrev(Node* prevptr) { prev = prevptr; }
	void setNext(Node* nextptr) { next = nextptr; }
	void setPriority(int p) { priority = p; }

private:
	Node* next;
	Node* prev;
	int priority;
	int val;
};

class Stack {
public:
	Stack() { top = nullptr; }
	~Stack() {}

	void Push(int value) {
		Node* tmp = new Node(value, top);
		top = tmp;
	}

	int Pop() {
		int ret = top->getVal();
		Node* tmp = top;
		top = top->getNext();
		delete tmp;
		return ret;
	}

private:
	Node* top;
};

class Queue {
protected:
	Node* back;
	Node* front;

	virtual Node* NodeDequeue(void) {
		Node* tmp = front;
		if (front != nullptr) {
			front = front->getPrev();
			if (front != nullptr) front->setNext(nullptr);
		}
		return tmp;
	}

public:
	Queue(void) { front = back = nullptr; }
	~Queue(void) {
		while (front != nullptr) { delete NodeDequeue(); }
	}

	void Enqueue(int val, int priority=0) {
		Node* tmp = new Node(val, back, NULL, priority);
		back = tmp;
		if (front == nullptr) front = back;
		else {
			tmp = back->getNext();
			tmp->setPrev(back);
		}
	}

	int Dequeue(void) {
		Node* tmp = NodeDequeue();
		int ret = tmp->getVal();
		if (front == nullptr) back = front;
		return ret;
	}
};

class Scheduler : public Queue {
protected:
	Node* NodeDequeue(void) {
		Node* tmp = front;
		Node* currentHighestNode = tmp;
		int currentHighestPriority = tmp->getPriority();

		while (tmp != nullptr) {
			if (tmp->getPriority() > currentHighestPriority) {
				currentHighestNode = tmp;
				currentHighestPriority = tmp->getPriority();
			}

			tmp = tmp->getPrev();
		}

		if (currentHighestNode == front && front != nullptr) {
			front = front->getPrev();
			if (front != nullptr) front->setNext(nullptr);
		}
		else if (currentHighestNode == back && back != nullptr) {
			back = back->getNext();
			if (back != nullptr) back->setPrev(nullptr);
		}
		else if (currentHighestNode != nullptr) {
			Node* n = currentHighestNode->getNext();
			Node* p = currentHighestNode->getPrev();

			n->setPrev(p);
			p->setNext(n);
		}

		return currentHighestNode;
	}
};

int main() {
	Scheduler numbers;

	numbers.Enqueue(10, 8);
	numbers.Enqueue(20, 2);
	numbers.Enqueue(30, 5);
	numbers.Enqueue(40, 10);
	numbers.Enqueue(50, 1);
	numbers.Enqueue(60, 4);

	cout << numbers.Dequeue() << endl;
	cout << numbers.Dequeue() << endl;
	cout << numbers.Dequeue() << endl;
	cout << numbers.Dequeue() << endl;
	cout << numbers.Dequeue() << endl;
	cout << numbers.Dequeue() << endl;
	
	getchar();
}