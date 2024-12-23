#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

// defining the class "Course"
class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;

    // constructor for courses
    Course() : courseNumber(""), courseTitle("") {}

    // Constructor with our course numbers and titles of courses
    Course(std::string number, std::string title)
        : courseNumber(number), courseTitle(title) {
    }

    // our function for adding prereqs to classes
    void addPrerequisite(std::string prerequisite) {
        prerequisites.push_back(prerequisite);
    }

    // function to print called upon course details
    void printCourseDetails() const {
        std::cout << "Course Number: " << courseNumber << std::endl;
        std::cout << "Course Title: " << courseTitle << std::endl;
        if (prerequisites.empty()) {
            std::cout << "No prerequisites." << std::endl;
        }
        else {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Loads our courses from csv file into hash table
void loadPredefinedCourses(std::unordered_map<std::string, Course>& courses) {
    // courses for hash table
    Course csci100("CSCI100", "Introduction to Computer Science");
    courses[csci100.courseNumber] = csci100;

    Course csci101("CSCI101", "Introduction to Programming in C++");
    csci101.addPrerequisite("CSCI100");
    courses[csci101.courseNumber] = csci101;

    Course csci200("CSCI200", "Data Structures");
    csci200.addPrerequisite("CSCI101");
    courses[csci200.courseNumber] = csci200;

    Course math201("MATH201", "Discrete Mathematics");
    courses[math201.courseNumber] = math201;

    Course csci300("CSCI300", "Introduction to Algorithms");
    csci300.addPrerequisite("CSCI200");
    csci300.addPrerequisite("MATH201");
    courses[csci300.courseNumber] = csci300;

    Course csci301("CSCI301", "Advanced Programming in C++");
    csci301.addPrerequisite("CSCI101");
    courses[csci301.courseNumber] = csci301;

    Course csci350("CSCI350", "Operating Systems");
    csci350.addPrerequisite("CSCI300");
    courses[csci350.courseNumber] = csci350;

    Course csci400("CSCI400", "Large Software Development");
    csci400.addPrerequisite("CSCI301");
    csci400.addPrerequisite("CSCI350");
    courses[csci400.courseNumber] = csci400;
}

// prints out all courses in Alphanumerical 
void printCoursesAlphanumerically(const std::unordered_map<std::string, Course>& courses) {
    // Create a vector of course numbers to sort them
    std::vector<std::string> courseNumbers;
    for (const auto& coursePair : courses) {
        courseNumbers.push_back(coursePair.first);
    }

    // course numbers in alphanumeric
    std::sort(courseNumbers.begin(), courseNumbers.end());

    // prints the course details after sorting
    for (const auto& courseNumber : courseNumbers) {
        const Course& course = courses.at(courseNumber);
        std::cout << "Course Number: " << course.courseNumber << " - " << course.courseTitle << std::endl;
    }
}

// specific details of specific courses
void printCourseDetails(const std::unordered_map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        it->second.printCourseDetails();
    }
    else {
        std::cout << "Course not found." << std::endl;
    }
}

//our menu functions for input and output
void showMenu() {
    std::cout << "Menu Options:\n";
    std::cout << "1. Load courses data\n";
    std::cout << "2. Print all courses in alphanumeric order\n";
    std::cout << "3. Print course details by course number\n";
    std::cout << "9. Exit\n";
}

int main() {
    std::unordered_map<std::string, Course> courses;

    bool running = true;
    while (running) {
        showMenu();
        int option;
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
        case 1:
            loadPredefinedCourses(courses);
            std::cout << "Courses data loaded successfully.\n";
            break;
        case 2:
            printCoursesAlphanumerically(courses);
            break;
        case 3: {
            std::string courseNumber;
            std::cout << "Enter the course number (e.g., CSCI101): ";
            std::cin >> courseNumber;
            printCourseDetails(courses, courseNumber);
            break;
        }
        case 9:
            running = false;
            std::cout << "Exiting the program...\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }
    //our hashtable will pull from CSV and respond based on input through menu from user.
    return 0;
}