#ifndef ROOMLINKEDLIST_H
#define ROOMLINKEDLIST_H

#include "Student.h"
#include <iomanip>

struct RoomNode {
  int roomNumber;
  string roomType;
  int capacity;
  bool isOccupied;
  Student resident;

  RoomNode *next;

  RoomNode(int num, const string &type, int cap)
      : roomNumber(num), roomType(type), capacity(cap), isOccupied(false),
        resident{}, next(nullptr) {}
};

class RoomLinkedList {
private:
  RoomNode *head;
  int count;

public:
  RoomLinkedList() : head(nullptr), count(0) {}

  ~RoomLinkedList() {
    RoomNode *cur = head;
    while (cur) {
      RoomNode *tmp = cur;
      cur = cur->next;
      delete tmp;
    }
  }

  bool addRoom(int roomNum, const string &type, int cap) {
    if (findRoom(roomNum)) {
      cout << "Room " << roomNum << " already exists.\n";
      return false;
    }
    RoomNode *node = new RoomNode(roomNum, type, cap);
    if (!head) {
      head = node;
    } else {
      // Walk to the end and append
      RoomNode *cur = head;
      while (cur->next)
        cur = cur->next;
      cur->next = node;
    }
    count++;
    return true;
  }

  bool removeRoom(int roomNum) {
    if (!head) {
      cout << "Room " << roomNum << " not found.\n";
      return false;
    }
    if (head->roomNumber == roomNum) {
      if (head->isOccupied) {
        cout << "Room " << roomNum << " is occupied. Vacate it first.\n";
        return false;
      }
      RoomNode *tmp = head;
      head = head->next;
      delete tmp;
      count--;
      return true;
    }
    for (RoomNode *cur = head; cur->next; cur = cur->next) {
      if (cur->next->roomNumber == roomNum) {
        if (cur->next->isOccupied) {
          cout << "Room " << roomNum << " is occupied. Vacate it first.\n";
          return false;
        }
        RoomNode *tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        count--;
        return true;
      }
    }
    cout << "Room " << roomNum << " not found.\n";
    return false;
  }

  RoomNode *findRoom(int roomNum) const {
    for (RoomNode *cur = head; cur; cur = cur->next)
      if (cur->roomNumber == roomNum)
        return cur;
    return nullptr;
  }

  RoomNode *findByStudentId(int studentId) const {
    for (RoomNode *cur = head; cur; cur = cur->next)
      if (cur->isOccupied && cur->resident.id == studentId)
        return cur;
    return nullptr;
  }

  RoomNode *firstVacant() const {
    for (RoomNode *cur = head; cur; cur = cur->next)
      if (!cur->isOccupied)
        return cur;
    return nullptr;
  }

  void printHeader() const {
    cout << left << setw(10) << "Room#" << setw(12) << "Type" << setw(10)
         << "Capacity" << setw(12) << "Status" << setw(8) << "Res.ID"
         << setw(20) << "Resident"
         << "\n";
  }

  static void printRow(const RoomNode *r) {
    cout << left << setw(10) << r->roomNumber << setw(12) << r->roomType
         << setw(10) << r->capacity << setw(12)
         << (r->isOccupied ? "Occupied" : "Vacant");
    if (r->isOccupied)
      cout << setw(8) << r->resident.id << setw(20) << r->resident.name;
    else
      cout << setw(8) << "-" << setw(20) << "-";
    cout << "\n";
  }

  void displayAll() const {
    if (!head) {
      cout << "  (no rooms)\n";
      return;
    }
    printHeader();
    for (RoomNode *c = head; c; c = c->next)
      printRow(c);
  }

  void displayVacant() const {
    if (!head) {
      cout << "  (no rooms)\n";
      return;
    }
    printHeader();
    bool found = false;
    for (RoomNode *c = head; c; c = c->next)
      if (!c->isOccupied) {
        printRow(c);
        found = true;
      }
    if (!found)
      cout << "  (no vacant rooms)\n";
  }

  void displayOccupied() const {
    if (!head) {
      cout << "  (no rooms)\n";
      return;
    }
    printHeader();
    bool found = false;
    for (RoomNode *c = head; c; c = c->next)
      if (c->isOccupied) {
        printRow(c);
        found = true;
      }
    if (!found)
      cout << "  (no occupied rooms)\n";
  }

  int totalRooms() const { return count; }
  int vacantRooms() const {
    int n = 0;
    for (RoomNode *c = head; c; c = c->next)
      if (!c->isOccupied)
        n++;
    return n;
  }
  int occupiedRooms() const { return count - vacantRooms(); }
};

#endif
