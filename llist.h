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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This header file contains the llist class definition.
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H

#include "record.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class llist
{
    private:
        record *    start;
        char        filename[20];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char[], char[]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);

        friend ostream& operator<<(ostream&, const llist&);
        llist(const llist&);
        llist& operator=(const llist&);
};

#endif
