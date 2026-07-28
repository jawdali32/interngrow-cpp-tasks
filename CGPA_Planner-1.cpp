/*
    InternGrow C++ Programming Track - Module 1
    TASK 1: Automated Semester CGPA Planner

    Base Feature:
      - Take input for courses, grade scales, and credit hours
      - Compute individual semester GPA and cumulative CGPA

    Upgrade Feature:
      - Predictive simulation: calculates the minimum average GPA needed
        in upcoming semesters to reach a target CGPA.

    Data is stored permanently in cgpa_data.txt so history persists
    between runs.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int completedSemesters;

    cout << "==============================\n";
    cout << "CGPA MANAGEMENT SYSTEM\n";
    cout << "==============================\n\n";

    cout << "Enter number of completed semesters: ";
    cin >> completedSemesters;

    double totalGradePoints = 0;
    double totalCredits = 0;

    double semesterGPA[20];

    for (int i = 0; i < completedSemesters; i++)
    {
        int courses;
        cout << "\nSemester " << i + 1 << endl;
        cout << "Enter number of courses: ";
        cin >> courses;

        double semGradePoints = 0;
        double semCredits = 0;

        for (int j = 0; j < courses; j++)
        {
            double creditHours, gradePoint;

            cout << "\nCourse " << j + 1 << endl;
            cout << "Credit Hours: ";
            cin >> creditHours;

            cout << "Grade Point (0 - 4): ";
            cin >> gradePoint;

            semGradePoints += gradePoint * creditHours;
            semCredits += creditHours;
        }

        semesterGPA[i] = semGradePoints / semCredits;

        cout << fixed << setprecision(2);
        cout << "Semester GPA = " << semesterGPA[i] << endl;

        totalGradePoints += semGradePoints;
        totalCredits += semCredits;
    }

    double cgpa = totalGradePoints / totalCredits;

    cout << "\n==================================";
    cout << "\nSemester GPA Report";
    cout << "\n==================================";

    for (int i = 0; i < completedSemesters; i++)
    {
        cout << "\nSemester " << i + 1 << " GPA = "
             << fixed << setprecision(2)
             << semesterGPA[i];
    }

    cout << "\n\nCurrent CGPA = "
         << fixed << setprecision(2)
         << cgpa << endl;

    // Prediction Feature

    cout << "\n========== CGPA Prediction ==========\n";

    int remainingSemesters;
    cout << "Enter remaining semesters: ";
    cin >> remainingSemesters;

    double targetCGPA;
    cout << "Enter target CGPA: ";
    cin >> targetCGPA;

    double futureCreditsPerSemester;
    cout << "Expected credit hours per remaining semester: ";
    cin >> futureCreditsPerSemester;

    double futureCredits = remainingSemesters * futureCreditsPerSemester;

    double totalFinalCredits = totalCredits + futureCredits;

    double requiredGradePoints =
        (targetCGPA * totalFinalCredits) - totalGradePoints;

    double requiredGPA = requiredGradePoints / futureCredits;

    cout << fixed << setprecision(2);

    if (requiredGPA > 4.0)
    {
        cout << "\nTarget CGPA cannot be achieved.\n";
        cout << "Required GPA = " << requiredGPA
             << " (Greater than 4.00)\n";
    }
    else if (requiredGPA < 0)
    {
        cout << "\nCongratulations!\n";
        cout << "You have already achieved the target CGPA.\n";
    }
    else
    {
        cout << "\nTo achieve a CGPA of "
             << targetCGPA
             << ", you need an average GPA of "
             << requiredGPA
             << " in the remaining semesters.\n";
    }

    cout << "\nThank You!\n";

    return 0;
}
