#include "manager.h"

// ############# NODE FUNCTIONS ##############

int isEmpty(Node *root) {

    if (root == NULL) return 1;

    return 0;
}

int push(Node **root_ptr, Record values) {
    Node *root = *root_ptr,

    // create node of pushed values
    *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return 0;

    strcpy(newNode->data.title, values.title);
    strcpy(newNode->data.director, values.director);
    strcpy(newNode->data.description, values.description);
    strcpy(newNode->data.genre, values.genre);
    newNode->data.duration.hours = values.duration.hours;
    newNode->data.duration.minutes = values.duration.minutes;
    newNode->data.year = values.year;
    newNode->data.n_played = values.n_played;
    newNode->data.rating = values.rating;
    newNode->next = NULL;
    newNode->prev = NULL;

    // push new node
    if (isEmpty(*root_ptr)) {
        *root_ptr = newNode;
    } else {
        root->prev = newNode;
        newNode->next = root;
        *root_ptr = newNode;
    }

    return 1;
}

// ############# PLAYLIST FUNCTIONS ############

int load(Node **root) {
    FILE *playlist = fopen(CSV_FILE_PATH, "r");
    if (playlist == NULL) return 0;

    char line[MAX_CHAR];
    fgets(line, MAX_CHAR, playlist);

    while (fgets(line, MAX_CHAR, playlist) != NULL) {
        Record movie = {"","","","", {0,0}, 0,0,0};

        strcpy(movie.title, strtok(line, ","));
        strcpy(movie.director, strtok(NULL, ","));
        strcpy(movie.description, strtok(NULL, ","));
        strcpy(movie.genre, strtok(NULL, ","));
        
        movie.duration.hours = atoi(strtok(NULL, ":"));
        movie.duration.minutes = atoi(strtok(NULL, ","));
        movie.year = atoi(strtok(NULL, ","));
        movie.n_played = atoi(strtok(NULL, ","));
        movie.rating = atoi(strtok(NULL, "\n"));

        if(!push(root, movie)) return 0;
    }
    fclose(playlist);

    return 1;
}

void store(Node *root, FILE *output) {
    
    // start from end
    if (root->next != NULL) {
        store(root->next, output);
    }

    fprintf(output, "%s,%s,%s,%s,%d:%d,%d,%d,%d\n", root->data.title, root->data.director, root->data.description, root->data.genre, root->data.duration.hours, root->data.duration.minutes, root->data.year, root->data.n_played, root->data.rating);
}

void display(Node *root) {
    int choice = 0, year = 0;
    Node *current = root;
    char director[20] = "", temp;

    do {
        system("cls");
        puts("1. Print all movies");
        puts("2. Print all records that match a director");
        puts("3. Print all records that match a year\n");

        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);

    switch (choice) {
        case 1:
            while (current != NULL) {
                puts(current->data.title);
                current = current->next;
            }
            break;

        case 2:
            printf("What director to search for: ");
            scanf("%c", &temp); //temp statement to clear buffer
            gets(director);

            printf("\nMovies under %s\n", director);
            while (current != NULL) {
                if (!strcmp(current->data.director, director))
                    puts(current->data.title);
                current = current->next;
            }
            break;

        case 3:
            printf("What year to search for: ");
            scanf("%4d", &year);

            printf("\nMovies under %d\n", year);
            while (current != NULL) {
                if (current->data.year == year)
                    puts(current->data.title);
                current = current->next;
            }
            break;
    }
    
}

void edit(Node *root) {
    char director[20] = "", title[20] = "", temp;
    Node *current = root,
        *second_current = root;
    int done = 0, choice;

    system("cls");

    printf("Which director: ");
    scanf("%c", &temp);
    gets(director);

    printf("Choose a movie under %s: \n", director);
    while (current != NULL) {
        if (!strcmp(current->data.director, director)) {
            printf("- %s\n",current->data.title);
        }
        current = current->next;
    }

    gets(title);
    while (second_current != NULL) {
        if (!strcmp(second_current->data.title, title)) {
            edit_record(&(second_current->data));
        }
        second_current = second_current->next;
    }
}

void edit_record(Record *dest) {
    int done = 0, choice;
    Record values = {"","","","",{0,0},0,0,0};
    char temp;

    while(!done) {
        do {
            system("cls");
            puts("1. title");
            puts("2. director");
            puts("3. description");
            puts("4. genre");
            puts("5. hours");
            puts("6. minutes");
            puts("7. year");
            puts("8. times played");
            puts("9. rating");
            puts("0. exit");
            scanf("%d", &choice);
        } while (choice < 0 || choice > 9);

        switch (choice) {
            case 0:
                done = 1;
                break;
            case 1:
                printf("New title: ");
                scanf("%c", &temp);
                gets(values.title);
                strcpy(dest->title, values.title);
                break;
            case 2:
                printf("New director: ");
                scanf("%c", &temp);
                gets(values.director);
                strcpy(dest->director, values.director);
                break;
            case 3:
                printf("New description: ");
                scanf("%c", &temp);
                gets(values.description);
                strcpy(dest->description, values.description);
                break;
            case 4:
                printf("New genre: ");
                scanf("%c", &temp);
                gets(values.genre);
                strcpy(dest->genre, values.genre);
                break;
            case 5:
                printf("New hour: ");
                scanf("%c", &temp);
                scanf("%d", &values.duration.hours);
                dest->duration.hours = values.duration.hours;
                break;
            case 6:
                printf("New minute: ");
                scanf("%c", &temp);
                scanf("%d", &values.duration.minutes);
                dest->duration.minutes = values.duration.minutes;
                break;
            case 7:
                printf("New year");
                scanf("%c", &temp);
                scanf("%d", &values.year);
                dest->year = values.year;
                break;
            case 8:
                printf("New times played: ");
                scanf("%c", &temp);
                scanf("%d", &values.n_played);
                dest->n_played = values.n_played;
                break;
            case 9:
                printf("New rating: ");
                scanf("%c", &temp);
                scanf("%d", &values.rating);
                dest->rating = values.rating;
                break;
        }
    }
}

void rate(Node *root) {
    char title[20] = "", temp;
    Node *current = root;
    int rating = 0;

    system("cls");
    while (current != NULL) {
        puts(current->data.title);
        current = current->next;
    }

    printf("Which movie to rate: ");
    scanf("%c", &temp);
    gets(title);

    current = root;
    while (current != NULL) {
        if (!strcmp(current->data.title, title)) {
            do {
                system("cls");
                printf("current rating: %d\n", current->data.rating);
                printf("What do you rate %s: ", title);
                scanf("%d", &rating);
            } while (rating < 1 || rating > 5);

            current->data.rating = rating;
        }

        current = current->next;
    }
}

void play(Node *root) {
    char title[20] = "", temp;
    Node *current = root;

    system("cls");
    while (current != NULL) {
        puts(current->data.title);
        current = current->next;
    }

    printf("Which movie to play first: ");
    scanf("%c", &temp);
    gets(title);

    current = root;
    // move to selected movie
    while (strcmp(current->data.title, title)) {
        current = current->next;
    }

    while (current != NULL) {
        system("cls");
        puts(current->data.title);
        puts(current->data.director);
        puts(current->data.description);
        puts(current->data.genre);
        printf("%d:%d\n", current->data.duration.hours,
                        current->data.duration.minutes);
        printf("%d\n", current->data.year);
        printf("%d\n", current->data.n_played);
        printf("%d\n", current->data.rating);

        delay(2);
        current = current->next;
    }

    current = root;
    while (strcmp(current->data.title, title)) {
        system("cls");
        puts(current->data.title);
        puts(current->data.director);
        puts(current->data.description);
        puts(current->data.genre);
        printf("%d:%d\n", current->data.duration.hours,
                        current->data.duration.minutes);
        printf("%d\n", current->data.year);
        printf("%d\n", current->data.n_played);
        printf("%d\n", current->data.rating);

        delay(2);
        current = current->next;
    }

    system("cls");
    puts("Finished playing");
    system("pause");

}

void delay(unsigned int secs) {
    // save start time
    const time_t start = time(NULL);

    time_t current;
    do {
        // get current time
        time(&current);

        // exit after seconds have passed
    } while (difftime(current, start) < secs);
}