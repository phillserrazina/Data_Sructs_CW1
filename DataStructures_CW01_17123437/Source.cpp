#include <iostream>
using namespace std;

// Stores the values and priorities of an object
// used by the Stack, Queue and Scheduler classes.
class Node 
{
public:
	// Constructor
	Node(int value, Node* nextptr = NULL, Node* prevptr = NULL, int currentPriority = 0) {
		this->value = value;
		next = nextptr;
		prev = prevptr;
		priority = currentPriority;
	}

	// GETTERS
	int getVal() { return value; }
	Node* getNext() { return next; }
	Node* getPrev() { return prev; }
	int getPriority() { return priority; }

	// SETTERS
	void setPrev(Node* prevptr) { prev = prevptr; }
	void setNext(Node* nextptr) { next = nextptr; }
	void setPriority(int p) { priority = p; }

private:
	// VARIABLES
	Node* next;
	Node* prev;
	int priority;
	int value;
};

// Data structure implemented in a LIFO manner, which means that the last
// element that was pushed in will be the first one to be popped out.
class Stack 
{
public:
	// Constuctor and Destructor
	Stack() { top = nullptr; }
	~Stack() {}

	// Inserts an element on the top of the stack.
	void Push(int i) {
		// Create a new node
		Node* tmp = new Node(i, top);
		// Set the new node as the top
		top = tmp;
	}

	Node* NodePop() {
		// Get the front node
		Node* tmp = top;
		// If the front exists
		if (top != nullptr) {
			// Set the new front to be the next node
			top = top->getNext();
			// If there is a next node, point it's next node to a nullptr
			if (top != nullptr) top->setPrev(nullptr);
		}
		// If the front node doesn't exist, throw an error.
		else throw "Empty Queue";

		// Return the found value
		return tmp;
	}

	// Removes and returns the element currently at the top of the Stack.
	int Pop() {
		// Check if the current node exists. If it doesn't, throw an error.
		if (top == nullptr) throw "Empty Stack";

		// Get the value to be returned from the top node
		int ret = top->getVal();
		// Get the top node
		Node* tmp = NodePop();

		// Clean the tmp node pointer from memory and return the desired value.
		delete tmp;
		return ret;
	}

private:
	// Variable where the top node of the stack is stored.
	Node* top;
};

// Data structure implemented in a FIFO manner, which means that the first
// element that was pushed in will be the first one to be popped out.
class Queue 
{
protected:
	// VARIABLES
	Node* back;
	Node* front;

public:
	// Constructor and Destructor
	Queue(void) { front = back = nullptr; }
	~Queue(void) {
		// Delete all node pointers from memory.
		while (front != nullptr) { delete NodeDequeue(); }
	}

	// Inserts an element to the back of the Queue.
	// If a priority if given, it can only be of value 0-10. Any value outside of those limits will be set to the closest limit.
	void Enqueue(int val, int priority=0) {
		// Handle limit exceptions
		if (priority < 0) priority = 0;
		else if (priority > 10) priority = 10;

		// Make a new node
		Node* tmp = new Node(val, back, NULL, priority);
		// Set the new node as the back node
		back = tmp;
		// If the front is null, that means that this is the first node of the Queue,
		// so we set the front to be the same as the back.
		if (front == nullptr) front = back;
		else {
			// If the front is not null, we set the previous back node to point to our
			// new one as their previous node.
			tmp = back->getNext();
			tmp->setPrev(back);
		}
	}

	// Removes and returns the element currently at the front of the Queue.
	int Dequeue(void) {
		// Get the front node
		Node* tmp = NodeDequeue();
		// Get the value from the front node
		int ret = tmp->getVal();
		// If this was the only node in the Queue, set both the back and the front to be nullptr
		if (front == nullptr) back = front;
		return ret;
	}

private:
	// Helper function that gets the current front node and handles the removal of said node.
	virtual Node* NodeDequeue(void) {
		// Get the front node
		Node* tmp = front;
		// If the front exists
		if (front != nullptr) {
			// Set the new front to be the next node
			front = front->getPrev();
			// If there is a next node, point it's next node to a nullptr
			if (front != nullptr) front->setNext(nullptr);
		}
		// If the front node doesn't exist, throw an error.
		else throw "Empty Queue";

		// Return the found value
		return tmp;
	}
};

// Data structure implemented in a priority manner, which means that it will
// pop the value that has the highest priority.
class Scheduler : public Queue 
{
private:
	// Variation of the NodeDequeue function implemented in the base class, modified
	// to return the node with the highest priority.
	Node* NodeDequeue(void) {
		// Get the front node
		Node* tmp = front;

		// If there are no nodes left, throw an error.
		if (tmp == nullptr) throw "Empty Scheduler";

		// Set the front node to be the highest priority as a means of reference
		Node* currentHighestNode = tmp;
		// Set the front node's priority to be the highest as a means of reference
		int currentHighestPriority = tmp->getPriority();

		// Go through the whole Scheduler
		while (tmp != nullptr) {
			// If the priority of the currently inspected node is higher than the one we currently have set
			if (tmp->getPriority() > currentHighestPriority) {
				// Make this node the higheste priority
				currentHighestNode = tmp;
				currentHighestPriority = tmp->getPriority();
			}

			// Go to the next node
			tmp = tmp->getPrev();
		}

		// If the highest found node is the front
		if (currentHighestNode == front && front != nullptr) {
			// Make the next node the new front
			front = front->getPrev();
			if (front != nullptr) front->setNext(nullptr);
		}

		// If the highest found node is the back
		else if (currentHighestNode == back && back != nullptr) {
			// Make the previous node the new back
			back = back->getNext();
			if (back != nullptr) back->setPrev(nullptr);
		}

		// If the highest found node is somewhere in the middle
		else if (currentHighestNode != nullptr) {
			// Get the next and previous nodes
			Node* n = currentHighestNode->getNext();
			Node* p = currentHighestNode->getPrev();

			// Set them to be each other's next and previous nodes
			n->setPrev(p);
			p->setNext(n);
		}

		// Go through the whole Scheduler
		tmp = front;
		while (tmp != nullptr) {
			// Increment priority of all the other nodes to prevent blocking.
			tmp->setPriority(tmp->getPriority() + 1);
			// Go to the next node
			tmp = tmp->getPrev();
		}

		return currentHighestNode;
	}
};

int main() {
	Scheduler scheduler;
	Queue myQueue;
	Stack myStack;

	myStack.Push(1);
	myStack.Push(2);
	myStack.Push(3);
	myStack.Push(4);
	
	try {
		cout << "Stack:" << endl;
		cout << myStack.Pop() << " ";
		cout << myStack.Pop() << " ";
		cout << myStack.Pop() << " ";
		cout << myStack.Pop() << " ";
		cout << myStack.Pop() << endl;
	}
	catch (const char* message) {
		cout << message << endl;
	}

	myQueue.Enqueue(1);
	myQueue.Enqueue(2);
	myQueue.Enqueue(3);
	myQueue.Enqueue(4);

	try {
		cout << "Queue:" << endl;
		cout << myQueue.Dequeue() << " ";
		cout << myQueue.Dequeue() << " ";
		cout << myQueue.Dequeue() << " ";
		cout << myQueue.Dequeue() << " ";
		cout << myQueue.Dequeue() << endl;
	}
	catch (const char* message) {
		cout << message << endl;
	}
	
	scheduler.Enqueue(10, 8);
	scheduler.Enqueue(20, 2);
	scheduler.Enqueue(40, 10);
	scheduler.Enqueue(50, 1);
	scheduler.Enqueue(60, 4);
	scheduler.Enqueue(30, 5);
	scheduler.Enqueue(90, 9);

	try {
		cout << "Scheduler:" << endl;
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		scheduler.Enqueue(70, 5);
		scheduler.Enqueue(80, 6);
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << " ";
		cout << scheduler.Dequeue() << endl;
	}
	catch (const char* message) {
		cout << message << endl;
	}

	getchar();
}