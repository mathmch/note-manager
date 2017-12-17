#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 255
#define FILE_EXTENSION ".txt"
#define HEADER_LINES 3

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

int validate_file(char *filename){
    FILE *fp;
    char line[BUFFER_SIZE];
    int count;
    char *headers[3] = {"Title:", "Author:", "Created:"};
    fp = fopen(filename, "r");
    for(count = 0; count < HEADER_LINES; count ++){
        if(fgets(line, BUFFER_SIZE, fp)==NULL){
            fclose(fp);
            return 0;
        }
        if(strncmp(line, headers[count], strlen(headers[count])) != 0){
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}
