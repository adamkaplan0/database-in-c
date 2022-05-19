/*
 * File: relation.c
 * Creator: Adam Kaplan
 * Time-stamp: November 27, 2016
 * Project 4
 */

#include "relation.h"

int stringToInt(char *input) {
  int res = 0;
  while(input[0] != '\0') {
    res += input[0];
    input++;
  }

  return res;
}

attribute_t* ATTRIBUTE_new(rawtype_t rawtypeID, BOOL isKey, char *name, void *data) {
  attribute_t *attr = (attribute_t*)malloc(sizeof(attribute_t));
  attr->rawtypeID = rawtypeID;
  attr->name = (char*)malloc(sizeof(char)*strlen(name));
  memcpy(attr->name, name, sizeof(char)*strlen(name) + 1);
  //attr->name = name;
  attr->isKey = isKey;

  if(rawtypeID == INTEGER) {
    attr->data = malloc(sizeof(int));
    memcpy(attr->data, data, sizeof(int));
  }
  else if(rawtypeID == STRING){
    attr->data = malloc(sizeof(char)*strlen(data) + 1);
    memcpy(attr->data, data, sizeof(char)*strlen(data) + 1);
  }

  attr->next = NULL;

  return attr;
}

BOOL ATTRIBUTE_equal(attribute_t *a1, attribute_t *a2) {
  if(a1->rawtypeID == a2->rawtypeID && strcmp(a1->name, a2->name) == 0) {
    //printf("equal got here\n");
    if(a1->rawtypeID == INTEGER) {
      if(*((int*)a1->data) == *((int*)a2->data))
        return TRUE;
    }
    else if(a1->rawtypeID == STRING){
      //printf("COURSE got here %s %s %d\n", a1->data, a2->data, strcmp(a1->data, a2->data));
      if(strcmp(a1->data, a2->data) == 0)
        return TRUE;
    }
  }
  return FALSE;
}

BOOL ATTRIBUTE_attributeEqual(attribute_t *a1, attribute_t *a2) {
  return (a1->rawtypeID == a2->rawtypeID && strcmp(a1->name, a2->name) == 0);
}

void ATTRIBUTE_print(attribute_t *attr) {
  if(attr != NULL) {
    printf("%s = ", attr->name);
    if(attr->rawtypeID == INTEGER)
      printf("%d\n", *((int*)attr->data));
    else if(attr->rawtypeID == STRING)
      printf("%s\n", attr->data);
  }
}

attributelist_t* ATTRIBUTELIST_new() {
  attributelist_t *list = (attributelist_t*)malloc(sizeof(attributelist_t));
  list->key = 0;
  list->length = 0;
  list->first = NULL;

  return list;
}

void ATTRIBUTELIST_add(attributelist_t *list, attribute_t *attr) {
  if(list != NULL) {
    if(list->first == NULL) {
      list->first = attr;
      list->length += 1;
    }
    else {
      attribute_t *current = list->first;

      while(current->next != NULL)
        current = current->next;
      current->next = attr;
      list->length += 1;
    }
    if(attr->isKey) {
      if(attr->rawtypeID == STRING)
        list->key += stringToInt(attr->data);
      else if(attr->rawtypeID == INTEGER)
        list->key += *((int*)attr->data);
    }
  }
}

void ATTRIBUTELIST_attributeDelete(attributelist_t *list, attribute_t *attr) {
  if(list != NULL) {
    if(list->first != NULL) {
      attribute_t *current = list->first;
      BOOL deleted = FALSE;

      if(ATTRIBUTE_attributeEqual(list->first, attr)) {
        list->first = list->first->next;
        deleted = TRUE;
      }
      else {
        while(current->next != NULL) {
          if(ATTRIBUTE_attributeEqual(current->next, attr)) {
            current->next = current->next->next;
            deleted = TRUE;
            break;
          }
          current = current->next;
        }
      }

      if(deleted) {
        list->length -= 1;

        if(attr->isKey) {
          if(attr->rawtypeID == STRING)
            list->key -= stringToInt(attr->data);
          else if(attr->rawtypeID == INTEGER)
            list->key -= *((int*)attr->data);
        }
      }
    }
  }
}

BOOL ATTRIBUTELIST_attributesCompare(attribute_t *attr, attributelist_t *list) {
  attribute_t *current = list->first;

  while(current != NULL) {
    if(ATTRIBUTE_attributeEqual(attr, current))
      return FALSE;
    current = current->next;
  }
  return TRUE;
}

void ATTRIBUTELIST_attributesDeleteExcept(attributelist_t *l1, attributelist_t *l2) {
  attribute_t *currl1 = l1->first;
  while(currl1 != NULL) {
    if(ATTRIBUTELIST_attributesCompare(currl1, l2))
      ATTRIBUTELIST_attributeDelete(l1, currl1);

    currl1 = currl1->next;
  }
}

BOOL ATTRIBUTELIST_equal(attributelist_t *l1, attributelist_t *l2) {
  if(l1->length == l2->length) {
    attribute_t *curr1 = l1->first;
    attribute_t *curr2 = l2->first;

    while(curr1 != NULL) {
      if(!ATTRIBUTE_equal(curr1, curr2))
        return FALSE;
      curr1 = curr1->next;
      curr2 = curr2->next;
    }
    return TRUE;
  }
  return FALSE;
}

BOOL ATTRIBUTELIST_attributesEqual(attributelist_t *l1, attributelist_t *l2) {
  if(l1->length == l2->length) {
    attribute_t *curr1 = l1->first;
    attribute_t *curr2 = l2->first;

    while(curr1 != NULL) {
      if(!ATTRIBUTE_attributeEqual(curr1, curr2))
        return FALSE;
      curr1 = curr1->next;
      curr2 = curr2->next;
    }
    return TRUE;
  }
  return FALSE;
}

BOOL ATTRIBUTELIST_contain(attributelist_t *l1, attributelist_t *l2) {
  if(l2->length > l1->length)
    return FALSE;

  attribute_t *currl2 = l2->first;

  while(currl2 != NULL) {
    attribute_t *currl1 = l1->first;
    BOOL found = FALSE;
    while(currl1 != NULL) {
      //printf("Attributes: %s %s\n", currl1->name, currl2->name);
      //printf("Are the attributes equal: %d\n", ATTRIBUTE_equal(currl1, currl2));
      if(ATTRIBUTE_equal(currl1, currl2))
        found = TRUE;
      currl1 = currl1->next;
    }
    if(!found)
      return FALSE;
    currl2 = currl2->next;
  }
  return TRUE;
}

BOOL ATTRIBUTELIST_contains(attributelist_t *list, attribute_t *attr) {
  attribute_t *current = list->first;

  while(current != NULL) {
    if(ATTRIBUTE_attributeEqual(current, attr))
      return TRUE;

    current = current->next;
  }
  return FALSE;
}

void ATTRIBUTELIST_merge(attributelist_t *l1, attributelist_t *l2) {
  attribute_t *curr2 = l2->first;

  while(curr2 != NULL) {
    if(!ATTRIBUTELIST_contains(l1, curr2)) {
      attribute_t *temp = ATTRIBUTE_new(curr2->rawtypeID, curr2->isKey, curr2->name, curr2->data);
      ATTRIBUTELIST_add(l1, temp);
    }

    curr2 = curr2->next;
  }
}

void ATTRIBUTELIST_print(attributelist_t *list) {
  if(list != NULL) {
    attribute_t *current = list->first;
    while(current != NULL) {
      ATTRIBUTE_print(current);
      current = current->next;
    }
    printf("\n\n");
  }
}

tuple_t* TUPLE_new(type_t typeID, attributelist_t *list) {
  tuple_t *tuple = (tuple_t*)malloc(sizeof(tuple_t));

  tuple->typeID = typeID;
  tuple->key = list->key;
  tuple->attributes = list;
  tuple->next = NULL;

  return tuple;
}

tuple_t* TUPLE_newSNAP(int StudentId, char *Name, char *Address, char *Phone) {
  tuple_t *tuple = (tuple_t*)malloc(sizeof(tuple_t));
  attribute_t *sid = ATTRIBUTE_new(INTEGER, TRUE, "StudentId", &StudentId);
  attribute_t *name = ATTRIBUTE_new(STRING, FALSE, "Name", Name);
  attribute_t *address = ATTRIBUTE_new(STRING, FALSE, "Address", Address);
  attribute_t *phone = ATTRIBUTE_new(STRING, FALSE, "Phone", Phone);
  attributelist_t *list = ATTRIBUTELIST_new();

  ATTRIBUTELIST_add(list, sid);
  ATTRIBUTELIST_add(list, name);
  ATTRIBUTELIST_add(list, address);
  ATTRIBUTELIST_add(list, phone);

  tuple->typeID = SNAP;
  tuple->key = list->key;
  tuple->attributes = list;
  tuple->next = NULL;

  return tuple;
}

tuple_t* TUPLE_newCSG(char *Course, int StudentId, char *Grade) {
  tuple_t *tuple = (tuple_t*)malloc(sizeof(tuple_t));
  attribute_t *sid = ATTRIBUTE_new(INTEGER, TRUE, "StudentId", &StudentId);
  attribute_t *course = ATTRIBUTE_new(STRING, FALSE, "Course", Course);
  attribute_t *grade = ATTRIBUTE_new(STRING, FALSE, "Grade", Grade);
  attributelist_t *list = ATTRIBUTELIST_new();


  ATTRIBUTELIST_add(list, course);
  ATTRIBUTELIST_add(list, sid);
  ATTRIBUTELIST_add(list, grade);

  tuple->typeID = CSG;
  tuple->key = list->key;
  tuple->attributes = list;
  tuple->next = NULL;

  return tuple;
}

tuple_t* TUPLE_newCDH(char *Course, char *Day, char *Hour) {
  tuple_t *tuple = (tuple_t*)malloc(sizeof(tuple_t));
  attribute_t *course = ATTRIBUTE_new(STRING, FALSE, "Course", Course);
  attribute_t *day = ATTRIBUTE_new(STRING, FALSE, "Day", Day);
  attribute_t *hour = ATTRIBUTE_new(STRING, FALSE, "Hour", Hour);
  attributelist_t *list = ATTRIBUTELIST_new();


  ATTRIBUTELIST_add(list, course);
  ATTRIBUTELIST_add(list, day);
  ATTRIBUTELIST_add(list, hour);

  tuple->typeID = CDH;
  tuple->key = list->key;
  tuple->attributes = list;
  tuple->next = NULL;

  return tuple;
}

tuple_t* TUPLE_newCP(char *Course, char* Prerequisite) {
  tuple_t *tuple = (tuple_t*)malloc(sizeof(tuple_t));
  attribute_t *course = ATTRIBUTE_new(STRING, FALSE, "Course", Course);
  attribute_t *prereq = ATTRIBUTE_new(STRING, FALSE, "Prerequisite", Prerequisite);
  attributelist_t *list = ATTRIBUTELIST_new();


  ATTRIBUTELIST_add(list, course);
  ATTRIBUTELIST_add(list, prereq);

  tuple->typeID = CP;
  tuple->key = list->key;
  tuple->attributes = list;
  tuple->next = NULL;

  return tuple;
}

tuple_t* TUPLE_newCR(char *Course, char* Room) {
  tuple_t *tuple = (tuple_t*)malloc(sizeof(tuple_t));
  attribute_t *course = ATTRIBUTE_new(STRING, FALSE, "Course", Course);
  attribute_t *room = ATTRIBUTE_new(STRING, FALSE, "Room", Room);
  attributelist_t *list = ATTRIBUTELIST_new();


  ATTRIBUTELIST_add(list, course);
  ATTRIBUTELIST_add(list, room);

  tuple->typeID = CR;
  tuple->key = list->key;
  tuple->attributes = list;
  tuple->next = NULL;

  return tuple;
}

tuple_t* TUPLE_copy(tuple_t *tuple) {
  tuple_t *result = TUPLE_new(tuple->typeID, tuple->attributes);
  result->next = tuple->next;

  return result;
}

tuple_t* TUPLE_merge(tuple_t *t1, tuple_t *t2) {
  tuple_t *result = TUPLE_copy(t1);
  result->next = NULL;
  ATTRIBUTELIST_merge(result->attributes, t2->attributes);

  return result;
}

BOOL TUPLE_equal(tuple_t *t1, tuple_t *t2) {
  if(t1 != NULL && t2 != NULL) {
    if(t1->typeID == t2->typeID)
      return ATTRIBUTELIST_equal(t1->attributes, t2->attributes);
  }
  return FALSE;
}

void TUPLE_print(tuple_t *tuple) {
  if(tuple != NULL) {
      ATTRIBUTELIST_print(tuple->attributes);
  }
}

tuplelist_t* TUPLELIST_new(type_t typeID) {
  tuplelist_t *list = (tuplelist_t*)malloc(sizeof(tuplelist_t));

  list->typeID = typeID;
  list->length = 0;
  list->first = NULL;

  return list;
}

BOOL TUPLELIST_contains(tuplelist_t *list, tuple_t* tuple) {
  if(list != NULL) {
    if(list->typeID == tuple->typeID) {
      if(list->first == NULL)
        return FALSE;
      else {
        tuple_t *current = list->first;

        while(current != NULL) {
          if(TUPLE_equal(current, tuple))
            return TRUE;
          current = current->next;
        }
        return FALSE;
      }
    }
  }
  return FALSE;
}

void TUPLELIST_add(tuplelist_t *list, tuple_t* tuple) {
  if(list != NULL && tuple != NULL) {
      if(list->first == NULL) {
        list->key = tuple->key;
        list->first = tuple;
        list->length += 1;
      }
      else {
        if(!TUPLELIST_contains(list, tuple)) {
          tuple_t *current = list->first;
          if(list->length == 1) {
            list->first->next = tuple;
            list->length += 1;
          }
          else {/*
            printf("more than second insert %d\n", list->length);
            for(int i = 0; i < list->length - 2; i++) {
              current = current->next;
            }*/
            while(current->next != NULL) {
              current = current->next;
            }
            current->next = tuple;
            list->length += 1;
          }

        }
    }
  }
}

tuple_t* TUPLELIST_lookup(tuplelist_t *list, tuple_t* tuple) {
  if(list != NULL) {
      if(list->first == NULL)
        return NULL;
      else {
        tuple_t *current = list->first;

        while(current != NULL) {
          if(TUPLE_equal(current, tuple))
            return current;
        }
      }
  }
  return NULL;
}

void TUPLELIST_delete(tuplelist_t *list, tuple_t *tuple) {
  if(list != NULL) {
      if(list->first != NULL) {
        tuple_t *current = list->first;

        if(TUPLE_equal(current, tuple)) {
          list->first = list->first->next;
        }



        while(current->next != NULL) {
          if(TUPLE_equal(current->next, tuple)) {
            current->next = current->next->next;
          }
          current = current->next;
        }
      }
  }
}

void TUPLELIST_print(tuplelist_t *list) {
  if(list != NULL) {
    tuple_t *current = list->first;
    while(current != NULL) {
      TUPLE_print(current);
      current = current->next;
    }
  }
}

hashtable_t* HASHTABLE_new(type_t typeID, int size) {
  hashtable_t *table = (hashtable_t*)malloc(sizeof(hashtable_t));
  table->typeID = typeID;
  table->size = size;
  table->array = (tuplelist_t**)malloc(sizeof(tuplelist_t)*size);

  for(int i = 0; i < size; i++) {
    table->array[i] = TUPLELIST_new(typeID);
  }

  return table;
}

int hash(hashtable_t *table, int key) {
  return key % table->size;
}

void HASHTABLE_add(hashtable_t *table, tuple_t *tuple) {
  if(table != NULL) {
    if(table->typeID == tuple->typeID || table->typeID == OTHER) {
      int index = hash(table, tuple->key);
      tuplelist_t *list = (table->array[index]);
      TUPLELIST_add(list, tuple);
    }
  }
}

tuple_t* HASHTABLE_lookup(hashtable_t *table, tuple_t *tuple) {
  if(table != NULL) {
    if(table->typeID == tuple->typeID) {
      int index = hash(table, tuple->key);
      return TUPLELIST_lookup((table->array[index]), tuple);
    }
  }
  return NULL;
}

//Implement delete function (general)
void HASHTABLE_deleteGeneral(hashtable_t *table, attributelist_t *attributes) {
  //If there is only 1 attributes && we have index on A
  if(attributes->length == 1 && attributes->key != 0) {

    int index = hash(table, attributes->key);
    tuplelist_t *tuplelist = (table->array[index]);

    if(tuplelist->first != NULL) {
      tuple_t *current = tuplelist->first;

      while(current != NULL) {
        HASHTABLE_delete(table, current);
        current = current->next;
      }
    }
  }
  else if(attributes->length > 1 && attributes->key != 0) {
    int index = hash(table, attributes->key);
    tuplelist_t *tuplelist = (table->array[index]);

    if(tuplelist->first != NULL) {
      tuple_t *current = tuplelist->first;

      while(current != NULL) {
        if(ATTRIBUTELIST_contain(current->attributes, attributes))
          HASHTABLE_delete(table, current);
        current = current->next;
      }
    }
  }
  else {
    for(int i = 0; i < table->size; i++) {
      tuplelist_t *tuplelist = (table->array[i]);
      if(tuplelist->first != NULL) {
        tuple_t *current = tuplelist->first;

        while(current != NULL) {
          if(ATTRIBUTELIST_contain(current->attributes, attributes))
            HASHTABLE_delete(table, current);
          current = current->next;
        }
      }
    }
  }
}

void HASHTABLE_delete(hashtable_t *table, tuple_t *tuple) {
  if(table != NULL) {
    if(table->typeID == tuple->typeID) {
      int index = hash(table, tuple->key);
      TUPLELIST_delete((table->array[index]), tuple);
    }
  }
}

BOOL HASHTABLE_contains(hashtable_t *table, tuple_t *tuple) {
  return (HASHTABLE_lookup(table, tuple) != NULL);
}

BOOL HASHTABLE_equalAttributes(hashtable_t *table1, hashtable_t *table2) {
  if(table1 != NULL && table2 != NULL) {
    tuplelist_t *tlist1;
    tuplelist_t *tlist2;

    for(int i = 0; i < table1->size; i++) {
      tuplelist_t *tuplelist = (table1->array[i]);
      if(tuplelist->first != NULL)
        tlist1 = tuplelist;
    }

    for(int i = 0; i < table2->size; i++) {
      tuplelist_t *tuplelist = (table2->array[i]);
      if(tuplelist->first != NULL)
        tlist2 = tuplelist;
    }
    return ATTRIBUTELIST_attributesEqual(tlist1->first->attributes, tlist2->first->attributes);
  }

  return FALSE;
}

hashtable_t* HASHTABLE_copy(hashtable_t *source) {
  hashtable_t *copy = HASHTABLE_new(source->typeID, source->size);
  for(int i = 0; i < source->size; i++) {
    tuplelist_t *tuplelist = (source->array[i]);
    if(tuplelist->first != NULL) {
      tuple_t *current = tuplelist->first;
      while(current != NULL) {
        tuple_t *temp = TUPLE_copy(current);
        temp->next = NULL;
        HASHTABLE_add(copy, temp);
        current = current->next;
      }
    }
  }
  return copy;
}

void HASHTABLE_print(hashtable_t *table) {
  for(int i = 0; i < table->size; i++)
    TUPLELIST_print((table->array[i]));
}

hashtable_t* HASHTABLE_union(hashtable_t *table1, hashtable_t *table2) {
  if(table1 != NULL && table2 != NULL) {
    hashtable_t *copy = HASHTABLE_copy(table1);
    if(table1->typeID == table2->typeID && HASHTABLE_equalAttributes(table1, table2)) {

      for(int i = 0; i < table2->size; i++) {
        tuplelist_t *tuplelist = (table2->array[i]);
        if(tuplelist->first != NULL) {
          tuple_t *current = tuplelist->first;

          while(current != NULL) {
            HASHTABLE_add(copy, current);
            current = current->next;
          }
        }
      }
      return copy;
    }
  }
  return NULL;
}

hashtable_t* HASHTABLE_intersection(hashtable_t *table1, hashtable_t *table2) {
  if(table1 != NULL && table2 != NULL) {

    hashtable_t *result = HASHTABLE_new(table1->typeID, table1->size);

    if(table1->typeID == table2->typeID && HASHTABLE_equalAttributes(table1, table2)) {

      for(int i = 0; i < table1->size; i++) {

        tuplelist_t *tuplelist = (table1->array[i]);
        if(tuplelist->first != NULL) {
          tuple_t *current = tuplelist->first;

          while(current != NULL) {

            for(int j = 0; j < table2->size; j++) {
              tuplelist_t *tuplelist2 = (table2->array[j]);

              if(tuplelist2->first != NULL) {
                tuple_t *current2 = tuplelist2->first;

                while(current2 != NULL) {
                  if(TUPLE_equal(current, current2)) {
                    tuple_t *temp = TUPLE_copy(current);
                    temp->next = NULL;

                    HASHTABLE_add(result, temp);
                  }
                  current2 = current2->next;
                }
              }
            }

            current = current->next;

          }
        }
      }
      return result;
    }
  }
  return NULL;
}

hashtable_t* HASHTABLE_difference(hashtable_t *table1, hashtable_t *table2) {
  if(table1 != NULL && table2 != NULL) {
    hashtable_t *result = HASHTABLE_new(table1->typeID, table1->size);

    if(table1->typeID == table2->typeID && HASHTABLE_equalAttributes(table1, table2)) {
      for(int i = 0; i < table1->size; i++) {
        tuplelist_t *tuplelist = (table1->array[i]);
        if(tuplelist->first != NULL) {
          tuple_t *current1 = tuplelist->first;

          while(current1 != NULL) {
            BOOL found = FALSE;
            for(int j = 0; j < table2->size; j++) {
              tuplelist_t *tuplelist2 = (table2->array[j]);
              if(tuplelist2->first != NULL) {
                tuple_t *current2 = tuplelist2->first;

                while(current2 != NULL) {
                  if(TUPLE_equal(current1, current2))
                    found = TRUE;
                  current2 = current2->next;
                }
              }
            }
            if(!found) {
              tuple_t *temp = TUPLE_copy(current1);
              temp->next = NULL;

              HASHTABLE_add(result, temp);
            }
            current1 = current1->next;
          }
        }
      }
      return result;
    }
  }
  return NULL;
}

hashtable_t* HASHTABLE_selection(hashtable_t *table, attributelist_t *attributes) {
  hashtable_t *result = HASHTABLE_new(OTHER, table->size);
  //If there is only 1 attributes && we have index on A
  if(attributes->length == 1 && attributes->key != 0) {
    int index = hash(table, attributes->key);
    tuplelist_t *tuplelist = (table->array[index]);
    if(tuplelist->first != NULL) {
      tuple_t *current = tuplelist->first;

      while(current != NULL) {
        tuple_t *temp = TUPLE_copy(current);
        temp->next = NULL;
        HASHTABLE_add(result, temp);
        current = current->next;
      }
      return result;
    }
    return NULL;
  }
  else if(attributes->length > 1 && attributes->key != 0) {

    int index = hash(table, attributes->key);
    tuplelist_t *tuplelist = (table->array[index]);

    if(tuplelist->first != NULL) {
      tuple_t *current = tuplelist->first;

      while(current != NULL) {
        if(ATTRIBUTELIST_contain(current->attributes, attributes)) {

          tuple_t *temp = TUPLE_copy(current);
          temp->next = NULL;
          HASHTABLE_add(result, temp);
        }

        current = current->next;
      }

      return result;
    }
    return NULL;
  }
  else {
    for(int i = 0; i < table->size; i++) {
      tuplelist_t *tuplelist = (table->array[i]);
      if(tuplelist->first != NULL) {
        tuple_t *current = tuplelist->first;
        while(current != NULL) {
          if(ATTRIBUTELIST_contain(current->attributes, attributes)) {

            tuple_t *temp = TUPLE_copy(current);
            temp->next = NULL;
            HASHTABLE_add(result, temp);
          }

          current = current->next;
        }
      }
    }
    return result;
  }
}

hashtable_t* HASHTABLE_projection(hashtable_t *table, attributelist_t *attributes) {
  hashtable_t *result = HASHTABLE_copy(table);

  for(int i = 0; i < result->size; i++) {
    tuplelist_t *tuplelist = (result->array[i]);
    if(tuplelist->first != NULL) {
      tuple_t *current = tuplelist->first;

      while(current != NULL) {
        ATTRIBUTELIST_attributesDeleteExcept(current->attributes, attributes);
        current = current->next;
      }
    }
  }

  return result;
}

hashtable_t* HASHTABLE_join(hashtable_t *table1, hashtable_t *table2, attribute_t *attr) {
  hashtable_t *result = HASHTABLE_new(OTHER, table1->size);
  //If table1 and table2 agree on attr and attr is a key
  if(attr->isKey) {
    for(int i = 0; i < table1->size; i++) {
      tuplelist_t *tuplelist = (table1->array[i]);
      if(tuplelist->first != NULL) {
        tuple_t *current = tuplelist->first;

        while(current != NULL) {
          attribute_t *currattr = current->attributes->first;
          void *attrdata;
          int attrkey;
          while(currattr != NULL) {
            if(ATTRIBUTE_attributeEqual(currattr, attr)) {
              if(currattr->rawtypeID == INTEGER) {
                attrdata = malloc(sizeof(int));
                attrkey = *((int*)currattr->data);
                memcpy(attrdata, currattr->data, sizeof(int));
              }
              else {
                attrdata = malloc(sizeof(char)*strlen(currattr->data));
                attrkey = stringToInt(currattr->data);
                memcpy(attrdata, currattr->data, sizeof(char)*strlen(currattr->data));
              }
              break;
            }

            currattr = currattr->next;
          }
          //attr is the tuples only key
          if(current->key - attrkey == 0) {

            int index = hash(table2, attrkey);
            tuplelist_t *tuplelist2 = (table2->array[index]);

            if(tuplelist2->first != NULL) {
              tuple_t *curr2 = tuplelist2->first;
              while(curr2 != NULL) {
                //Create tuple from r & s
                tuple_t *merge = TUPLE_merge(current, curr2);
                HASHTABLE_add(result, merge);
                curr2 = curr2->next;
              }
            }
          }
          //Otherwise do the nested loop join
          else {
            for(int j = 0; j <table2->size; j++) {
              tuplelist_t *tuplelist2 = (table2->array[j]);
              if(tuplelist2->first != NULL) {
                tuple_t *curr2 = tuplelist2->first;

                while(curr2 != NULL) {
                  //get the attribute value of current and curr2 and compare them
                  attribute_t *currattr2 = curr2->attributes->first;

                  while(currattr2 != NULL) {
                    if(ATTRIBUTE_equal(currattr2, currattr)) {
                      tuple_t *merge = TUPLE_merge(current, curr2);
                      HASHTABLE_add(result, merge);
                      break;
                    }
                    currattr2 = currattr2->next;
                  }
                  curr2 = curr2->next;
                }
              }
            }
          }
          current = current->next;
        }
      }
    }
  }
  //The attribute is not a key
  else {
    for(int i = 0; i < table1->size; i++) {
      tuplelist_t *tuplelist1 = (table1->array[i]);
      if(tuplelist1->first != NULL) {
        tuple_t *curr1 = tuplelist1->first;

        while(curr1 != NULL) {

          attribute_t *currattr = curr1->attributes->first;
          while(currattr != NULL) {
            if(ATTRIBUTE_attributeEqual(currattr, attr))
              break;
            currattr = currattr->next;
          }
          if(currattr != NULL) {
            for(int j = 0; j <table2->size; j++) {
              tuplelist_t *tuplelist2 = (table2->array[j]);
              if(tuplelist2->first != NULL) {
                tuple_t *curr2 = tuplelist2->first;

                while(curr2 != NULL) {
                  //get the attribute value of current and curr2 and compare them
                  attribute_t *currattr2 = curr2->attributes->first;

                  while(currattr2 != NULL) {
                    if(ATTRIBUTE_equal(currattr2, currattr)) {
                      tuple_t *merge = TUPLE_merge(curr1, curr2);
                      HASHTABLE_add(result, merge);
                      break;
                    }
                    currattr2 = currattr2->next;
                  }
                  curr2 = curr2->next;
                }
              }
            }
          }
          curr1 = curr1->next;
        }
      }
    }
  }
return result;
}

//What grade did StudentName get in CourseName?
char* student_Grade(hashtable_t *snap, hashtable_t *csg, char *name, char *course) {
  for(int i = 0; i < snap->size; i++) {
    tuplelist_t *snap_list = (snap->array[i]);

    if(snap_list != NULL) {
      if(snap_list->first != NULL) {
        tuple_t *current_snap = snap_list->first;

        while(current_snap != NULL) {
          if(strcmp(current_snap->attributes->first->next->data, name) == 0) {
            int current_snap_sid = *((int*)current_snap->attributes->first->data);

            for(int j = 0; j < csg->size; j++) {
              tuplelist_t *csg_list = (csg->array[j]);

              if(csg_list != NULL) {
                if(csg_list->first != NULL) {
                  tuple_t *current_csg = csg_list->first;

                  while(current_csg != NULL) {
                    if(strcmp(current_csg->attributes->first->data, course) == 0 && *((int*)current_csg->attributes->first->next->data) == current_snap_sid)
                      return (char*)current_csg->attributes->first->next->next->data;
                    current_csg = current_csg->next;
                  }
                }
              }
            }
          }
          current_snap = current_snap->next;
        }
      }
    }
  }
  return NULL;
}

//Where is StudentName at Time on Day?”
char* student_Place(hashtable_t *snap, hashtable_t *csg, hashtable_t *cdh, hashtable_t *cr, char *name, char *day, char *hour) {
  //Since it didn't say I wasn't allowed to use relational algebra I'll solve it that way
  attribute_t *namea = ATTRIBUTE_new(STRING, FALSE, "Name", name);
  attribute_t *daya = ATTRIBUTE_new(STRING, FALSE, "Day", day);
  attribute_t *houra = ATTRIBUTE_new(STRING, FALSE, "Hour", hour);
  attribute_t *rooma = ATTRIBUTE_new(STRING, FALSE, "Room", "random");
  attribute_t *coursea = ATTRIBUTE_new(STRING, FALSE, "Course", "random");
  int a = 10;
  attribute_t *sida = ATTRIBUTE_new(INTEGER, TRUE, "StudentId", &a);

  attributelist_t *selection1 = ATTRIBUTELIST_new();
  attributelist_t *selection2 = ATTRIBUTELIST_new();
  attributelist_t *projection1 = ATTRIBUTELIST_new();

  ATTRIBUTELIST_add(selection1, namea);

  ATTRIBUTELIST_add(selection2, daya);
  ATTRIBUTELIST_add(selection2, houra);

  ATTRIBUTELIST_add(projection1, rooma);
  hashtable_t *selection1t = HASHTABLE_selection(snap, selection1);

  hashtable_t *join1t = HASHTABLE_join(selection1t, csg, sida);

  hashtable_t *selection2t = HASHTABLE_selection(cdh, selection2);
  hashtable_t *join2t = HASHTABLE_join(join1t, selection2t, coursea);

  hashtable_t *join3t = HASHTABLE_join(cr, join2t, coursea);

  hashtable_t *projection1t = HASHTABLE_projection(join3t, projection1);

  for(int i = 0; i < projection1t->size; i++) {
    tuplelist_t *list = (projection1t->array[i]);

    if(list != NULL) {
      if(list->first != NULL) {
        tuple_t *current = list->first;

        return current->attributes->first->data;
      }
    }
  }
  return NULL;
}
