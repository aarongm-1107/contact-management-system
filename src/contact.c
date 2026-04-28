#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ================= STRUCT =================
struct Contact
{
    char name[50];
    char phone[15];
    struct Contact *next;
};

struct Contact *head = NULL;

// ================= COLOR =================
void setColor() { system("color 0A"); }

// ================= LOADING =================
void loading()
{
    printf("\nProcessing");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        Sleep(300);
    }
}

// ================= COUNT =================
int countContacts()
{
    int count = 0;
    struct Contact *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// ================= DUPLICATE =================
int isDuplicate(char phone[])
{
    struct Contact *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->phone, phone) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// ================= SORT =================
void sortAscending()
{
    struct Contact *i, *j;
    char name[50], phone[15];

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->name, j->name) > 0)
            {
                strcpy(name, i->name);
                strcpy(phone, i->phone);

                strcpy(i->name, j->name);
                strcpy(i->phone, j->phone);

                strcpy(j->name, name);
                strcpy(j->phone, phone);
            }
        }
    }
}

void sortDescending()
{
    struct Contact *i, *j;
    char name[50], phone[15];

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->name, j->name) < 0)
            {
                strcpy(name, i->name);
                strcpy(phone, i->phone);

                strcpy(i->name, j->name);
                strcpy(i->phone, j->phone);

                strcpy(j->name, name);
                strcpy(j->phone, phone);
            }
        }
    }
}

// ================= FILE =================
void saveToFile()
{
    FILE *fp = fopen("contacts.txt", "w");
    struct Contact *temp = head;

    while (temp != NULL)
    {
        fprintf(fp, "%s,%s\n", temp->name, temp->phone);
        temp = temp->next;
    }
    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen("contacts.txt", "r");
    if (!fp)
        return;

    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        struct Contact *newNode = malloc(sizeof(struct Contact));
        sscanf(line, "%[^,],%[^\n]", newNode->name, newNode->phone);
        newNode->next = head;
        head = newNode;
    }
    fclose(fp);
}

// ================= UTIL =================
void clear() { system("cls"); }

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    getchar();
}

void inputString(char *str, int size)
{
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}

// ================= PARTIAL SELECT =================
struct Contact *selectContactByPartial(char partial[])
{
    struct Contact *temp = head;
    struct Contact *matches[100];
    int count = 0;

    while (temp != NULL)
    {
        if (strstr(temp->name, partial) != NULL)
        {
            matches[count++] = temp;
        }
        temp = temp->next;
    }

    if (count == 0)
    {
        printf("\n❌ No matching contacts!\n");
        return NULL;
    }

    printf("\n===== MATCHES =====\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s (%s)\n", i + 1, matches[i]->name, matches[i]->phone);
    }

    int choice;
    printf("Select contact: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > count)
    {
        printf("\n❌ Invalid choice!\n");
        return NULL;
    }

    return matches[choice - 1];
}

// ================= ADD =================
void addContact()
{
    struct Contact *newNode = malloc(sizeof(struct Contact));

    clear();
    printf("\n===== ADD CONTACT =====\n");

    printf("Enter Name  : ");
    getchar();
    inputString(newNode->name, 50);

    printf("Enter Phone : ");
    inputString(newNode->phone, 15);

    if (isDuplicate(newNode->phone))
    {
        printf("\n❌ Duplicate phone number!\n");
        free(newNode);
        pauseScreen();
        return;
    }

    newNode->next = head;
    head = newNode;

    saveToFile();
    loading();

    printf("\n✔ Contact Added!\n");
    pauseScreen();
}

// ================= DISPLAY =================
void displayContacts()
{
    int choice;

    clear();
    printf("\n===== SORT OPTIONS =====\n");
    printf("1. Sort A-Z\n2. Sort Z-A\n3. No Sort\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1)
        sortAscending();
    else if (choice == 2)
        sortDescending();

    struct Contact *temp = head;

    clear();
    printf("\n===== CONTACT LIST =====\n");

    int i = 1;
    while (temp != NULL)
    {
        printf("\n[%d]\nName  : %s\nPhone : %s\n", i++, temp->name, temp->phone);
        temp = temp->next;
    }

    printf("\nTotal Contacts: %d\n", countContacts());
    pauseScreen();
}

// ================= SEARCH =================
void searchContact()
{
    int choice;
    char input[50];
    struct Contact *temp;

    clear();
    printf("\n===== ADVANCED SEARCH =====\n");
    printf("1. Exact Name\n2. Partial Name\n3. Phone Number\n4. Back\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 4)
        return;

    printf("Enter value: ");
    getchar();
    inputString(input, 50);

    temp = head;
    int found = 0;

    while (temp != NULL)
    {
        if ((choice == 1 && strcmp(temp->name, input) == 0) ||
            (choice == 2 && strstr(temp->name, input) != NULL) ||
            (choice == 3 && strcmp(temp->phone, input) == 0))
        {
            printf("\n%s - %s\n", temp->name, temp->phone);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("\n❌ Not Found\n");

    pauseScreen();
}

// ================= DELETE =================
void deleteContact()
{
    char input[50];

    clear();
    printf("\n===== DELETE CONTACT =====\n");

    printf("Enter partial name: ");
    getchar();
    inputString(input, 50);

    struct Contact *target = selectContactByPartial(input);
    if (target == NULL)
    {
        pauseScreen();
        return;
    }

    struct Contact *temp = head, *prev = NULL;

    while (temp != NULL)
    {
        if (temp == target)
        {
            char ch;
            printf("Confirm delete (y/n): ");
            scanf(" %c", &ch);

            if (ch != 'y' && ch != 'Y')
                return;

            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            saveToFile();
            loading();

            printf("\nDeleted\n");
            pauseScreen();
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// ================= UPDATE (FIXED) =================
void updateContact()
{
    char input[50];

    clear();
    printf("\n===== UPDATE CONTACT =====\n");

    printf("Enter partial name: ");
    getchar();
    inputString(input, 50);

    struct Contact *temp = selectContactByPartial(input);
    if (temp == NULL)
    {
        pauseScreen();
        return;
    }

    getchar(); // 🔥 FIXED HERE

    printf("Enter New Name: ");
    inputString(temp->name, 50);

    printf("Enter New Phone: ");
    inputString(temp->phone, 15);

    saveToFile();
    loading();

    printf("\n✔ Updated\n");
    pauseScreen();
}

// ================= STATS =================
void showStats()
{
    clear();
    printf("\n===== STATS =====\n");
    printf("Total Contacts: %d\n", countContacts());

    if (head != NULL)
        printf("Latest Contact: %s\n", head->name);

    pauseScreen();
}

// ================= DASHBOARD =================
void dashboard()
{
    clear();
    printf("========================================\n");
    printf("     CONTACT MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Total Contacts: %d\n", countContacts());
    printf("========================================\n");
    printf("1. Manage Contacts\n");
    printf("2. Advanced Search\n");
    printf("3. View All Contacts\n");
    printf("4. Stats\n");
    printf("5. Exit\n");
}

// ================= SUB MENU =================
void manageMenu()
{
    clear();
    printf("========================================\n");
    printf("         CONTACT OPERATIONS\n");
    printf("========================================\n");
    printf("1. Add Contact\n");
    printf("2. Delete Contact\n");
    printf("3. Update Contact\n");
    printf("4. Back\n");
}

// ================= MAIN =================
int main()
{
    int choice, subChoice;

    setColor();
    loadFromFile();

    clear();
    printf("========================================\n");
    printf("     CONTACT MANAGEMENT SYSTEM\n");
    printf("         Aaron & Ann\n");
    printf("========================================\n");
    printf("\nPress Enter to start...");
    getchar();
    loading();

    while (1)
    {
        dashboard();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            while (1)
            {
                manageMenu();
                printf("Enter choice: ");
                scanf("%d", &subChoice);

                if (subChoice == 1)
                    addContact();
                else if (subChoice == 2)
                    deleteContact();
                else if (subChoice == 3)
                    updateContact();
                else
                    break;
            }
            break;

        case 2:
            searchContact();
            break;
        case 3:
            displayContacts();
            break;
        case 4:
            showStats();
            break;
        case 5:
            exit(0);
        }
    }
}