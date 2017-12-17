#ifndef UTIL_H
#define UTIL_H

#define EXIT_VAL '5'
#define BUFFER_SIZE 255
#define FILE_EXTENSION ".txt"
#define HEADER_LINES 3
#define MAX_NAME_LENGTH 20
#define MAX_FILENAME_LENGTH MAX_NAME_LENGTH+4
#define MAX_USER_NAME_LENGTH 20

char *string_to_filename(char *filename);
char *parse_time(char *filename, char *time);
int validate_file(char *filename);

#endif // UTIL_H
