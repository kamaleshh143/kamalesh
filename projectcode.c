#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "student_data.txt"

typedef struct {
    int regNo;
    char name[50];
    float cgpa;
    int backlogs;
    int skills;
    int pin;
    int isEligible;
} Student;

Student list[MAX];
int count = 0;

int findStudent(int regNo);
int checkEligibility(Student s);
void updateEligibility(Student *s);
void loadFromFile();
void saveToFile();
void addStudent();
void viewAll();
void searchStudent();
void displayEligible();
void checkMyStatus();
void menu();

int findStudent(int regNo) {
    for (int i = 0; i < count; i++) {
        if (list[i].regNo == regNo)
            return i;
    }
    return -1;
}

int checkEligibility(Student s) {
    return (s.cgpa >= 7.0 && s.backlogs == 0 && s.skills >= 2);
}

void updateEligibility(Student *s) {
    s->isEligible = checkEligibility(*s);
}

void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    count = 0;

    if (fp == NULL)
        return;

    while (count < MAX &&
           fscanf(fp, "%d %49s %f %d %d %d %d",
                  &list[count].regNo,
                  list[count].name,
                  &list[count].cgpa,
                  &list[count].backlogs,
                  &list[count].skills,
                  &list[count].pin,
                  &list[count].isEligible) == 7) {
        count++;
    }

    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.2f %d %d %d %d\n",
                list[i].regNo,
                list[i].name,
                list[i].cgpa,
                list[i].backlogs,
                list[i].skills,
                list[i].pin,
                list[i].isEligible);
    }

    fclose(fp);
}

void addStudent() {
    if (count >= MAX) {
        printf("Student limit reached!\n");
        return;
    }

    Student s;

    printf("\n--- Add Student ---\n");
    printf("Enter Register Number: ");
    scanf("%d", &s.regNo);

    if (findStudent(s.regNo) != -1) {
        printf("Student with this Register Number already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf("%49s", s.name);

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);

    printf("Enter Number of Backlogs: ");
    scanf("%d", &s.backlogs);

    printf("Enter Number of Skills: ");
    scanf("%d", &s.skills);

    printf("Set 4-digit PIN: ");
    scanf("%d", &s.pin);

    updateEligibility(&s);

    list[count++] = s;
    saveToFile();

    printf("Student added successfully!\n");
}

void viewAll() {
    if (count == 0) {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- All Students ---\n");
    for (int i = 0; i < count; i++) {
        printf("RegNo: %d | Name: %s | CGPA: %.2f | Backlogs: %d | Skills: %d | Eligible: %s\n",
               list[i].regNo,
               list[i].name,
               list[i].cgpa,
               list[i].backlogs,
               list[i].skills,
               list[i].isEligible ? "Yes" : "No");
    }
}

void searchStudent() {
    int regNo, pin;
    printf("\nEnter Register Number to search: ");
    scanf("%d", &regNo);

    int i = findStudent(regNo);

    if (i == -1) {
        printf("Student not found!\n");
        return;
    }

   /*printf("Enter PIN: ");
    scanf("%d", &pin);

    if (list[i].pin != pin) {
        printf("Invalid PIN!\n");
        return;
    }*/

    printf("\n--- Student Found ---\n");
    printf("RegNo: %d\n", list[i].regNo);
    printf("Name: %s\n", list[i].name);
    printf("CGPA: %.2f\n", list[i].cgpa);
    printf("Backlogs: %d\n", list[i].backlogs);
    printf("Skills: %d\n", list[i].skills);
    printf("Eligible: %s\n", list[i].isEligible ? "Yes" : "No");
}

void displayEligible() {
    int found = 0;

    printf("\n--- Eligible Students ---\n");
    for (int i = 0; i < count; i++) {
        if (list[i].isEligible) {
            printf("RegNo: %d | Name: %s | CGPA: %.2f\n",
                   list[i].regNo,
                   list[i].name,
                   list[i].cgpa);
            found = 1;
        }
    }

    if (!found) {
        printf("No eligible students found!\n");
    }
}

void checkMyStatus() {
    int regNo, pin;
    printf("\nEnter Register Number: ");
    scanf("%d", &regNo);

    int i = findStudent(regNo);

    if (i == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (list[i].pin != pin) {
        printf("Invalid PIN!\n");
        return;
    }

    printf("\n--- Placement Status ---\n");
    printf("Name: %s\n", list[i].name);
    printf("Eligible: %s\n", list[i].isEligible ? "Yes" : "No");
}

void menu() {
    int choice;

    while (1) {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search by Register Number\n");
        printf("4. Display Eligible Students\n");
        printf("5. Check My Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAll(); break;
            case 3: searchStudent(); break;
            case 4: displayEligible(); break;
            case 5: checkMyStatus(); break;
            case 6:
                saveToFile();
                printf("Thank you!\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

int main() {
    loadFromFile();
    menu();
    return 0;
}git remote add origin https://github.com/kamaleshh143/kamalesh.git