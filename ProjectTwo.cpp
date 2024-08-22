// ProjectTwo.cpp
//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Todd Johnson
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : ProjectTwo
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Function to load data from file
void LoadDataStructure(map<string, Course>& courses) {
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);  // Initialize with 'line'
        string courseNumber, title, prereq;
        getline(iss, courseNumber, ',');
        getline(iss, title, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.title = title;

        while (getline(iss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseNumber] = course;
    }
    file.close();
}

// Function to print the course list
void PrintCourseList(const map<string, Course>& courses) {
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.title << endl;
    }
}

// Function to print course information and its prerequisites directly as listed
void PrintCourse(const map<string, Course>& courses) {
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.courseNumber << ", " << it->second.title << endl;
        cout << "Prerequisites: ";
        for (const string& prereq : it->second.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
    else {
        cout << "Course not found!" << endl;
    }
}

int main() {
    map<string, Course> courses;
    int choice;

    do {
        cout << "1. Load the file data into the data structure." << endl;
        cout << "2. Print an alphanumeric list of all the courses in the Computer Science department." << endl;
        cout << "3. Print the course title and the prerequisites for any individual course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            LoadDataStructure(courses);
            break;
        case 2:
            PrintCourseList(courses);
            break;
        case 3:
            PrintCourse(courses);
            break;
        case 9:
            cout << "Thank you" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
