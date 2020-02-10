/************************************************************
* Programmer: Garett Pascual-Folster					    *
* Class: CptS 122, Spring, 2020; Lab Section 4			    *
* Programming Assignment: PA2							    *
* Date: February 6, 2020								    *
* Description: Video Playlist Manager & Doubly Linked Lists *
************************************************************/

#include "manager.h"

int main(void) {
    int done = 0, choice;
    FILE *file = NULL;

    Node *root = NULL;

    while (!done) {
        do {
            system("cls");
            printf("(1)  load\n(2)  store\n(3)  display\n(4)  insert\n");
            printf("(5)  delete\n(6)  edit\n(7)  sort\n(8)  rate\n");
            printf("(9)  play\n(10) shuffle\n(11) exit\n");

            scanf(" %d", &choice);
        } while (choice < 1 || choice > 11);

        switch (choice) {
            case LOAD:
                load(&root);
                break;

            case STORE:
                if (!isEmpty(root)) {
                    file = fopen(CSV_FILE_PATH, "w");
                    fprintf(file, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n");
                    store(root, file);
                    fclose(file);
                } else {
                    puts("List is empty\n");
                    system("pause");
                }
                break;

            case DISPLAY:
                display(root);
                system("pause");
                break;

            case INSERT:
                break;

            case DELETE:
                break;

            case EDIT:
                edit(root);
                break;

            case SORT:
                break;

            case RATE:
                rate(root);
                break;

            case PLAY:
                play(root);
                break;

            case SHUFFLE:
                break;

            case EXIT:
                done = 1;
                break;
        }
    }

    //save on exit
    file = fopen(CSV_FILE_PATH, "w");
    fprintf(file, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating\n");
    store(root, file);
    fclose(file);

    system("cls");
    printf("Goodbye :)\n");

    return 0;
}