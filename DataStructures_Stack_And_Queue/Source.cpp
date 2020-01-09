#include <iostream>
using namespace std;

class Node {
public:
	Node(int i, Node* nextptr, int currentPriority=0) {
		val = i;
		next = nextptr;
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

	void push(int i) {
		Node* tmp = new Node(i, top);
		top = tmp;
	}

	int pop() {
		int ret = top->getVal();
		Node* tmp = top;
		top = top->getNext();
		delete tmp;
		return ret;
	}

	void print() {
		Node* counter = top;
		cout << "Stack Values: {";

		while (counter != nullptr) {
			if (counter->getNext() != nullptr) cout << counter->getVal() << ", ";
			else cout << counter->getVal();
			counter = counter->getNext();
		}

		cout << "}";
	}

private:
	Node* top;
};

class Queue {
protected:
	Node* back;
	Node* front;

public:
	Queue(void) { front = back = nullptr; }
	~Queue(void) {
		while (front != nullptr) { delete NodeDequeue(); }
	}

	void Enqueue(int val) {
		Node* tmp = new Node(val, back);
		back = tmp;
		if (front == nullptr) front = back;
		else {
			tmp = back->getNext();
			tmp->setPrev(back);
		}
	}

	Node* NodeDequeue(void) {
		Node* tmp = front;
		if (front != nullptr) {
			front = front->getPrev();
			if (front != nullptr) front->setNext(nullptr);
		}
		return tmp;
	}

	int Dequeue(void) {
		Node* tmp = NodeDequeue();
		int ret = tmp->getVal();
		if (front == nullptr) back = front;
		return ret;
	}

	void printFrontToBack() {
		Node* counter = front;
		cout << "Queue Values (Front to Back): {";

		while (counter != nullptr) {
			if (counter->getPrev() != nullptr) cout << counter->getVal() << ", ";
			else cout << counter->getVal();
			counter = counter->getPrev();
		}

		cout << "}";
	}

	void printBackToFront() {
		Node* counter = back;
		cout << "Queue Values (Back to Front): {";

		while (counter != nullptr) {
			if (counter->getNext() != nullptr) cout << counter->getVal() << ", ";
			else cout << counter->getVal();
			counter = counter->getNext();
		}

		cout << "}";
	}
};

class PriorityQueue {
protected:
	Node* back;
	Node* front;

public:
	PriorityQueue(void) { front = back = nullptr; }
	~PriorityQueue(void) {
		while (front != nullptr) { delete NodeDequeue(); }
	}

	void Enqueue(int val, int priority=0) {
		Node* tmp = new Node(val, back, priority);
		back = tmp;
		if (front == nullptr) front = back;
		else {
			tmp = back->getNext();
			tmp->setPrev(back);
		}
	}

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

	int Dequeue(void) {
		Node* tmp = NodeDequeue();
		int ret = tmp->getVal();
		if (front == nullptr) back = front;
		return ret;
	}

	void printFrontToBack() {
		Node* counter = front;
		cout << "Queue Values (Front to Back): {";

		while (counter != nullptr) {
			if (counter->getPrev() != nullptr) cout << counter->getVal() << ", ";
			else cout << counter->getVal();
			counter = counter->getPrev();
		}

		cout << "}";
	}

	void printBackToFront() {
		Node* counter = back;
		cout << "Queue Values (Back to Front): {";

		while (counter != nullptr) {
			if (counter->getNext() != nullptr) cout << counter->getVal() << ", ";
			else cout << counter->getVal();
			counter = counter->getNext();
		}

		cout << "}";
	}
};

int main() {
	PriorityQueue numbers;

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