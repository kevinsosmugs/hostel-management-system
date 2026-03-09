#ifndef HOSTELMANAGER_H
#define HOSTELMANAGER_H

#include "RoomLinkedList.h"
#include "WaitingQueue.h"
#include <limits>

class HostelManager {
private:
  WaitingQueue waitingList;
  RoomLinkedList rooms;

  static int readInt(const string &prompt) {
    int val;
    while (true) {
      cout << prompt;
      if (cin >> val) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return val;
      }
      cout << "Invalid input. Enter a number.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  static string readLine(const string &prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
  }

public:
  void addStudentApplication() {
    cout << "\n--- Add Student Application ---\n";
    Student s;
    s.id = readInt("  Student ID: ");
    s.name = readLine("  Name: ");
    s.gender = readLine("  Gender (M/F): ");
    s.course = readLine("  Course: ");
    s.yearOfStudy = readInt("  Year of Study: ");

    waitingList.enqueue(s);
    cout << "Added \"" << s.name << "\" to waiting list (position "
         << waitingList.size() << ").\n";
  }

  void assignRoom() {
    cout << "\n--- Assign Room ---\n";
    if (waitingList.isEmpty()) {
      cout << "No students in waiting list.\n";
      return;
    }
    int roomNum = readInt("  Room Number: ");
    RoomNode *room = rooms.findRoom(roomNum);
    if (!room) {
      cout << "Room " << roomNum << " does not exist.\n";
      return;
    }
    if (room->isOccupied) {
      cout << "Room " << roomNum << " is already occupied.\n";
      return;
    }
    Student s = waitingList.dequeue();
    room->isOccupied = true;
    room->resident = s;
    cout << "Room " << roomNum << " assigned to \"" << s.name << "\" (ID "
         << s.id << ").\n";
  }

  void autoAssign() {
    cout << "\n--- Auto-Assign ---\n";
    if (waitingList.isEmpty()) {
      cout << "No students in waiting list.\n";
      return;
    }
    int assigned = 0;
    while (!waitingList.isEmpty()) {
      RoomNode *room = rooms.firstVacant();
      if (!room) {
        cout << "No more vacant rooms.\n";
        break;
      }
      Student s = waitingList.dequeue();
      room->isOccupied = true;
      room->resident = s;
      cout << "  Room " << room->roomNumber << " -> \"" << s.name << "\" (ID "
           << s.id << ")\n";
      assigned++;
    }
    cout << assigned << " student(s) assigned.\n";
    if (!waitingList.isEmpty())
      cout << waitingList.size() << " student(s) still waiting.\n";
  }

  void vacateRoom() {
    cout << "\n--- Vacate Room ---\n";
    int roomNum = readInt("  Room Number: ");
    RoomNode *room = rooms.findRoom(roomNum);
    if (!room) {
      cout << "Room " << roomNum << " does not exist.\n";
      return;
    }
    if (!room->isOccupied) {
      cout << "Room " << roomNum << " is already vacant.\n";
      return;
    }
    cout << "Room " << roomNum << " vacated. \"" << room->resident.name
         << "\" removed.\n";
    room->isOccupied = false;
    room->resident = Student{};
  }

  void addNewRoom() {
    cout << "\n--- Add Room ---\n";
    int roomNum = readInt("  Room Number: ");
    string type = readLine("  Type (Single/Double/Triple): ");
    int capacity = readInt("  Capacity: ");

    if (rooms.addRoom(roomNum, type, capacity))
      cout << "Room " << roomNum << " (" << type << ") added.\n";
  }

  void removeARoom() {
    cout << "\n--- Remove Room ---\n";
    int roomNum = readInt("  Room Number: ");
    if (rooms.removeRoom(roomNum))
      cout << "Room " << roomNum << " removed.\n";
  }

  void searchStudent() {
    cout << "\n--- Search Student ---\n";
    int id = readInt("  Student ID: ");
    RoomNode *room = rooms.findByStudentId(id);
    if (room) {
      cout << "Found in Room " << room->roomNumber << ":\n";
      room->resident.display();
    } else {
      cout << "Student ID " << id << " not assigned to any room.\n";
    }
  }

  void displayWaitingList() {
    cout << "\n--- Waiting List (" << waitingList.size() << " students) ---\n";
    waitingList.display();
  }

  void displayAllRooms() {
    cout << "\n--- All Rooms ---\n";
    rooms.displayAll();
  }
  void displayVacantRooms() {
    cout << "\n--- Vacant Rooms ---\n";
    rooms.displayVacant();
  }
  void displayOccupiedRooms() {
    cout << "\n--- Occupied Rooms ---\n";
    rooms.displayOccupied();
  }

  void displayStatistics() {
    cout << "\n--- Statistics ---\n"
         << "  Total Rooms:      " << rooms.totalRooms() << "\n"
         << "  Occupied Rooms:   " << rooms.occupiedRooms() << "\n"
         << "  Vacant Rooms:     " << rooms.vacantRooms() << "\n"
         << "  Waiting Students: " << waitingList.size() << "\n";
  }

  void run() {
    cout << "\nHostel Room Allocation System\n";

    bool running = true;
    while (running) {
      cout << "\n--- Menu ---\n"
           << "  1. Add Student Application\n"
           << "  2. Assign Room\n"
           << "  3. Auto-Assign All\n"
           << "  4. Vacate Room\n"
           << "  5. Add Room\n"
           << "  6. Remove Room\n"
           << "  7. Search Student\n"
           << "  8. Waiting List\n"
           << "  9. All Rooms\n"
           << " 10. Vacant Rooms\n"
           << " 11. Occupied Rooms\n"
           << " 12. Statistics\n"
           << "  0. Exit\n";

      int choice = readInt("  Choice: ");

      switch (choice) {
      case 1:
        addStudentApplication();
        break;
      case 2:
        assignRoom();
        break;
      case 3:
        autoAssign();
        break;
      case 4:
        vacateRoom();
        break;
      case 5:
        addNewRoom();
        break;
      case 6:
        removeARoom();
        break;
      case 7:
        searchStudent();
        break;
      case 8:
        displayWaitingList();
        break;
      case 9:
        displayAllRooms();
        break;
      case 10:
        displayVacantRooms();
        break;
      case 11:
        displayOccupiedRooms();
        break;
      case 12:
        displayStatistics();
        break;
      case 0:
        cout << "Goodbye.\n";
        running = false;
        break;
      default:
        cout << "Invalid choice.\n";
      }
    }
  }
};

#endif
