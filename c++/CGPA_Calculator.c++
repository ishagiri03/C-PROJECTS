#include <iostream>
#include <fstream>
using namespace std;

// Project Description:
// This program calculates GPA and CGPA of a student based on subjects,
// credits and grades. It also stores the result in a file.

int main() {
    int n;
    float credit, gradePoint, totalCredits = 0, totalGradePoints = 0;
    string grade;

    ofstream file("cgpa_record.txt");   // File to store data

    cout << "Enter number of subjects: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cout << "\nSubject " << i << endl;

        cout << "Enter credits: ";
        cin >> credit;

        cout << "Enter grade (A, B, C, D, F): ";
        cin >> grade;

        // Convert grade to grade point
        if (grade == "A")
            gradePoint = 10;
        else if (grade == "B")
            gradePoint = 8;
        else if (grade == "C")
            gradePoint = 6;
        else if (grade == "D")
            gradePoint = 4;
        else
            gradePoint = 0;

        totalCredits = totalCredits + credit;
        totalGradePoints = totalGradePoints + (credit * gradePoint);

        // Save each subject data to file
        file << "Subject " << i << " | Credits: " << credit 
             << " | Grade: " << grade 
             << " | Grade Point: " << gradePoint << endl;
    }

    float gpa = totalGradePoints / totalCredits;

    cout << "\nTotal Credits = " << totalCredits << endl;
    cout << "Total Grade Points = " << totalGradePoints << endl;
    cout << "Your GPA / CGPA = " << gpa << endl;

    file << "\nTotal Credits = " << totalCredits << endl;
    file << "Total Grade Points = " << totalGradePoints << endl;
    file << "Final CGPA = " << gpa << endl;

    file.close();

    cout << "\nResult saved in file: cgpa_record.txt" << endl;

    return 0;
}
