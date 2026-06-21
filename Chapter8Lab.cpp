
// Name: Sunny Rodrigues
// File: Chapter8Lab.cpp
// Description: Chapter 8 Lab - Roster Report

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;

// Function prototypes
void readRoster(char names[][31], int scores[][NUM_TESTS], int& count);
void calcAverages(const int scores[][NUM_TESTS], double averages[],
                  char grades[], int count);
void sortRoster(char names[][31], int scores[][NUM_TESTS],
                double averages[], char grades[], int count);
int searchRoster(const char names[][31], int count, const char target[]);
void printRoster(const char names[][31], const int scores[][NUM_TESTS],
                 const double averages[], const char grades[], int count);
void printStats(const double averages[], int count);

int main()
{
    char names[MAX_STUDENTS][31];
    int scores[MAX_STUDENTS][NUM_TESTS];
    double averages[MAX_STUDENTS] = {0};
    char grades[MAX_STUDENTS] = {'F'};

    int count = 0;
    int choice;

    do
    {
        cout << "\n===== Roster Report Menu =====\n";
        cout << "1. Load roster (enter data)\n";
        cout << "2. Calculate averages and grades\n";
        cout << "3. Sort roster alphabetically\n";
        cout << "4. Search for a student\n";
        cout << "5. Print roster\n";
        cout << "6. Print class statistics\n";
        cout << "7. Quit\n";
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore(1000, '\n');

        switch (choice)
        {
            case 1:
                readRoster(names, scores, count);
                break;

            case 2:
                calcAverages(scores, averages, grades, count);
                cout << "\nAverages and grades calculated.\n";
                break;

            case 3:
                sortRoster(names, scores, averages, grades, count);
                cout << "\nRoster sorted alphabetically.\n";
                break;

            case 4:
            {
                char target[31];

                cout << "\nEnter student name to search: ";
                cin.getline(target, 31);

                int index = searchRoster(names, count, target);

                if (index != -1)
                {
                    cout << "Student found at index "
                         << index << ".\n";
                }
                else
                {
                    cout << "Student not found.\n";
                }

                break;
            }

            case 5:
                printRoster(names, scores, averages, grades, count);
                break;

            case 6:
                printStats(averages, count);
                break;

            case 7:
                cout << "\nProgram terminated.\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}

void readRoster(char names[][31], int scores[][NUM_TESTS], int& count)
{
    do
    {
        cout << "Enter number of students (1-10): ";
        cin >> count;
    }
    while (count < 1 || count > MAX_STUDENTS);

    cin.ignore(1000, '\n');

    for (int i = 0; i < count; i++)
    {
        cout << "\nEnter student #" << (i + 1) << " name: ";
        cin.getline(names[i], 31);

        for (int j = 0; j < NUM_TESTS; j++)
        {
            cout << "Enter test score "
                 << (j + 1) << ": ";
            cin >> scores[i][j];
        }

        cin.ignore(1000, '\n');
    }
}

void calcAverages(const int scores[][NUM_TESTS],
                  double averages[],
                  char grades[],
                  int count)
{
    for (int i = 0; i < count; i++)
    {
        int total = 0;

        for (int j = 0; j < NUM_TESTS; j++)
        {
            total += scores[i][j];
        }

        averages[i] = static_cast<double>(total) / NUM_TESTS;

        if (averages[i] >= 90)
            grades[i] = 'A';
        else if (averages[i] >= 80)
            grades[i] = 'B';
        else if (averages[i] >= 70)
            grades[i] = 'C';
        else if (averages[i] >= 60)
            grades[i] = 'D';
        else
            grades[i] = 'F';
    }
}

void sortRoster(char names[][31],
                int scores[][NUM_TESTS],
                double averages[],
                char grades[],
                int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(names[j], names[minIndex]) < 0)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            char tempName[31];
            strcpy(tempName, names[i]);
            strcpy(names[i], names[minIndex]);
            strcpy(names[minIndex], tempName);

            for (int k = 0; k < NUM_TESTS; k++)
            {
                int tempScore = scores[i][k];
                scores[i][k] = scores[minIndex][k];
                scores[minIndex][k] = tempScore;
            }

            double tempAverage = averages[i];
            averages[i] = averages[minIndex];
            averages[minIndex] = tempAverage;

            char tempGrade = grades[i];
            grades[i] = grades[minIndex];
            grades[minIndex] = tempGrade;
        }
    }
}

int searchRoster(const char names[][31],
                 int count,
                 const char target[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], target) == 0)
        {
            return i;
        }
    }

    return -1;
}

void printRoster(const char names[][31],
                 const int scores[][NUM_TESTS],
                 const double averages[],
                 const char grades[],
                 int count)
{
    cout << fixed << setprecision(2);

    cout << "\n============================== ROSTER ==============================\n";

    cout << left
         << setw(25) << "Name"
         << setw(8) << "T1"
         << setw(8) << "T2"
         << setw(8) << "T3"
         << setw(8) << "T4"
         << setw(12) << "Average"
         << setw(8) << "Grade"
         << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left
             << setw(25) << names[i]
             << setw(8) << scores[i][0]
             << setw(8) << scores[i][1]
             << setw(8) << scores[i][2]
             << setw(8) << scores[i][3]
             << setw(12) << averages[i]
             << setw(8) << grades[i]
             << endl;
    }
}

void printStats(const double averages[], int count)
{
    if (count == 0)
    {
        cout << "\nNo roster data available.\n";
        return;
    }

    double localCopy[MAX_STUDENTS] = {0};

    for (int i = 0; i < count; i++)
    {
        localCopy[i] = averages[i];
    }

    double high = averages[0];
    double low = averages[0];
    double total = 0.0;

    int validCount = 0;

    for (auto value : localCopy)
    {
        if (validCount < count)
        {
            total += value;

            if (value > high)
                high = value;

            if (value < low)
                low = value;

            validCount++;
        }
    }

    cout << fixed << setprecision(2);

    cout << "\nClass Statistics\n";
    cout << "Highest Average: " << high << endl;
    cout << "Lowest Average : " << low << endl;
    cout << "Class Average  : "
         << total / count << endl;
}