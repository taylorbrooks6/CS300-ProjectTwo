// File: ProjectTwo.cpp
// Course: CS 300
// Single-file implementation using a Binary Search Tree (BST) to store the courses.
// Author: Taylor Brooks
// Due Date: October 19, 2025
// Visual Studio 2022 - C++

// This program loads course data from a CSV file into a Binary Search Tree (BST), 
// allowing users to view all courses in alphanumeric order or query-specific
// courses and their prerequisites. The BST ensures efficient insertion and search operations.
// Duplicate course numbers update the existing entry.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>      // std::toupper

// -------------------------------
// Data Structures
// -------------------------------

/**
 * @struct Course
 * @brief Represents a single course with number, title, and prerequisites.
 */
struct Course {
    std::string courseNumber;         ///< Stored uppercase (e.g., "CSCI100")
    std::string courseTitle;          ///< Course title exactly as in file
    std::vector<std::string> prereqs; ///< Prerequisite course numbers (uppercase)
};

/**
 * @struct BSTNode
 * @brief Node structure for the binary search tree.
 */
struct BSTNode {
    Course course;       ///< Course data
    BSTNode* left;       ///< Pointer to left child
    BSTNode* right;      ///< Pointer to right child
    explicit BSTNode(const Course& c) : course(c), left(nullptr), right(nullptr) {}
};

// -------------------------------
// Utility Functions
// -------------------------------

/**
 * @brief Trims leading and trailing whitespace from a string.
 * @param s Input string
 * @return Trimmed string
 */
static inline std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    if (start == s.size()) return "";

    size_t end = s.size() - 1;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end]))) --end;
    return s.substr(start, end - start + 1);
}

/**
 * @brief Converts a string to uppercase.
 * @param s Input string
 * @return Uppercase version of the string
 */
static inline std::string toUpper(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return out;
}

/**
 * @brief Splits a CSV line into tokens, trimming whitespace.
 * @param line CSV-formatted string
 * @return Vector of tokens
 */
static std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// -------------------------------
// BST Operations
// -------------------------------

/**
 * @brief Inserts a course into the BST. Updates duplicates.
 * @param root Pointer to root of BST
 * @param course Course to insert
 * @return Updated root pointer
 *
 * If the course number already exists, updates the existing node
 * with the new title and prerequisites.
 */
BSTNode* insertBST(BSTNode* root, const Course& course) {
    if (!root) {
        return new BSTNode(course);
    }
    if (course.courseNumber == root->course.courseNumber) {
        // Handle duplicate by updating existing node
        std::cout << "Warning: Duplicate course " << course.courseNumber
            << " found. Updating existing entry.\n";
        root->course.courseTitle = course.courseTitle;
        root->course.prereqs = course.prereqs;
        return root;
    }
    if (course.courseNumber < root->course.courseNumber) {
        root->left = insertBST(root->left, course);
    }
    else {
        root->right = insertBST(root->right, course);
    }
    return root;
}

/**
 * @brief Searches the BST for a course by number.
 * @param root Root of the BST
 * @param courseNumberUpper Uppercase course number to search for
 * @return Pointer to Course if found, nullptr otherwise
 */
Course* searchBST(BSTNode* root, const std::string& courseNumberUpper) {
    if (!root) return nullptr;
    if (courseNumberUpper == root->course.courseNumber) return &root->course;
    if (courseNumberUpper < root->course.courseNumber) return searchBST(root->left, courseNumberUpper);
    return searchBST(root->right, courseNumberUpper);
}

/**
 * @brief Performs an in-order traversal to print all courses.
 * @param root Root of BST
 */
void printAllInOrder(BSTNode* root) {
    if (!root) return;
    printAllInOrder(root->left);
    std::cout << root->course.courseNumber << ", " << root->course.courseTitle << "\n";
    printAllInOrder(root->right);
}

/**
 * @brief Recursively deletes the BST to free memory.
 * @param root Root node to delete
 */
void deleteBST(BSTNode* root) {
    if (!root) return;
    deleteBST(root->left);
    deleteBST(root->right);
    delete root;
}

/**
 * @brief Collects all courses into a vector for validation or other operations.
 * @param root Root of BST
 * @param out Output vector of course pointers
 */
void collectCourses(BSTNode* root, std::vector<Course*>& out) {
    if (!root) return;
    collectCourses(root->left, out);
    out.push_back(&root->course);
    collectCourses(root->right, out);
}

// -------------------------------
// File Loading & Validation
// -------------------------------

/**
 * @brief Loads courses from a CSV file into a BST and validates prerequisites.
 * @param filePath Path to CSV file
 * @return Pointer to BST root, nullptr on failure
 *
 * Prints warnings for missing prerequisites or malformed lines.
 */
BSTNode* loadCoursesBST(const std::string& filePath) {
    std::ifstream infile(filePath);
    if (!infile.is_open()) {
        std::cout << "Error: Cannot open file \"" << filePath << "\"\n";
        return nullptr;
    }

    BSTNode* root = nullptr;
    std::string line;
    size_t lineno = 0;

    while (std::getline(infile, line)) {
        ++lineno;
        std::string trimmed = trim(line);
        if (trimmed.empty()) continue; // Skip blank lines

        std::vector<std::string> tokens = splitCSVLine(trimmed);
        if (tokens.size() < 2) {
            std::cout << "Malformed line " << lineno << ": \"" << line
                << "\" (expected at least courseNumber and title)\n";
            continue;
        }

        // Create Course object
        Course c;
        c.courseNumber = toUpper(tokens[0]);
        c.courseTitle = tokens[1];

        // Add prerequisites if any
        c.prereqs.clear();
        if (tokens.size() > 2) {
            for (size_t i = 2; i < tokens.size(); ++i) {
                if (!tokens[i].empty()) {
                    c.prereqs.push_back(toUpper(tokens[i]));
                }
            }
        }

        // Insert course into BST
        root = insertBST(root, c);
    }
    infile.close();

    // Validate that all prerequisites exist
    std::vector<Course*> allCourses;
    collectCourses(root, allCourses);
    for (Course* cp : allCourses) {
        for (const auto& prereqNum : cp->prereqs) {
            Course* found = searchBST(root, prereqNum);
            if (!found) {
                std::cout << "Warning: Prerequisite " << prereqNum
                    << " for course " << cp->courseNumber
                    << " is missing from the dataset.\n";
            }
        }
    }

    std::cout << "Loaded " << allCourses.size() << " course(s).\n";
    return root;
}

// -------------------------------
// Menu and User Interaction
// -------------------------------

/**
 * @brief Prints the main menu options to the console.
 */
void printMenu() {
    std::cout << "1. Load Data Structure.\n";
    std::cout << "2. Print Course List.\n";
    std::cout << "3. Print Course.\n";
    std::cout << "9. Exit\n";
}

/**
 * @brief Handles option to print a specific course and its prerequisites.
 * @param root Root of BST
 */
void optionPrintCourse(BSTNode* root) {
    std::cout << "What course do you want to know about? ";
    std::string input;
    std::getline(std::cin, input);
    input = trim(input);
    if (input.empty()) {
        std::cout << "No course entered.\n";
        return;
    }

    std::string key = toUpper(input);
    Course* c = searchBST(root, key);
    if (!c) {
        std::cout << "Course not found\n";
        return;
    }

    // Print course title
    std::cout << c->courseNumber << ", " << c->courseTitle << "\n";

    // Print prerequisites
    if (c->prereqs.empty()) {
        std::cout << "Prerequisites: None\n";
    }
    else {
        std::cout << "Prerequisites: ";
        for (size_t i = 0; i < c->prereqs.size(); ++i) {
            const std::string& prereqNum = c->prereqs[i];
            Course* preCourse = searchBST(root, prereqNum);
            if (preCourse) {
                std::cout << prereqNum << " (" << preCourse->courseTitle << ")";
            }
            else {
                std::cout << prereqNum << " (title not found)";
            }
            if (i + 1 < c->prereqs.size()) std::cout << ", ";
        }
        std::cout << "\n";
    }
}

// -------------------------------
// Main Program
// -------------------------------

int main() {
    std::cout << "Welcome to the course planner.\n";

    BSTNode* root = nullptr;
    bool loaded = false;

    while (true) {
        printMenu();
        std::cout << "What would you like to do? ";

        std::string choiceLine;
        std::getline(std::cin, choiceLine);
        choiceLine = trim(choiceLine);
        if (choiceLine.empty()) {
            std::cout << "No option entered. Please enter a number from the menu.\n";
            continue;
        }

        int choice = 0;
        try {
            choice = std::stoi(choiceLine);
        }
        catch (...) {
            std::cout << choiceLine << " is not a valid option.\n";
            continue;
        }

        if (choice == 1) { // Load data
            std::cout << "Enter a file name to load: ";
            std::string filename;
            std::getline(std::cin, filename);
            filename = trim(filename);
            if (filename.empty()) {
                std::cout << "No file name entered.\n";
                continue;
            }

            // Delete existing BST if present to avoid memory leaks
            if (root) {
                deleteBST(root);
                root = nullptr;
            }

            BSTNode* newRoot = loadCoursesBST(filename);
            if (newRoot) {
                root = newRoot;
                loaded = true;
            }
            else {
                loaded = false;
            }
        }
        else if (choice == 2) { // Print all courses
            if (!loaded || !root) {
                std::cout << "No data loaded. Please load a data file first.\n";
                continue;
            }
            std::cout << "Here is a sample schedule:\n";
            printAllInOrder(root);
        }
        else if (choice == 3) { // Print specific course
            if (!loaded || !root) {
                std::cout << "No data loaded. Please load a data file first.\n";
                continue;
            }
            optionPrintCourse(root);
        }
        else if (choice == 9) { // Exit
            std::cout << "Thank you for using the course planner!\n";
            break;
        }
        else {
            std::cout << choice << " is not a valid option.\n";
        }
    }

    // Clean up memory
    if (root) deleteBST(root);

    return 0;
}