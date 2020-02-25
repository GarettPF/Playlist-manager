#include "test.h"

Node *test_root = NULL;

void test_insert(void) {
    int success = push(&test_root, test_case);

    if (!success) {
        puts("Test failed");
    } else {
        for (Node *current = test_root; current != NULL;
            current = current->next) {
            printf("Title: %s\n", current->data.title);
            printf("Director: %s\n", current->data.director);
            printf("Description: %s\n", current->data.description);
            printf("Genre: %s\n", current->data.genre);
            printf("duration: %d:%d\n", current->data.duration.hours,
                            current->data.duration.minutes);
            printf("year: %d\n", current->data.year);
            printf("Times played: %d\n", current->data.n_played);
            printf("Rating: %d\n", current->data.rating);
            printf("\nHead pointer address: %d\n", test_root);
        }
    }
    system("pause");
    system("cls");
}

void test_delete(void) {
    char title[100];
    Node *current = test_root, *prev;

    if (isEmpty(test_root))
        return;
    
    system("cls");
    strcpy(title, test_case.title);

    if (!strcmp(current->data.title, title)) {
        test_root = current->next;
        free(current);
    } else {
        while (current->next != NULL) {
            prev = current;
            current = current->next;

            if (!strcmp(current->data.title, title)) {
                prev->next = current->next;
                free(current);
            }
        }
    }

    // print results
    printf("deleted address: %d\n", current);
    printf("Address of head ptr: %d\n", test_root);
    system("pause");
    system("cls");
}

void test_shuffle(void) {
    Node *counter = test_root;
    int count = 0, num, *pos;

    // get the amount of movies
    while (counter != NULL) {
        count++;
        counter = counter->next;
    }

    // create random order
    int *order = (int*)malloc(sizeof(int*) * count),
        j, i;
    for (i = 0; i < count; ++i) {
        num = rand() % count + 1;
        *(order + i) = num;

        j = i - 1;
        while (j >= 0) {
            if (*(order + j--) == *(order + i))
                i -= 1;
        }
    }

    printf("play order = ");
    for (int i = 0; i < count; i++) {
        printf("%d ", *(order + i));
    }

    printf("\nList state = ");
    // play movies in this order
    int pos_n = 1;
    i = 0;
    while (i < count) {
        if (pos_n == *(order + i)) {
            printf("%s, ", test_root->data.title);
            i++;
        }
        if (pos_n < *(order + i)) {
            pos_n++;
            test_root = test_root->next;
        }
        if (pos_n > *(order + i)) {
            pos_n--;
            test_root = test_root->prev;
        }
    }
    system("pause");
    system("cls");
}