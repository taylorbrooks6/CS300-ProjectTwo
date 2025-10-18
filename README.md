# Project Two – ABCU Course Planner

**Author:** Taylor Brooks  
**Course:** CS 300 – Analysis and Design  
**Institution:** SNHU (Applied Bachelor’s in Computer Science)  
**Project:** Project Two – Course Planner  

---

## Overview
This program simulates a **course advising system** that allows students and advisors to view courses, their descriptions, and any required prerequisites. It reads data from a `.csv` file, stores the information using an efficient data structure, and provides an interactive console menu for easy navigation.

---

## Features
- Loads course data from a `.csv` file  
- Stores courses in a **Binary Search Tree (BST)** for fast, ordered retrieval  
- Prints a complete course list in **alphanumeric order**  
- Displays **individual course details** with prerequisites  
- Handles invalid input and missing data gracefully  

---

## File Information
| File Name | Description |
|------------|-------------|
| `ProjectTwo.cpp` | Main source file containing the full implementation of the course planner |
| `CS 300 ABCU_Advising_Program_Input.csv` | Sample input file containing course information and prerequisites |
| `README.md` | This file – provides documentation and project overview |

---

## Sample Program Execution
Welcome to the course planner.//
Load Data Structure.//
Print Course List.//
Print Course.//
Exit//
What would you like to do? 1//
//
Enter a file name to load: CS 300 ABCU_Advising_Program_Input.csv//
Loaded 8 course(s).//
//
Load Data Structure.//
Print Course List.//
Print Course.//
Exit//
What would you like to do? 2//
//
Here is a sample schedule://
CSCI100, Introduction to Computer Science//
CSCI101, Introduction to Programming in C++//
CSCI200, Data Structures//
CSCI300, Introduction to Algorithms//
CSCI301, Advanced Programming in C++//
CSCI350, Operating Systems//
CSCI400, Large Software Development//
MATH201, Discrete Mathematics//
//
Load Data Structure.//
Print Course List.//
Print Course.//
Exit//
What would you like to do? 3//
//
What course do you want to know about? csci400//
CSCI400, Large Software Development//
Prerequisites: CSCI301 (Advanced Programming in C++), CSCI350 (Operating Systems)//
//
Load Data Structure.//
Print Course List.//
Print Course.//
Exit//
What would you like to do? 9//
//
Thank you for using the course planner!//

## Data Structure Design
The project uses a **Binary Search Tree (BST)** to store courses by their course ID.  
- Each node represents a single course.  
- In-order traversal ensures alphabetical output.  
- Lookup operations for individual courses are O(log n) on average.

---

## How to Run
1. Compile the program (e.g., in Visual Studio or g++):
g++ ProjectTwo.cpp -o ProjectTwo

2. Run the executable

3. When prompted, enter the CSV file name (example:  
`CS 300 ABCU_Advising_Program_Input.csv`)

---

## Notes
- Input file must follow the format:  
COURSE_ID,Course Name,Prerequisite1,Prerequisite2

- The program validates missing files and invalid course codes.

---

## Acknowledgements
This project was developed for **Project Two** in the **CS 300** course.  
It demonstrates mastery of **data structures**, **file handling**, and **algorithmic efficiency** in C++.

---

## Author Contact
**Taylor Brooks**  
GitHub: [@taylorbrooks6](https://github.com/taylorbrooks6)  
