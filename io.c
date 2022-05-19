/*
 * File: relation.h
 * Creator: Adam Kaplan
 * Time-stamp: November 27, 2016
 * Project 4
 */

#include "io.h"

void saveToFile(hashtable_t *table, char *filename) {
  FILE *f = fopen(filename, "w");

  if(f != NULL) {
    fprintf(f, "%d\n", table->size);
    fprintf(f, "%d\n", table->typeID);

    for(int i = 0; i < table->size; i ++) {
      tuplelist_t *list = (table->array[i]);

      if(list != NULL) {
        if(list->first != NULL) {
          tuple_t *current = list->first;

          while(current != NULL) {
            fprintf(f, "%d_%d:", current->key, current->typeID);

            attribute_t *currattr = current->attributes->first;

            while(currattr != NULL) {
              if(currattr->rawtypeID == INTEGER)
                fprintf(f, "%d_%d_%s_%d", currattr->rawtypeID, currattr->isKey, currattr->name, *((int*)currattr->data));
              else
                fprintf(f, "%d_%d_%s_%s", currattr->rawtypeID, currattr->isKey, currattr->name, currattr->data);
              if(currattr->next != NULL)
                fprintf(f, "|");
              currattr = currattr->next;
            }
            fprintf(f, "\n");
            current = current->next;
          }
        }
      }
    }
    fclose(f);
  }
  else
    printf("Cannot open file!\n");
}

//For nested strtok: https://stackoverflow.com/questions/4693884/nested-strtok-function-problem-in-c
hashtable_t* getFromFile(char *filename) {
  //Size
  //Type
  //Key_type:Attrrawtype_isKey_name_data-...
  //.
  //.
  //.
  FILE *f = fopen(filename, "r");

  if(f != NULL) {
    int size;
    type_t typeID;
    hashtable_t *table;
    int counter = 1;
    char line[999];
    while(fgets(line, 999, f) != NULL) {
      //strtok(line, "\n");
      //If it is the first line in the file
      if(counter == 1)
        size = atoi(line);
      //If it is the second line in the file
      else if(counter == 2) {
        typeID = atoi(line);
        table = HASHTABLE_new(typeID, size);
      }
      //For all other lines in the file (Singular TUPLE)
      else {
        int tuple_key;
        type_t tuple_typeID;
        attributelist_t *tuple_attributes = ATTRIBUTELIST_new();

        char *endtok1;
        char *split1 = strtok_r(line, ":", &endtok1);
        int c1 = 1;

        //Splitting the general token info from the actual tokens
        while(split1 != NULL) {
          //General info about token
          if(c1 == 1) {
            char *endtok2;
            char *split2 = strtok_r(split1, "_", &endtok2);
            int c2 = 1;

            //Each general piece of information
            while(split2 != NULL) {
              if(c2 == 1) {
                //tuple Key
                tuple_key = atoi(split2);
              }
              else {
                //tuple type
                tuple_typeID = atoi(split2);
              }
              split2 = strtok_r(NULL, "_", &endtok2);
              c2++;
            }
          }
          //Attributes of a token
          else {
            char *endtok2;
            char *split2 = strtok_r(split1, "|", &endtok2);

            //Singular attributes of a token
            while(split2 != NULL) {

              rawtype_t attr_rawtypeID;
              BOOL attr_isKey;
              char *attr_name = (char*)malloc(sizeof(char)*1001 + 1);
              attribute_t *attr;

              char *endtok3;
              char *split3 = strtok_r(split2, "_", &endtok3);
              int c3 = 1;

              //Values of a singular attribute
              while(split3 != NULL) {
                if(c3 == 1) {
                  //rawtype_t
                  attr_rawtypeID = atoi(split3);
                }
                else if(c3 == 2) {
                  //isKey
                  attr_isKey = atoi(split3);
                }
                else if(c3 == 3) {
                  //Name
                  attr_name = split3;
                }
                else {
                  if(attr_rawtypeID == INTEGER) {
                    int temp = atoi(split3);
                    attr = ATTRIBUTE_new(attr_rawtypeID, attr_isKey, attr_name, &temp);
                  }
                  else {
                    char *temp = split3;
                    attr = ATTRIBUTE_new(attr_rawtypeID, attr_isKey, attr_name, temp);
                  }
                }
                split3 = strtok_r(NULL, "_", &endtok3);
                c3++;
              }
              ATTRIBUTELIST_add(tuple_attributes, attr);
              split2 = strtok_r(NULL, "|", &endtok2);
            }
          }
          split1 = strtok_r(NULL, ":", &endtok1);
          c1++;
        }
        tuple_attributes->key = tuple_key;

        tuple_t *tuple = TUPLE_new(tuple_typeID, tuple_attributes);
        HASHTABLE_add(table, tuple);
      }
      counter++;
  }
  fclose(f);
  return table;
}
return NULL;

}
