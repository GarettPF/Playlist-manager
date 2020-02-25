/************************************************************
* Programmer: Garett Pascual-Folster					    *
* Class: CptS 122, Spring, 2020; Lab Section 4			    *
* Programming Assignment: PA2							    *
* Date: February 6, 2020								    *
* Description: Video Playlist Manager & Doubly Linked Lists *
************************************************************/

#include "manager.h"
#include "test.h"

int main(void) {
    int done = 0, choice;
    Node *root = NULL;
    srand(time(NULL));

    // test functions
    test_insert();
    test_delete();
    // Node *test_root = NULL;
    load(&test_root);
    test_shuffle();

    while (!done) {
        do {
            system("cls");
            printf("(1)  load\n(2)  store\n(3)  display\n(4)  insert\n");
            printf("(5)  delete\n(6)  edit\n(7)  sort\n(8)  rate\n");
            printf("(9)  play\n(10) shuffle\n(11) exit\n");

            scanf(" %d", &choice);
        } while (choice < 1 || choice > 11);

        // check if list is empty
        if (isEmpty(root) && choice != 1) {
            puts("List is empty\n");
            system("pause");
        } 
        if (choice == EXIT) {
            done = 1;
        } else {
            menu_selection(&root, choice);
        }
    }

    //save on exit
    FILE *file = fopen(CSV_FILE_PATH, "w");
    if (file != NULL) {
        fprintf(file, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n");
        store(root, file);
        fclose(file);
    } else {
        puts("Data was not saved :(");
        system("pause");
    }
    system("cls");
    printf("Goodbye :)\n");

    return 0;
}