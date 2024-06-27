#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include "naturalnum.h"

using namespace std;

void printList(const list<int>& myList) {
    for (int num : myList) {
        cout << num << " ";
    }
    cout << endl;
}

void printStack(stack<int> myStack) {
    while (!myStack.empty()) {
        cout << myStack.top() << " ";
        myStack.pop();
    }
    cout << endl;
}

void printQueue(queue<int> myQueue) {
    while (!myQueue.empty()) {
        cout << myQueue.front() << " ";
        myQueue.pop();
    }
    cout << endl;
}

int main() {
    list<int> myList;
    stack<int> myStack;
    queue<int> myQueue;

    int num;
    cout << "Enter a sequence of integers, terminate with 0:" << endl;
    cin >> num;
    while (num != 0) {
        myList.push_back(num);
        myStack.push(num);
        myQueue.push(num);
        cin >> num;
    }

    cout << "Elements of the list: ";
    printList(myList);

    cout << "Elements of the stack: ";
    printStack(myStack);

    cout << "Elements of the queue: ";
    printQueue(myQueue);

    cout << "Elements of the list in reverse order: ";
    myList.reverse();
    printList(myList);

    cout << "Elements of the stack in reverse order: ";
    stack<int> tempStack = myStack;
    while (!tempStack.empty()) {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;

    cout << "Elements of the queue in reverse order: ";
    stack<int> reverseStack;
    queue<int> tempQueue = myQueue;
    while (!tempQueue.empty()) {
        reverseStack.push(tempQueue.front());
        tempQueue.pop();
    }
    while (!reverseStack.empty()) {
        cout << reverseStack.top() << " ";
        reverseStack.pop();
    }
    cout << endl;

    // Using NaturalNumber class
    NaturalNumber numObj;
    cout << "Enter a natural number to get its factors: ";
    cin >> num;
    list<int> factors = numObj.getFactors(num);
    cout << "Factors of " << num << ": ";
    printList(factors);

    return 0;
}
