#ifndef UTIL_H
#define UTIL_H

#define FILE_EXTENSION ".txt"
#define BUFFER_SIZE 255

char *string_to_filename(char *filename);
char *parse_time(char *filename, char *time);
int validate_file(char *filename);

#endif // UTIL_H
