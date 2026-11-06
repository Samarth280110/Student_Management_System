
#include <stdio.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

struct Student s[100];
int count = 0;

void line() {
    printf("-------------------------------------\n");
}

void load() {
    FILE *f = fopen("data", "r");
    if (f == NULL) return;

    while (count < 100 &&
           fscanf(f, "%d %49s %f",
           &s[count].roll, s[count].name,
           &s[count].marks) == 3) {
        count++;
    }

    fclose(f);
}

void save() {
    FILE *f = fopen("data", "w");
    if (f == NULL) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d %s %.2f\n",
                s[i].roll, s[i].name, s[i].marks);
    }

    fclose(f);
}

int getInt(char msg[]) {
    int n;
    char ch;

    printf("%s", msg);
    while (scanf("%d%c", &n, &ch) != 2 || ch != '\n') {
        while (getchar() != '\n');
        printf("Enter a valid number: ");
    }

    return n;
}

float getMarks() {
    float m;
    char ch;

    printf("Enter marks: ");
    while (scanf("%f%c", &m, &ch) != 2 ||
           ch != '\n' || m < 0 || m > 100) {
        while (getchar() != '\n');
        printf("Enter marks between 0 and 100: ");
    }

    return m;
}

int find(int roll) {
    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll)
            return i;
    }

    return -1;
}

void add() {
    if (count >= 100) {
        printf("Student limit reached!\n");
        return;
    }

    int roll = getInt("Enter roll number: ");

    if (roll <= 0 || find(roll) != -1) {
        printf("Invalid or duplicate roll number!\n");
        return;
    }

    s[count].roll = roll;

    printf("Enter name: ");
    scanf(" %49[^\n]", s[count].name);

    s[count].marks = getMarks();

    count++;
    save();

    printf("Student added successfully!\n");
}

void display() {
    if (count == 0) {
        printf("No records found!\n");
        return;
    }

    line();
    printf("          STUDENT RECORDS\n");
    line();

    for (int i = 0; i < count; i++) {
        printf("Roll: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);
        printf("Marks: %.2f\n", s[i].marks);
        line();
    }
}

void search() {
    int roll = getInt("Enter roll number to search: ");
    int i = find(roll);

    if (i == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Name: %s\n", s[i].name);
    printf("Marks: %.2f\n", s[i].marks);
}

void edit() {
    int roll = getInt("Enter roll number to edit: ");
    int i = find(roll);

    if (i == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter new name: ");
    scanf(" %49[^\n]", s[i].name);

    s[i].marks = getMarks();

    save();
    printf("Student updated successfully!\n");
}

int main() {
    int choice;

    load();

    do {
        printf("\n===== STUDENT MANAGEMENT =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Edit Student\n");
        printf("5. Exit\n");

        choice = getInt("Enter choice: ");

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: edit(); break;
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
