#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include <string.h>
#include <fstream.h>
#include <alloc.h>
#define FILE_NAME "C:\\TURBOC3\\Projects\\csc\\birthday.dat"
struct birthday
{
    char name[50];
    int day;
    int month;
    birthday *next;
    birthday *prev;
};
struct birthday *list;
void getBirthdayDetails(struct birthday *bDay)
{
    char name[50];
    int day, month;

    printf("Enter the Name: ");
    do
    {
        gets(name);
    } while (strlen(name) < 3);

    do
    {
        printf("Enter Birthday (dd/MM) (e.g. 06/04 for 6th April): ");
    } while (scanf("\n%d/%d", &day, &month) != 2);

    strcpy(bDay->name, name);
    bDay->day = day;
    bDay->month = month;
}
struct birthday *getBirthday()
{
    struct birthday *newBirthday;
    newBirthday = (struct birthday *)malloc(sizeof(struct birthday));

    getBirthdayDetails(newBirthday);

    newBirthday->next = NULL;
    newBirthday->prev = NULL;
    return newBirthday;
}
int pushItemToLinkedList(struct birthday *newBirthday)
{
    struct birthday *prev, *cur;
    if (list == NULL)
    {
        list = newBirthday; //first node in list
        return 1;
    }
    for (prev = NULL, cur = list; (cur); prev = cur, cur = cur->next)
    {

        if (
            (cur->month > newBirthday->month) ||
            (cur->month == newBirthday->month && cur->day > newBirthday->day) ||
            (cur->month == newBirthday->month && cur->day == newBirthday->day && strcmp(cur->name, newBirthday->name) > 0))
            break;
    }

    newBirthday->prev = prev;
    if (cur)
    {
        cur->prev = newBirthday;
        newBirthday->next = cur;
    }
    if (prev)
        prev->next = newBirthday;
    else
        list = newBirthday;

    return 0;
}
void popItemFromLinkedList(struct birthday *itemToBeRemoved)
{
    struct birthday *next = itemToBeRemoved->next;
    struct birthday *prev = itemToBeRemoved->prev;

    if (next != NULL && prev != NULL)
    {
        prev->next = itemToBeRemoved->next;
        next->prev = itemToBeRemoved->prev;
    }
    else if (prev != NULL)
    {
        prev->next = NULL;
    }
    else if (next != NULL)
    {
        next->prev = NULL;
        list = next;
    }
}
void showAllBirthdays()
{
    struct birthday *cur;
    int n = 0;

    if (list == NULL)
    {
        printf("No Birthdays to show!");
        return;
    }
    cur = list;
    printf("Birthday    Name\n");
    for (cur = list; (cur); cur = cur->next)
    {
        printf("%d/%d           %s\n", cur->day, cur->month, cur->name);
        n++;
    }
}
struct birthday **find(int day, int month, char name[50], int toggle, int *iResultCount)
{
    struct birthday *results[50];
    *iResultCount = 0;

    struct birthday *cur, *prev;
    if (list == NULL)
        return NULL;

    for (prev = NULL, cur = list; (cur); prev = cur, cur = cur->next)
    {
        if ((toggle == 1 && cur->month == month && cur->day == day) ||
            (toggle == 2 && cur->month == month) ||
            (toggle == 3 && strstr(cur->name, name) != NULL))
        {
            results[*iResultCount] = cur;
            *iResultCount += 1;
        }
    }
    return results;
}
struct birthday *GetDataFromFile()
{
    struct birthday *root;
    struct birthday *prev;
    birthday *cur;
    prev = root = NULL;

    ifstream file;
    file.open(FILE_NAME, ios::in | ios::binary);
    if (file)
    {
        cur = new birthday;
        file.read((char *)cur, sizeof(*cur));
        while (!file.eof())
        {
            cur->next = NULL;
            cur->prev = prev;
            if (prev)
            {
                prev->next = cur;
            }
            else
            {
                root = cur;
            }
            prev = cur;
            cur = new birthday;
            file.read((char *)cur, sizeof(*cur));
        }
        file.close();
    }
    return root;
}
void SaveFile()
{
    ofstream file;
    struct birthday *cur;
    file.open(FILE_NAME, ios::out | ios::binary);
    if (!file)
    {
        cout << "Error in creating file...\n";
        return;
    }
    for (cur = list; (cur); cur = cur->next)
    {
        file.write((char *)cur, sizeof(*cur));
    }
    file.close();
}
void main()
{
    int ch = 0;
    struct birthday *birthday1, *birthday2;
    list = GetDataFromFile();

    do
    {
        clrscr();
        cout << "Menu" << endl;
        cout << "1. Add a New Birthday" << endl;
        cout << "2. Delete an existing Birthday" << endl;
        cout << "3. Show all Birthdays" << endl;
        cout << "4. Modify a Birthday" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice:  ";
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            struct birthday *newBirthday = getBirthday();
            pushItemToLinkedList(newBirthday);
            printf("Birthday accepted successfully");
            break;
        case 3:
            showAllBirthdays();
            break;
        case 2:
        case 4:
            int searchChoice = 0;
            printf("Search by Birthday (1), Month (2) or Name (3)?     ");
            scanf("\n%d", &searchChoice);
            int day;
            int month;
            day = month = 0;
            char nameToFind[50];
            if (searchChoice == 1)
            {
                do
                {
                    printf("Enter Birthday (dd/MM) (e.g. 06/04 for 6th April): ");
                } while (scanf("\n%d/%d", &day, &month) != 2);
            }
            else if (searchChoice == 2)
            {
                do
                {
                    printf("Enter Month of Birthday (MM) (e.g. 04 for April): ");
                } while (scanf("\n%d", &month) != 1);
            }
            else
            {
                printf("Enter the name of the person you wish to search for: ");
                do
                {
                    gets(nameToFind);
                } while (strlen(nameToFind) < 3);
            }
            int iResultCount = 0;

            struct birthday **results = find(day, month, nameToFind, searchChoice, &iResultCount);
            if (iResultCount == 1)
            {
                birthday2 = results[0];
                printf("Birthday    Name\n");
                printf("%d/%d           %s\n\n", birthday2->day, birthday2->month, birthday2->name);

                if (ch == 4)
                {
                    printf("Enter New Birthday Details\n\n");
                    getBirthdayDetails(birthday2);
                    popItemFromLinkedList(birthday2);
                    pushItemToLinkedList(birthday2);
                    printf("Birthday modified successfully !");
                }
                else
                {
                    char answer;
                    printf("Do you wish to delete the Birthday (Y/n):");
                    cin >> answer;
                    if (answer == 'y' || answer == 'Y')
                    {
                        popItemFromLinkedList(birthday2);
                        free(birthday2);
                    }
                }
            }
            else
            {
                printf("One Birthday Is Not Found !");
            }
            break;
        case 5:
            SaveFile();
            free(list);
            return;
            break;
        }
        getch();
    } while (1);
}
