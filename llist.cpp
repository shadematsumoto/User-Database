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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This program is the database handling the records and files
//    with specialized methods to do so.
//
****************************************************************/

#include "llist.h"

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION: Linked list constructor
//
//  Parameters: N/A
//
//  Return values: N/A
//
****************************************************************/

llist::llist()
{
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: llist\n";
        cout << " called successfully.\n";
    #endif
    start = NULL;
    strcpy(filename, "records.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION: Linked list constructor with specified filename
//
//  Parameters: file (char []) : Name of file
//
//  Return values: N/A
//
****************************************************************/

llist::llist(char file[])
{
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: llist(char [])\n";
        cout << " file = " << file << '\n';
    #endif
    start = NULL;
    strncpy(filename, file, sizeof(filename) - 1);
    filename[sizeof(filename) - 1] = '\0';
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION: Linked list destructor
//
//  Parameters: N/A
//
//  Return values: N/A
//
****************************************************************/

llist::~llist()
{
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: ~llist\n";
        cout << " called successfully.\n";
    #endif
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION: Linked list copy constructor
//
//  Parameters: source (const llist &) : Reference to source llist
//
//  Return values: N/A
//
****************************************************************/

llist::llist(const llist &source)
{
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: llist(const llist &)\n";
        cout << " called successfully.\n";
    #endif
    start = NULL;
    strncpy(filename, source.filename, sizeof(filename));
    filename[sizeof(filename) - 1] = '\0';

    record *current = source.start;
    record *prev = NULL;

    while (current)
    {
        record *newRecord = new record;
        newRecord->accountno = current->accountno;
        strncpy(newRecord->name, current->name, sizeof(newRecord->name));
        strncpy(newRecord->address, current->address, sizeof(newRecord->address));
        newRecord->next = NULL;

        if (!prev)
        {
            start = newRecord;
        }
        else
        {
            prev->next = newRecord;
        }
        prev = newRecord;
        current = current->next;
    }
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record including its account number,
//                  name, and address sorted in ascending order
//                  based on its account number.
//
//  Parameters: start   uaccountno (int) : Account number to add
//                       uname (char []) : Account name to add
//                    uaddress (char []) : Address string to add
//
//  Return values:  0 : Record successfully added
//                 -1 : Account number already in records
//                       (or not enough memory in heap)
//
****************************************************************/

int llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    int result = 0;
    record *current = start;
    record *prev = NULL;

    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: addRecord\n";
        cout << " uaccountno = " << uaccountno << '\n';
        cout << " uname = " << uname << '\n';
        cout << " uaddress:\n" << uaddress << '\n';
    #endif

    while (current && current->accountno < uaccountno)
    {
       prev = current;
       current = current->next;
    }

    if (current && current->accountno == uaccountno)
    {
        result = -1;
        #ifdef DEBUGMODE
            cout << " uaccountno already in records.\n\n";
        #endif
    }
    else
    {
        record *newrecord = new record;

        if (!newrecord)
        {
            result = -1;
            #ifdef DEBUGMODE
                cout << " Memory not allocated.\n\n";
            #endif
        }
        else
        {
            newrecord->accountno = uaccountno;
            strcpy(newrecord->name, uname);
            strcpy(newrecord->address, uaddress);
            newrecord->next = current;

            if (!prev)
            {
                start = newrecord;
            }
            else
            {
                prev->next = newrecord;
            }
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all the records
//
//  Parameters: N/A
//
//  Return values: N/A
//
****************************************************************/

void llist::printAllRecords()
{
    if (!start)
    {
        cout << "\nThere are no records.\n";
    }
    else
    {
        record *current = start;
        while (current)
        {
            cout << "\nAccount number: " << current->accountno << '\n';
            cout << "Name: " << current->name << '\n';
            cout << "Address:\n" << current->address << '\n';
            current = current->next;
        }
    }
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: printAllRecords\n";
        cout << " called successfully.\n";
    #endif
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Prints a record given an account number
//
//  Parameters: uaccountno (int) : Account number to be
//                                  searched
//
//  Return values:  0 : Record found
//                 -1 : Record not found
//
****************************************************************/

int llist::findRecord(int uaccountno)
{
    record *current = start;
    int result = -1;

    while (current)
    {
        if (current->accountno == uaccountno)
        {
            result = 0;
            cout << "\nAccount number: " << current->accountno << '\n';
            cout << "Name: " << current->name << '\n';
            cout << "Address:\n" << current->address << '\n';
            current = NULL;
        }
        else
        {
            current = current->next;
        }
    }


    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: findRecord\n";
        cout << " uaccountno = " << uaccountno << '\n';
    #endif

    return result;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes a record with an account number
//
//  Parameters: uaccountno (int) : Account number to delete
//
//  Return values:  0 : Record successfully deleted
//                 -1 : Record not found
//
****************************************************************/

int llist::deleteRecord(int uaccountno)
{
    int result = -1;
    record *current = start;
    record *prev = NULL;

    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: deleteRecord\n";
        cout << " uaccountno = " << uaccountno << '\n';
    #endif

    while (current)
    {
        if (uaccountno == current->accountno)
        {
            result = 0;
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                start = current->next;
            }

            delete current;
            current = NULL;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Writes the records on a file
//
//  Parameters: N/A
//
//  Return values:  0 : File successfully written
//                 -1 : File could not be opened
//
****************************************************************/

int llist::writefile()
{
    int result = -1;

    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: writefile\n";
        cout << " called successfully.\n";
    #endif

    ofstream ofs (filename, ofstream::out);
    if (ofs)
    {
        result = 0;
        record *current = start;
        while (current)
        {
            ofs << current->accountno << '\n';
            ofs << current->name << '\n';
            ofs << current->address << "\n\n";
            current = current->next;
        }
        ofs.close();
    }

    return result;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the records from a file
//
//  Parameters: N/A
//
//  Return values:  0 : File successfully read
//                 -1 : File could not be opened
//
****************************************************************/

int llist::readfile()
{
    int result = -1;

    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: readfile\n";
        cout << " called successfully.\n";
    #endif

    ifstream ifs (filename, ifstream::in);
    if (ifs)
    {
        result = 0;
        int accountno;

        while (ifs >> accountno)
        {
            char name[25] = "";
            char address[45] = "";
            char tempstring[45] = "";

            ifs.ignore();
            ifs.getline(name, 25);
            ifs.getline(tempstring, 45);
            while (tempstring[0] != '\0')
            {
                if (address[0] != '\0')
                {
                    strcat(address, "\n");
                }

                strcat(address, tempstring);

                ifs.getline(tempstring, 45);
            }

            addRecord(accountno, name, address);
        }
        ifs.close();
    }

    return result;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Release allocated heap memory
//                  and assign NULL to start
//
//  Parameters: N/A
//
//  Return values: N/A
//
****************************************************************/

void llist::cleanup()
{
    record *current = start;

    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: cleanup\n";
        cout << " called successfully.\n";
    #endif

    while (current)
    {
        record *temp = current;
        current = current->next;
        delete temp;
    }
    start = NULL;
}

/*****************************************************************
//
//  Function name: operator<<
//
//  DESCRIPTION:   Overloads the << operator
//
//  Parameters: os (ostream &) : Stream to output to
//              list (const llist &) : Linked list to reference
//
//  Return values:  ostream & : Return input
//
****************************************************************/

ostream & operator<<(ostream &os, const llist &list)
{
    if (!list.start)
    {
        cout << "\nThere are no records.\n";
    }
    else
    {
        record *current = list.start;
        while (current)
        {
            os << "\nAccount number: " << current->accountno << '\n';
            os << "Name: " << current->name << '\n';
            os << "Address:\n" << current->address << '\n';
            current = current->next;
        }
    }
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: operator<<\n";
        cout << " called successfully.\n";
    #endif
    return os;
}

/*****************************************************************
//
//  Function name: operator=
//
//  DESCRIPTION:   Overloads the = operator
//
//  Parameters: source (const llist &) : Linked list to reference
//
//  Return values: llist & : Return input
//
****************************************************************/

llist & llist::operator=(const llist &source)
{
    #ifdef DEBUGMODE
        cout << "\nDEBUG INFO: operator=\n";
        cout << " called successfully.\n";
    #endif
    if (this != &source)
    {
        cleanup();

        strncpy(filename, source.filename, sizeof(filename));
        filename[sizeof(filename) - 1] = '\0';

        record *current = source.start;
        record *prev = NULL;

        while (current)
        {
            record *newRecord = new record;
            newRecord->accountno = current->accountno;
            strncpy(newRecord->name, current->name, sizeof(newRecord->name));
            strncpy(newRecord->address, current->address, sizeof(newRecord->address));
            newRecord->next = NULL;

            if (!prev)
            {
                start = newRecord;
            }
            else
            {
                prev->next = newRecord;
            }
            prev = newRecord;
            current = current->next;
        }
    }
    return *this;
}
