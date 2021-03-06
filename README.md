# Custom Database in `C`

## General Information

As a college project, I had to implement my own database system. This includes the most basic operations on a database such as selection, projection and join. I also included functionalities such as union, intersection, and difference, which will be described in more detail below. All of this is implemented using a hash table. The examples used are from the `FOCS` registrar database.

## How To Get Going

My submission includes a make file, so just run the make file and it will create a executable for you. Then just run `./main`.

## Implementation Specifics

I used a linked list to represent the attributes for each tuple and a linked list to connect each tuple in a relation. I used an array of tuple lists as the basis for my hash table.

### Database Operations

* **Insert:** If the tuple has a key, I insert it using hashing otherwise I add it to the first linked list in my hash table.
* **Lookup:** I can either lookup a specific tuple in the hash table or if I want some more layway I can use the select function and specify what attributes matter to me and which do not.
* **Delete:** I can either delete a specific tuple or delete all the tuples with specific attributes, I used a modified selection function for this functionality.
* **Union:** I just used the pseudo-code from the book to build this method.
* **Intersection:** This is just a modified union function, as the only thing that changes is the condition under which I add an element.
* **Difference:** Just like intersection, this is only a modified union function with a slightly altered condition.
* **Selection:** Here I differentiated between if one of the attributes was a key or not, as well as how many attributes there are. Based on that I used the algorithms we went over in class.
* **Projection:** I used the algorithm we went over in class, which was loop over all tuples and just delete all of the attributes that we do not care about and save it as a new hash table.
* **Join:** This was by far the most complicated function of them all. Here I differentiated between if the index was a key or not, and if it was I used a index join, otherwise I used a nested-loop join.

## Examples

* I use the registrar database from the book as the basis and show how all of the functions work. Since it is a lot to print, I copy and pasted it to the `OUTPUT.txt` for you to read.
* I show how to save a database in a file. In my example I save the SNAP database in a .txt file and also read it back in.

## File Information

* `main.c` -- The main method is in this file, it is where all of the functionalities are shown.
* `relation.c` -- The core file. It includes all database related functions.
* `relation.h` -- Header for the core file.
* `io.c` -- The IO method file. It contains all of the IO functions.
* `io.h` -- Header for the IO methods.
* `OUTPUT.txt` -- Copy & Paste of the terminal output.
* `test.txt` -- Sample save of the SNAP database. (gets recreated every time you run the program)
* `Makefile`
