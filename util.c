#include <string.h>
#define FILE_EXTENSION ".txt"

char *string_to_filename(char *filename){
    filename[strlen(filename)-1] = 0;
    strcat(filename, FILE_EXTENSION);
    return filename;
}

char *parse_time(char *filename, char *time){
    char *token = NULL;
    strtok(time, " ");
    token = strtok(NULL, " ");
    strcpy(filename, token);
    strcat(filename, "_");
    token = strtok(NULL, " ");
    strcat(filename , token);
    strcat(filename, "_");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    strncat(filename, token, 4);
    strcat(filename, FILE_EXTENSION);
    return filename;
}
