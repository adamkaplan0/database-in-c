/*
 * File: relation.h
 * Creator: Adam Kaplan
 * Time-stamp: November 27, 2016
 * Project 4
 */

#ifndef RELATION
#define RELATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int BOOL;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef enum {SNAP, CSG, CDH, CP, CR, OTHER} type_t;
typedef enum {INTEGER, STRING} rawtype_t;

typedef struct ATTRIBUTE {
  rawtype_t rawtypeID; //for generic usage
  BOOL isKey; //to keep track of which attributes are keys
  char *name; //name of the attribute
  void *data; //the type of data stored in the attribute
  struct ATTRIBUTE *next;
} attribute_t;

typedef struct ATTRIBUTELIST {
  int length;
  int key; //key for all of the attributes combined
  attribute_t *first;
} attributelist_t;

typedef struct TUPLE {
  type_t typeID;
  int key; //key of tuple
  attributelist_t *attributes; //the attributes of the tuple
  struct TUPLE *next;
} tuple_t;

typedef struct TUPLELIST {
  type_t typeID;
  int key;
  int length;
  tuple_t *first;
} tuplelist_t;

typedef struct HASHTABLE {
  type_t typeID;
  int size;
  tuplelist_t **array;
} hashtable_t;

//Miscellaneous functions
int stringToInt(char *input);

//Attribute functions
attribute_t* ATTRIBUTE_new(rawtype_t rawtypeID, BOOL isKey, char *name, void *data);
BOOL ATTRIBUTE_equal(attribute_t *a1, attribute_t *a2);
BOOL ATTRIBUTE_attributeEqual(attribute_t *a1, attribute_t *a2);
void ATTRIBUTE_print(attribute_t *attr);

//Attribute list functions
attributelist_t* ATTRIBUTELIST_new();
void ATTRIBUTELIST_add(attributelist_t *list, attribute_t *attr);
BOOL ATTRIBUTELIST_attributesCompare(attribute_t *attr, attributelist_t *list);
void ATTRIBUTELIST_attributeDelete(attributelist_t *list, attribute_t *attr);
void ATTRIBUTELIST_attributesDeleteExcept(attributelist_t *l1, attributelist_t *l2);
BOOL ATTRIBUTELIST_equal(attributelist_t *l1, attributelist_t *l2);
BOOL ATTRIBUTELIST_attributesEqual(attributelist_t *l1, attributelist_t *l2);
BOOL ATTRIBUTELIST_contains(attributelist_t *list, attribute_t *attr);
void ATTRIBUTELIST_merge(attributelist_t *l1, attributelist_t *l2);
void ATTRIBUTELIST_print(attributelist_t *list);

//Tuple functions
tuple_t* TUPLE_new(type_t typeID, attributelist_t *list);
tuple_t* TUPLE_newSNAP(int StudentId, char *Name, char *Address, char *Phone);
tuple_t* TUPLE_newCSG(char *Course, int StudentId, char *Grade);
tuple_t* TUPLE_newCDH(char *Course, char *Day, char *Hour);
tuple_t* TUPLE_newCP(char *Course, char* Prerequisite);
tuple_t* TUPLE_newCR(char *Course, char* Room);
BOOL TUPLE_equal(tuple_t *t1, tuple_t *t2);
void TUPLE_print(tuple_t *tuple);

//Tuple list functions
tuplelist_t* TUPLELIST_new(type_t typeID);
BOOL TUPLELIST_contains(tuplelist_t *list, tuple_t* tuple);
void TUPLELIST_add(tuplelist_t *list, tuple_t* tuple);
tuple_t* TUPLELIST_lookup(tuplelist_t *list, tuple_t* tuple);
void TUPLELIST_delete(tuplelist_t *list, tuple_t *tuple);
void TUPLELIST_print(tuplelist_t *list);

//Hashtable functions
hashtable_t* HASHTABLE_new(type_t typeID, int size);
int hash(hashtable_t *table, int key);
void HASHTABLE_add(hashtable_t *table, tuple_t *tuple);
tuple_t* HASHTABLE_lookup(hashtable_t *table, tuple_t *tuple);
void HASHTABLE_delete(hashtable_t *table, tuple_t *tuple);
void HASHTABLE_deleteGeneral(hashtable_t *table, attributelist_t *attributes);
BOOL HASHTABLE_contains(hashtable_t *table, tuple_t *tuple);
BOOL HASHTABLE_equalAttributes(hashtable_t *table1, hashtable_t *table2);
hashtable_t* HASHTABLE_copy(hashtable_t *source);
hashtable_t* HASHTABLE_selection(hashtable_t *table, attributelist_t *attributes);
hashtable_t* HASHTABLE_projection(hashtable_t *table, attributelist_t *attributes);
hashtable_t* HASHTABLE_join(hashtable_t *table1, hashtable_t *table2, attribute_t *attr);
void HASHTABLE_print(hashtable_t *table);

//Set functions
hashtable_t* HASHTABLE_union(hashtable_t *table1, hashtable_t *table2);
hashtable_t* HASHTABLE_intersection(hashtable_t *table1, hashtable_t *table2);
hashtable_t* HASHTABLE_difference(hashtable_t *table1, hashtable_t *table2);

//Query functions
char* student_Grade(hashtable_t *snap, hashtable_t *csg, char *name, char *course);
char* student_Place(hashtable_t *snap, hashtable_t *csg, hashtable_t *cdh, hashtable_t *cr, char *name, char *hour, char *day);

#endif
