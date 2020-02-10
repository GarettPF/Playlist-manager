#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CSV_FILE_PATH "moviePlayList.csv"
#define MAX_CHAR 255

// commands
#define LOAD 1
#define STORE 2
#define DISPLAY 3
#define INSERT 4
#define DELETE 5
#define EDIT 6
#define SORT 7
#define RATE 8
#define PLAY 9
#define SHUFFLE 10
#define EXIT 11

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

/*
Function: isEmpty
Description: Checks whether a linked list is empty
    @param *root        root ptr of the linked list to check
    @return             1 if true || 0 if false
*/
int isEmpty(Node *root);

/*
Functin: push
Description: Pushes the values into a new node
    to be at the top of the linked list
    @param **root_ptr       The address of the ptr to the first element
    @param values           The values to store
    @return                 1 if successful || 0 if unsuccessful
*/
int push(Node **root_ptr, Record values);

// ############# PLAYLIST FUNCTIONS ############

/*
Function: load
Description: Loads the data from the given csv file
    @param **root           The address of the ptr to the first element
    @return                 1 if successful || 0 if unsuccussful
*/
int load(Node **root);

/*
Function: store
Description: Stores the current values of the linked list
    onto the current csv file and overwrites the data
    @param *root            root ptr of the linked list to store
    @param *output          The address to the output file
*/
void store(Node *root, FILE *output);

/*
Function: display
Description: Displays the values of the current linked list
    to the screen in the stdout
    @param *root            root ptr of the linked list to display
    @return                 void
*/
void display(Node *root);

/*
Function: edit
Description: Edits a specific movie chosen by the user
    and is given access to edit any value they want
    @param *root            root ptr of the linked list to edit
    @return                 void
*/
void edit(Node *root);

/*
Function: edit_record
Description: A sub function for the above edit function
    acts as the main editing funcitonality to the user
    @param *dest            Destination to store the edits
    @return                 void
*/
void edit_record(Record *dest);

/*
Function: rate
Description: Gives the user access to rate the movie of their choice
    @param *root            root ptr to the linked list to rate
    @return                 void
*/
void rate(Node *root);

/*
Function: play
Description: Plays the movie by the first one being chosen by the
    user and is cycling throughout the movies and displaying
    all the content within each movie for a quick second
    @param *root            root ptr to the linked list to play
    @return                 void
*/
void play(Node *root);

/*
Function: delay
Description: The delay function to be the way to delay the movies
    before moving onto the next movie within the play function
    @param secs             the amount in secons to delay the console
    @return                 void
*/
void delay(unsigned int secs);