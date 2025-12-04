

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LEN 64
#define DISEASE_LEN 64
#define CONTACT_LEN 16
#define DATE_LEN 12
#define GENDER_LEN 10

/* ---------------------- STRUCTURE ---------------------- */

typedef struct Patient {
    int patientID;
    char name[NAME_LEN];
    int age;
    char gender[GENDER_LEN];
    char contact[CONTACT_LEN];
    char disease[DISEASE_LEN];
    char admitDate[DATE_LEN];
    struct Patient *next;
} Patient;

Patient *head = NULL;

/* ---------------------- UTILITIES ---------------------- */

void trim_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

int getValidPositiveInteger(const char *prompt) {
    char buf[128];
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) continue;

        trim_newline(buf);
        if (strlen(buf) == 0) {
            printf("Input required.\n"); continue;
        }

        int valid = 1;
        for (size_t i = 0; i < strlen(buf); i++) {
            if (!isdigit((unsigned char)buf[i])) { valid = 0; break; }
        }

        if (!valid) {
            printf("Invalid! Only digits allowed.\n");
            continue;
        }

        long v = strtol(buf, NULL, 10);
        if (v <= 0) {
            printf("Value must be > 0.\n");
            continue;
        }

        return (int)v;
    }
}

void getValidAlphaSpace(const char *prompt, char *out, size_t outlen) {
    char buf[256];
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) continue;

        trim_newline(buf);
        if (strlen(buf) == 0) {
            printf("Input required.\n");
            continue;
        }

        int valid = 1;
        for (size_t i = 0; buf[i]; i++) {
            if (!isalpha((unsigned char)buf[i]) && buf[i] != ' ') {
                valid = 0; break;
            }
        }

        if (!valid) {
            printf("Only alphabets and spaces allowed.\n");
            continue;
        }

        strncpy(out, buf, outlen - 1);
        out[outlen - 1] = '\0';
        return;
    }
}

void getValidGender(char *out, size_t outlen) {
    char buf[64];
    while (1) {
        printf("Enter Gender (Male/Female/Others): ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;

        trim_newline(buf);
        if (strlen(buf) == 0) continue;

        char temp[64];
        for (size_t i = 0; buf[i]; i++)
            temp[i] = tolower(buf[i]);
        temp[strlen(buf)] = '\0';

        if (strcmp(temp, "male") == 0 || strcmp(temp, "m") == 0) {
            strcpy(out, "Male");
            return;
        }
        if (strcmp(temp, "female") == 0 || strcmp(temp, "f") == 0) {
            strcpy(out, "Female");
            return;
        }
        if (strcmp(temp, "others") == 0 || strcmp(temp, "other") == 0 || strcmp(temp, "o") == 0) {
            strcpy(out, "Others");
            return;
        }

        printf("Invalid gender! Try again.\n");
    }
}

void getValidContact(char *out, size_t outlen) {
    char buf[64];
    while (1) {
        printf("Enter Contact (10 digits): ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;

        trim_newline(buf);
        if (strlen(buf) != 10) {
            printf("Contact must be exactly 10 digits.\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(buf[i])) { valid = 0; break; }
        }

        if (!valid) {
            printf("Only digits allowed.\n");
            continue;
        }

        strcpy(out, buf);
        return;
    }
}

/* YYYY/MM/DD validation */
int validDateParts(int y, int m, int d) {
    if (y < 1900 || y > 9999) return 0;
    if (m < 1 || m > 12) return 0;

    int mdays = 31;
    if (m == 2) {
        int leap = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
        mdays = leap ? 29 : 28;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        mdays = 30;
    }

    if (d < 1 || d > mdays) return 0;
    return 1;
}

void getValidDate(char *out, size_t outlen) {
    char buf[64];
    while (1) {
        printf("Enter Admit Date (YYYY/MM/DD): ");
        if (!fgets(buf, sizeof(buf), stdin)) continue;

        trim_newline(buf);

        if (strlen(buf) != 10 || buf[4] != '/' || buf[7] != '/') {
            printf("Invalid format.\n");
            continue;
        }

        if (!isdigit(buf[0]) || !isdigit(buf[1]) || !isdigit(buf[2]) || !isdigit(buf[3]) ||
            !isdigit(buf[5]) || !isdigit(buf[6]) || !isdigit(buf[8]) || !isdigit(buf[9])) {
            printf("Date contains invalid characters.\n");
            continue;
        }

        int y = atoi(&buf[0]);
        int m = atoi(&buf[5]);
        int d = atoi(&buf[8]);

        if (!validDateParts(y, m, d)) {
            printf("Invalid date.\n");
            continue;
        }

        strcpy(out, buf);
        return;
    }
}

/* ---------------------- LINKED LIST OPERATIONS ---------------------- */

int idExists(int id) {
    Patient *p = head;
    while (p) {
        if (p->patientID == id) return 1;
        p = p->next;
    }
    return 0;
}

void addPatient() {
    Patient *n = malloc(sizeof(Patient));
    if (!n) {
        printf("Memory error.\n");
        return;
    }

    while (1) {
        n->patientID = getValidPositiveInteger("Enter Patient ID: ");
        if (!idExists(n->patientID)) break;
        printf("ID already exists! Try again.\n");
    }

    getValidAlphaSpace("Enter Name: ", n->name, NAME_LEN);
    n->age = getValidPositiveInteger("Enter Age: ");
    getValidGender(n->gender, GENDER_LEN);
    getValidContact(n->contact, CONTACT_LEN);
    getValidAlphaSpace("Enter Disease: ", n->disease, DISEASE_LEN);
    getValidDate(n->admitDate, DATE_LEN);

    n->next = NULL;

    if (!head) head = n;
    else {
        Patient *p = head;
        while (p->next) p = p->next;
        p->next = n;
    }

    printf("✔ Patient added successfully!\n");
}

void displayAll() {
    if (!head) {
        printf("No records.\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    printf("%-6s %-20s %-4s %-8s %-12s %-15s %-10s\n",
           "ID", "Name", "Age", "Gender", "Contact", "Disease", "AdmitDate");

    printf("-------------------------------------------------------------------------------\n");

    Patient *p = head;
    while (p) {
        printf("%-6d %-20s %-4d %-8s %-12s %-15s %-10s\n",
               p->patientID, p->name, p->age,
               p->gender, p->contact, p->disease, p->admitDate);
        p = p->next;
    }
}

Patient* searchByID(int id) {
    Patient *p = head;
    while (p) {
        if (p->patientID == id) return p;
        p = p->next;
    }
    return NULL;
}

void searchPatient() {
    int id = getValidPositiveInteger("Enter Patient ID to search: ");
    Patient *p = searchByID(id);

    if (!p) {
        printf("Patient not found.\n");
        return;
    }

    printf("\nPatient Found:\n");
    printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nContact: %s\nDisease: %s\nAdmit Date: %s\n",
           p->patientID, p->name, p->age,
           p->gender, p->contact, p->disease, p->admitDate);
}

void modifyPatient() {
    int id = getValidPositiveInteger("Enter Patient ID to modify: ");
    Patient *p = searchByID(id);

    if (!p) {
        printf("Patient not found.\n");
        return;
    }

    printf("\nRe-enter all details:\n");

    getValidAlphaSpace("New Name: ", p->name, NAME_LEN);
    p->age = getValidPositiveInteger("New Age: ");
    getValidGender(p->gender, GENDER_LEN);
    getValidContact(p->contact, CONTACT_LEN);
    getValidAlphaSpace("New Disease: ", p->disease, DISEASE_LEN);
    getValidDate(p->admitDate, DATE_LEN);

    printf("✔ Record updated.\n");
}

void deletePatient() {
    int id = getValidPositiveInteger("Enter Patient ID to delete: ");

    Patient *cur = head;
    Patient *prev = NULL;

    while (cur && cur->patientID != id) {
        prev = cur;
        cur = cur->next;
    }

    if (!cur) {
        printf("Patient not found.\n");
        return;
    }

    if (!prev) head = cur->next;
    else prev->next = cur->next;

    free(cur);

    printf("✔ Record deleted.\n");
}

/* ---------------------- MAIN MENU ---------------------- */

int main() {
    while (1) {
        printf("\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Modify Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");

        int ch = getValidPositiveInteger("Enter choice: ");

        switch (ch) {
            case 1: addPatient(); break;
            case 2: displayAll(); break;
            case 3: searchPatient(); break;
            case 4: modifyPatient(); break;
            case 5: deletePatient(); break;
            case 6: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
