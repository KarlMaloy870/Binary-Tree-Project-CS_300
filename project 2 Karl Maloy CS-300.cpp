#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define Course class

class Course {
public:
    string courseNumber;
    string title;
    vector<string> prerequisites;


    // Constructor
    Course(const string& number, const string& title)
        : courseNumber(number), title(title) {}

    // Method to add prerequisite
    void addPrerequisite(const string& prereq) {
        prerequisites.push_back(prereq);
    }
};

// Binary Search Tree Node
struct TreeNode {
    Course data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Course& course) : data(course), left(nullptr), right(nullptr) {}
};

// Binary Search Tree
class BST {
private:
    TreeNode* root;

    // Private helper functions
    void insert(TreeNode*& node, const Course& course);
    void inOrderTraversal(TreeNode* node);
    void printCourse(TreeNode* node, const string& courseNumber);
    void destroyTree(TreeNode* node);

public:
    BST() : root(nullptr) {}
    ~BST();

    void insert(const Course& course);
    void inOrderTraversal();
    void printCourse(const string& courseNumber);
};

// Destructor to delete nodes recursively
BST::~BST() {
    destroyTree(root);
}

void BST::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert a course into the BST
void BST::insert(TreeNode*& node, const Course& course) {
    if (node == nullptr) {
        node = new TreeNode(course);
    }
    else {
        if (course.courseNumber < node->data.courseNumber) {
            insert(node->left, course);
        }
        else {
            insert(node->right, course);
        }
    }
}

void BST::insert(const Course& course) {
    insert(root, course);
}

// In-order traversal of the BST
void BST::inOrderTraversal(TreeNode* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        cout << "Course Number: " << node->data.courseNumber << ", Title: " << node->data.title << endl;
        inOrderTraversal(node->right);
    }
}

void BST::inOrderTraversal() {
    inOrderTraversal(root);
}

// Print course information based on course number
void BST::printCourse(TreeNode* node, const string& courseNumber) {
    if (node == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    if (courseNumber < node->data.courseNumber) {
        printCourse(node->left, courseNumber);
    }
    else if (courseNumber > node->data.courseNumber) {
        printCourse(node->right, courseNumber);
    }
    else {
        cout << "Course Title: " << node->data.title << endl;
        if (!node->data.prerequisites.empty()) {
            cout << "Prerequisites:";
            for (const auto& prereq : node->data.prerequisites) {
                cout << " " << prereq;
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites." << endl;
        }
    }
}

void BST::printCourse(const string& courseNumber) {
    printCourse(root, courseNumber);
}



// Main program with menu
int main() {
    BST bst;
    bool dataLoaded = false;
    int option;

    do {
        // Display menu
        cout << "\nMenu:\n";
        cout << "1. Load data from file\n";
        cout << "2. Print Computer Science course list\n";
        cout << "3. Print course information and prerequisites\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
        case 1: {
            if (!dataLoaded) {
                string fileName;
                cout << "Enter file name: ";
                cin >> fileName;

                ifstream file(fileName);
                if (!file.is_open()) {
                    cerr << "Error opening file: " << fileName << endl;
                    break;
                }

                string line;
                while (getline(file, line)) {
                    stringstream ss(line);
                    string courseNumber, title, prereq;

                    // Read courseNumber and title
                    getline(ss, courseNumber, ',');
                    getline(ss, title, ',');

                    Course course(courseNumber, title);

                    // Read prerequisites
                    while (getline(ss, prereq, ',')) {
                        course.addPrerequisite(prereq);
                    }

                    bst.insert(course);
                }

                file.close();
                dataLoaded = true;
                cout << "Data loaded successfully.\n";
            }
            else {
                cout << "Data already loaded.\n";
            }
            break;
        }
        case 2: {
            cout << "\nComputer Science Course List:\n";
            bst.inOrderTraversal(); // Assuming Computer Science courses are sorted in the BST
            break;
        }
        case 3: {
            string courseNumber;
            cout << "Enter course number: ";
            cin >> courseNumber;
            bst.printCourse(courseNumber);
            break;
        }
        case 9: {
            cout << "Exiting program.\n";
            break;
        }
        default:
            cout << "Invalid option. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    } while (option != 9);

    return 0;
}
