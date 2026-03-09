#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include "Student.h"

struct QueueNode {
  Student data;
  QueueNode *next;
  QueueNode(Student s) : data(s), next(nullptr) {}
};

class WaitingQueue {
private:
  QueueNode *front;
  QueueNode *rear;
  int count;

public:
  WaitingQueue() : front(nullptr), rear(nullptr), count(0) {}

  ~WaitingQueue() {
    while (!isEmpty())
      dequeue();
  }

  void enqueue(Student s) {
    QueueNode *node = new QueueNode(s);
    if (isEmpty()) {
      front = rear = node;
    } else {
      rear->next = node;
      rear = node;
    }
    count++;
  }

  Student dequeue() {
    if (isEmpty()) {
      cout << "Queue is empty.\n";
      return Student{};
    }
    QueueNode *temp = front;
    Student s = temp->data;
    front = front->next;
    if (!front)
      rear = nullptr;
    delete temp;
    count--;
    return s;
  }

  Student peek() const {
    if (isEmpty()) {
      cout << "Queue is empty.\n";
      return Student{};
    }
    return front->data;
  }

  bool isEmpty() const { return front == nullptr; }
  int size() const { return count; }

  void display() const {
    if (isEmpty()) {
      cout << "  (waiting list is empty)\n";
      return;
    }
    int pos = 1;
    QueueNode *cur = front;
    while (cur) {
      cout << "  #" << pos++ << "\n";
      cur->data.display();
      cout << "\n";
      cur = cur->next;
    }
  }
};

#endif
