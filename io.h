/*
 * File: relation.h
 * Creator: Adam Kaplan
 * Time-stamp: November 27, 2016
 * Project 4
 */

#ifndef IO
#define IO

#include "relation.h"

void saveToFile(hashtable_t *table, char *filename);
hashtable_t* getFromFile(char *filename);

#endif
