#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CSV_FILE_PATH "moviePlayList.csv"
#define MAX_CHAR 255

typedef struct record {
    char title[20];
    char director[20];
    char description[200];
    char genre[10];

    struct duration {
        int hours;
        int minutes;
    } duration;

    int year;
    int n_played;
    int rating;
} Record;

typedef struct node {
    Record data;
    struct node *prev;
    struct node *next;
} Node;

// ############# NODE FUNCTIONS ##############

int isEmpty(Node *root);

int push(Node **root_ptr, Record values);

// ############# PLAYLIST FUNCTIONS ############

int load(Node **root);

void store(Node *root, FILE *output);

void display(Node *root);

void edit(Node *root);

void edit_record(Record *dest);

void rate(Node *root);

void play(Node *root);

void delay(unsigned int secs);

int save(Node *root);