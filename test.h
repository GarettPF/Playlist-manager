#ifndef _TEST_H_
#define _TEST_H_

#include "manager.h"

static Record test_case = {
    "Bohemian rhapsody",
    "Bryan Singer",
    "Freddie mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.",
    "Drama",
    {
        2,
        13
    },
    2018,
    -1,
    6
};

extern Node *test_root;

/*
Function: test_insert
Description: tests the manager.h files' insert function
    with the given global variable test_case
    @param void
    @return void
*/
void test_insert(void);

/*
Function: test_delete
Description: tests the manager.h files' delete function
    with the given global variable test_case
    @param void
    @return void
*/
void test_delete(void);

/*
Function: test_shuffle
Description: tests the manager.h files' shuffle function
    by listing the play order and movies
    @param void
    @return void
*/
void test_shuffle(void);

#endif // #ifndef _TEST_H_