#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    WRITE = 0,
    READ = 1,
}State;

typedef enum {
    ALL = 0,
    SELECT = 1,
}Readoption;

typedef struct{
    char *albumorsong;
    char *artist;
    int year;
    float estval;
}Vinyl;

void argHandler(int argc, char *argv[], State state);
int read(State state);
int write(State state);

int main(int argc, char *argv[]){
    State state;

    argHandler(argc, argv, state);

    return 0;
}

void argHandler(int argc, char *argv[], State state){
    if(argc > 2){
        printf("Too many arguments\n");
    } else {
        if(argv[1] == NULL){
            printf("- 0 to add\n- 1 to check\n");
            scanf("%d", &state);
            write(state);
            read(state);
        } else if(strcmp(argv[1],"-w") == 0){
            state = WRITE;
            write(state);
        } else if(strcmp(argv[1],"-r") == 0) {
            state = READ;
            read(state);
        } else if(strcmp(argv[1],"-h") == 0) {
            printf("Usage:\tmusin [-w]\tmusin [-r]\n");
        } else {    
            printf("Not an argument, try using the flag -h for help\n");
        }
    }
}

int read(State state){
    Readoption roption;
    char rbuffer[255];
    if(state == READ){ 
        FILE *pF = fopen("music.txt", "r");
        if(pF == NULL){
            printf("Cannot find file\n");
        } else {
            printf("- 0 to read all\n - 1 to select\n");
            scanf("%d", &roption);
            if(roption == ALL) {
                while(fgets(rbuffer, 225, pF) != NULL){
                    printf("Printing all: \n");
                    printf("%s", rbuffer);
                }
            } else if(roption == SELECT) {
                char substr[150];
                printf("Type what to search for: ");
                scanf("%s", substr);
                while(fgets(rbuffer, 225, pF) != NULL){
                    char *Poutput = strstr(rbuffer, substr);
                    printf("Search result: %s", Poutput);
                }    
            }
        }
    fclose(pF);
    } else {
        return 0;
    }
    return 0;
}

// write (append)
int write(State state){
    int counter;
    const char deco[] = "**********************************************";

    if(state == WRITE){
        FILE *pF = fopen("../music.txt", "a");
        printf("How many songs would you like to add?\n");
        scanf("%d", &counter);
            
        // initialize counter amount of Vinyl structs
        for(int i = 0; i < counter; i++){
            Vinyl Vinyl[] = {Vinyl[i].albumorsong, 
                            Vinyl[i].artist, 
                            Vinyl[i].year, 
                            Vinyl[i].estval,
                            };
            
            char *aos = (char*)malloc(50); 
            char *a = (char*)malloc(50); 
            // prompts
            printf("What is the name of the album? (Song if single): \n");
            scanf("%s", aos);
            strcpy(aos, Vinyl[i].albumorsong);
            free(aos);
            printf("What is the name the artist?: \n");
            scanf("%s", a);
            strcpy(a, Vinyl[i].artist);
            free(a);
            printf("What year did the song come out?");
            scanf("%d", &Vinyl[i].year);
            printf("The value of the song is AUD$: ");
            scanf("%f", &Vinyl[i].estval);
            
            // prints vinyl structs into file
            fprintf(pF, " %s\n Album/song name: %s\n- Artist: %s\n- Year: %d\n- Estimated value (AUD): %.2f\n %s\n", 
            deco, Vinyl[i].albumorsong, Vinyl[i].artist, Vinyl[i].year, Vinyl[i].estval, deco);
        }
    fclose(pF);
    } else {
        return 0;
    }
    return 0;
}
