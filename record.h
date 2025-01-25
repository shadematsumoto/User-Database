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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This header contains the record struct definition.
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                 accountno;
    char                name[25];
    char                address[45];
    struct record *     next;
};

#endif
