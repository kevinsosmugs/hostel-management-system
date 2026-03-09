#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

struct Student {
  int id;
  string name;
  string gender;
  string course;
  int yearOfStudy;

  void display() const {
    cout << "  ID: " << id << "\n"
         << "  Name: " << name << "\n"
         << "  Gender: " << gender << "\n"
         << "  Course: " << course << "\n"
         << "  Year: " << yearOfStudy << "\n";
  }
};

#endif
