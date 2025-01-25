/*****************************************************************
//
//  NAME:        Shade Matsumoto
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 30, 2024
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This program is the user interface for the bank database,
//   able to call the corresponding database functions by
//   providing a readable and functional menu of options,
//   asking for relevant information.
//
****************************************************************/

#include "llist.h"
#include <iostream>
#include <cstring>

void getaddress(char [], int);
void getAccountNum(int &);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   This function acts as the user interface for
//                  managing bank record by displaying a menu,
//                  accepting user inputs, and then calls the
//                  corresponding database functions.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments
//                                   (used to activate debug mode)
//
//  Return values: 0 : Program ended
//
****************************************************************/

int main(int argc, char *argv[])
{
    int uaccountno;
    char uname[25];
    char uaddress[45];
    char user_input[10];
    int quit_program = 0;

    /* Program start */
    llist database;

    cout << "\n==================================\n";
    cout << "===Welcome to the Bank Database===\n";
    #ifdef DEBUGMODE
        cout << "============DEBUG MODE============\n";
    #endif
    cout << "==================================\n\n";

    cout << "Menu:\n";
    cout << "add: Add a new record\n";
    cout << "printall: Print all records\n";
    cout << "find: Find a record by account number\n";
    cout << "delete: Delete a record by account number\n";
    cout << "quit: Quit the program\n";

    /* Main loop */
    while (quit_program == 0)
    {
        cout << "\nEnter a command: ";

        cin.getline(user_input, 10);

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n'); /* Clear buffer */
        }

        /* Menu options comparing string up to '\n' from user_input */
        if (user_input[0] == '\0') /* User only pressed ENTER */
        {
            cout << "\nPlease enter a command.\n";
        }
        else if (strncmp(user_input, "add", strcspn(user_input, "\0")) == 0)
        {
            getAccountNum(uaccountno);
            cout << "\nEnter name: ";
            do
            {
                cin.getline(uname, 25);
            }
            while (uname[0] == '\0');

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n'); /* Clear buffer */
            }

            getaddress(uaddress, 45);

            if (database.addRecord(uaccountno, uname, uaddress) == -1)
            {
                cout << "Record could not be added.\n";
            }
            else
            {
                cout << "Record was successfully added.\n";
            }
        }
        else if (strncmp(user_input, "printall", strcspn(user_input, "\0")) == 0)
        {
            cout << database;
        }
        else if (strncmp(user_input, "find", strcspn(user_input, "\0")) == 0)
        {
            getAccountNum(uaccountno);

            if (database.findRecord(uaccountno) == -1)
            {
                cout << "\nRecord could not be found.\n";
            }
        }
        else if (strncmp(user_input, "delete", strcspn(user_input, "\0")) == 0)
        {
            getAccountNum(uaccountno);

            if (database.deleteRecord(uaccountno) == -1)
            {
                cout << "\nRecord could not be found.\n";
            }
        }
        else if (strncmp(user_input, "quit", strcspn(user_input, "\0")) == 0)
        {
            quit_program = 1;
        }
        else
        {
            cout << "\nCommand not found.\n"; /* No commands matched */
        }
    }

    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   This function accepts user input to obtain the
//                  address including newline characters.
//
//  Parameters:    uaddress (char []) : array to input address
//                 size (int) : size of array
//
//  Return values: N/A
//
****************************************************************/

void getaddress(char uaddress[], int size) {
    char buffer[45];
    int done = 0;

    uaddress[0] = '\0'; /* Initialize uaddress */

    cout << "\nEnter address (press ENTER twice to finish):\n";

    while (done == 0)
    {
        cin.getline(buffer, 45);
        if (buffer[0] == '\0' && uaddress[0] != '\0') /* Newline in new line (ENTER twice) */
        {
            done = 1;
        }
        else if ((int)strcspn(uaddress, "\0") < size - 1)
        {
            if (uaddress[0] != '\0') /* If uaddress is not empty */
            {
                strcat(uaddress, "\n"); /* Appends '\n' */
            }

            strncat(uaddress, buffer, size - strlen(uaddress) - 1); /* Appends buffer to available memory in uaddress */
        }

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n'); /* Clear buffer */
        }
    }
}

/*****************************************************************
//
//  Function name: getAccountNum
//
//  DESCRIPTION:   This function accepts user input to obtain the
//                  account number, reprompting if not valid
//
//  Parameters:    uaccountno (int &) : reference to uaccountno
//
//  Return values: N/A
//
****************************************************************/

void getAccountNum(int &uaccountno)
{
    cout << "\nEnter account number: ";

    cin >> uaccountno;
    while (cin.fail() || uaccountno <= 0)
    {
        cin.clear();
        cin.ignore(10000, '\n'); /* Clear buffer */
        cout << "Invalid input. Please enter a positive integer: ";
        cin >> uaccountno;
    }
    cin.ignore(10000, '\n'); /* Clear buffer */
}
