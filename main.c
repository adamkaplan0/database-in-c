/*
 * File: main.c
 * Creator: Adam Kaplan
 * Time-stamp: November 27, 2016
 * Project 4
 */

#include "io.h"

int main(int argc, char *argv[]) {
  tuple_t *snap1 = TUPLE_newSNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
  tuple_t *snap2 = TUPLE_newSNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
  tuple_t *snap3 = TUPLE_newSNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");

  tuple_t *snap1c = TUPLE_newSNAP(12345, "C. Brown", "12 Apple St.", "555-1234");
  tuple_t *snap2c = TUPLE_newSNAP(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678");
  tuple_t *snap3c = TUPLE_newSNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");

  tuple_t *snap1d = TUPLE_newSNAP(12346, "C. Brown Different", "12 Apple St.", "555-1234");
  tuple_t *snap2d = TUPLE_newSNAP(67891, "L. Van Pelt Different", "34 Pear Ave.", "555-5678");
  tuple_t *snap3d = TUPLE_newSNAP(22223, "P. Patty Different", "56 Grape Blvd.", "555-9999");

  tuple_t *csg1 = TUPLE_newCSG("CS101", 12345, "A");
  tuple_t *csg2 = TUPLE_newCSG("CS101", 67890, "B");
  tuple_t *csg3 = TUPLE_newCSG("EE200", 12345, "C");
  tuple_t *csg4 = TUPLE_newCSG("EE200", 22222, "B+");
  tuple_t *csg5 = TUPLE_newCSG("CS101", 33333, "A-");
  tuple_t *csg6 = TUPLE_newCSG("PH100", 67890, "C+");

  tuple_t *cp1 = TUPLE_newCP("CS101", "CS100");
  tuple_t *cp2 = TUPLE_newCP("EE200", "EE005");
  tuple_t *cp3 = TUPLE_newCP("EE200", "CS100");
  tuple_t *cp4 = TUPLE_newCP("CS120", "CS101");
  tuple_t *cp5 = TUPLE_newCP("CS121", "CS120");
  tuple_t *cp6 = TUPLE_newCP("CS205", "CS101");
  tuple_t *cp7 = TUPLE_newCP("CS206", "CS121");
  tuple_t *cp8 = TUPLE_newCP("CS206", "CS205");

  tuple_t *cdh1 = TUPLE_newCDH("CS101", "M", "9AM");
  tuple_t *cdh2 = TUPLE_newCDH("CS101", "W", "9AM");
  tuple_t *cdh3 = TUPLE_newCDH("CS101", "F", "9AM");
  tuple_t *cdh4 = TUPLE_newCDH("EE200", "Tu", "10AM");
  tuple_t *cdh5 = TUPLE_newCDH("EE200", "W", "1PM");
  tuple_t *cdh6 = TUPLE_newCDH("EE200", "Th", "10AM");

  tuple_t *cr1 = TUPLE_newCR("CS101", "Turing Aud.");
  tuple_t *cr2 = TUPLE_newCR("EE200", "25 Ohm Hall");
  tuple_t *cr3 = TUPLE_newCR("PH100", "Newton Lab");

  tuple_t *cr1c = TUPLE_newCR("CS101", "Turing Aud.");
  tuple_t *cr2c = TUPLE_newCR("EE200", "25 Ohm Hall");
  tuple_t *cr3c = TUPLE_newCR("PH100", "Newton Lab");

  tuple_t *cr1d = TUPLE_newCR("CS101", "Turing Aud.");
  tuple_t *cr2d = TUPLE_newCR("EE201", "25 Ohm Hall");
  tuple_t *cr3d = TUPLE_newCR("PH100", "Newton Lab");

  tuple_t *cr1cc = TUPLE_newCR("CS101", "Turing Aud.");
  tuple_t *cr2cc = TUPLE_newCR("EE200", "25 Ohm Hall");
  tuple_t *cr3cc = TUPLE_newCR("PH100", "Newton Lab");

  tuple_t *cr1dd = TUPLE_newCR("CS101", "Turing Aud.");
  tuple_t *cr2dd = TUPLE_newCR("EE201", "25 Ohm Hall");
  tuple_t *cr3dd = TUPLE_newCR("PH100", "Newton Lab");

  hashtable_t *snap = HASHTABLE_new(SNAP, 1009);
  hashtable_t *snapc = HASHTABLE_new(SNAP, 1009);
  hashtable_t *snapd = HASHTABLE_new(SNAP, 1009);
  hashtable_t *csg = HASHTABLE_new(CSG, 1009);
  hashtable_t *cdh = HASHTABLE_new(CDH, 1009);
  hashtable_t *cp = HASHTABLE_new(CP, 1009);
  hashtable_t *cr = HASHTABLE_new(CR, 1009);
  hashtable_t *crc = HASHTABLE_new(CR, 1009);
  hashtable_t *crd = HASHTABLE_new(CR, 1009);
  hashtable_t *crcc = HASHTABLE_new(CR, 1009);
  hashtable_t *crdd = HASHTABLE_new(CR, 1009);

  printf("PART 1:\n\n");

  printf("Adding all of SNAP.\n");
  HASHTABLE_add(snap, snap1);
  HASHTABLE_add(snap, snap2);
  HASHTABLE_add(snap, snap3);
  HASHTABLE_add(snapc, snap1c);
  HASHTABLE_add(snapc, snap2c);
  HASHTABLE_add(snapc, snap3c);
  HASHTABLE_add(snapd, snap1d);
  HASHTABLE_add(snapd, snap2d);
  HASHTABLE_add(snapd, snap3d);

  printf("Adding all of CSG.\n");
  HASHTABLE_add(csg, csg1);
  HASHTABLE_add(csg, csg2);
  HASHTABLE_add(csg, csg3);
  HASHTABLE_add(csg, csg4);
  HASHTABLE_add(csg, csg5);
  HASHTABLE_add(csg, csg6);

  printf("Adding all of CP.\n");
  HASHTABLE_add(cp, cp1);
  HASHTABLE_add(cp, cp2);
  HASHTABLE_add(cp, cp3);
  HASHTABLE_add(cp, cp4);
  HASHTABLE_add(cp, cp5);
  HASHTABLE_add(cp, cp6);
  HASHTABLE_add(cp, cp7);
  HASHTABLE_add(cp, cp8);

  printf("Adding all of CDH.\n");
  HASHTABLE_add(cdh, cdh1);
  HASHTABLE_add(cdh, cdh2);
  HASHTABLE_add(cdh, cdh3);
  HASHTABLE_add(cdh, cdh4);
  HASHTABLE_add(cdh, cdh5);
  HASHTABLE_add(cdh, cdh6);

  printf("Adding all of CR.\n\n");
  HASHTABLE_add(cr, cr1);
  HASHTABLE_add(cr, cr2);
  HASHTABLE_add(cr, cr3);
  HASHTABLE_add(crc, cr1c);
  HASHTABLE_add(crc, cr2c);
  HASHTABLE_add(crc, cr3c);
  HASHTABLE_add(crd, cr1d);
  HASHTABLE_add(crd, cr2d);
  HASHTABLE_add(crd, cr3d);
  HASHTABLE_add(crcc, cr1cc);
  HASHTABLE_add(crcc, cr2cc);
  HASHTABLE_add(crcc, cr3cc);
  HASHTABLE_add(crdd, cr1dd);
  HASHTABLE_add(crdd, cr2dd);
  HASHTABLE_add(crdd, cr3dd);

  printf("Printing all of the original databases.\n\n");
  printf("SNAP:\n");
  HASHTABLE_print(snap);
  printf("CSG:\n");
  HASHTABLE_print(csg);
  printf("CP:\n");
  HASHTABLE_print(cp);
  printf("CDH:\n");
  HASHTABLE_print(cdh);
  printf("CR:\n");
  HASHTABLE_print(cr);

  tuple_t *snap1s = TUPLE_newSNAP(12345, "C. Brown", "12 Apple St.", "555-1234");

  printf("Looking up C. Brown from SNAP.\n");
  TUPLE_print(HASHTABLE_lookup(snap, snap1s));

  printf("Deleting C. Brown from SNAP.\n");
  HASHTABLE_delete(snap, snap1s);
  printf("Printing the SNAP database. (without C. Brown of course)\n");
  HASHTABLE_print(snap);

  printf("Inserting C. Brown to SNAP again.\n");
  HASHTABLE_add(snap, snap1s);
  printf("Printing the SNAP database.\n");
  HASHTABLE_print(snap);


  tuple_t *csg1s = TUPLE_newCSG("CS101", 12345, "A");
  int s = 12345;
  attribute_t *sid = ATTRIBUTE_new(INTEGER, TRUE, "StudentId", &s);
  attributelist_t *deletelist = ATTRIBUTELIST_new();


  ATTRIBUTELIST_add(deletelist, sid);

  printf("Looking up 12345 from CSG.\n");
  hashtable_t *selection = HASHTABLE_selection(csg, deletelist);
  printf("finished selection\n");
  HASHTABLE_print(selection);

  printf("Deleting ALL 12345 from CSG.\n");
  HASHTABLE_deleteGeneral(csg, deletelist);
  printf("Printing the CSG database. (without 12345 of course)\n");
  HASHTABLE_print(csg);

  printf("Inserting 12345 CS101 to CSG again.\n");
  HASHTABLE_add(csg, csg1s);
  printf("Printing the CSG database.\n");
  HASHTABLE_print(csg);

  printf("Saving SNAP database to test.txt.\n");
  saveToFile(snap, "test.txt");
  printf("Loading SNAP database from test.txt.\n");
  hashtable_t *test = getFromFile("test.txt");
  printf("Printing loaded SNAP database.\n");
  HASHTABLE_print(test);

  //Add union examples

  printf("PART 2:\n\n");

  printf("What grade did C. Brown get in CS101? %s\n", student_Grade(snap, csg, "C. Brown", "CS101"));

  printf("Where is C. Brown on Mondays at 9AM? %s\n\n", student_Place(snap, csg, cdh, cr, "C. Brown", "M", "9AM"));


  printf("PART 3:\n\n");

  printf("Union of two SNAP tables, which are slightly different:\n");
  printf("Original:\n");
  HASHTABLE_print(snapc);
  printf("Different:\n");
  HASHTABLE_print(snapd);
  printf("Union:\n");
  hashtable_t *union_ = (hashtable_t*)malloc(sizeof(hashtable_t));
  union_ = HASHTABLE_union(snapc, snapd);
  HASHTABLE_print(union_);

  printf("Intersection of two CR tables, which are slightly different:\n");
  printf("Original:\n");
  HASHTABLE_print(crc);
  printf("Different:\n");
  HASHTABLE_print(crd);
  printf("Intersection:\n");
  HASHTABLE_print(HASHTABLE_intersection(crc, crd));

  printf("Difference of two CR tables, which are slightly different:\n");
  printf("Original:\n");
  HASHTABLE_print(crcc);
  printf("Different:\n");
  HASHTABLE_print(crdd);
  printf("Difference:\n");
  HASHTABLE_print(HASHTABLE_difference(crcc, crdd));

  printf("Selecting Course = CS101 from CSG:\n\n");

  attribute_t *select_course = ATTRIBUTE_new(STRING, FALSE, "Course", "CS101");
  attributelist_t *selectlist1 = ATTRIBUTELIST_new();
  ATTRIBUTELIST_add(selectlist1, select_course);
  HASHTABLE_print(HASHTABLE_selection(csg, selectlist1));

  printf("Projecting only the StudentIds from the previous table:\n\n");
  int a = 10;
  attribute_t *project_sid = ATTRIBUTE_new(INTEGER, TRUE, "StudentId", &a);
  attributelist_t *projectlist1 = ATTRIBUTELIST_new();
  ATTRIBUTELIST_add(projectlist1, project_sid);
  HASHTABLE_print(HASHTABLE_projection(HASHTABLE_selection(csg, selectlist1), projectlist1));

  printf("Joining CDH and CR on Course: \n\n");
  hashtable_t *cre = HASHTABLE_new(CR, 1009);
  tuple_t *cr1e = TUPLE_newCR("CS101", "Turing Aud.");
  tuple_t *cr2e = TUPLE_newCR("EE200", "25 Ohm Hall");
  tuple_t *cr3e = TUPLE_newCR("PH100", "Newton Lab");
  HASHTABLE_add(cre, cr1e);
  HASHTABLE_add(cre, cr2e);
  HASHTABLE_add(cre, cr3e);
  attribute_t *join_course = ATTRIBUTE_new(STRING, FALSE, "Course", "random");

  HASHTABLE_print(HASHTABLE_join(cdh, crc, join_course));

  printf("Projecting Day, Hour from The selection of Room=Turing Aud. from the Join of CR and CDH; \n\n");
  attribute_t *daya = ATTRIBUTE_new(STRING, FALSE, "Day", "random");
  attribute_t *houra = ATTRIBUTE_new(STRING, FALSE, "Hour", "random");
  attribute_t *rooma = ATTRIBUTE_new(STRING, FALSE, "Room", "Turing Aud.");
  attributelist_t *selection1 = ATTRIBUTELIST_new();
  attributelist_t *projection1 = ATTRIBUTELIST_new();
  ATTRIBUTELIST_add(projection1, daya);
  ATTRIBUTELIST_add(projection1, houra);
  ATTRIBUTELIST_add(selection1, rooma);

  hashtable_t *joint = HASHTABLE_join(cdh, crc, join_course);

  hashtable_t *selectiont = HASHTABLE_selection(joint, selection1);

  hashtable_t *projectiont = HASHTABLE_projection(selectiont, projection1);
  HASHTABLE_print(projectiont);
}
