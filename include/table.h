#ifndef __TABLE__
#define __TABLE__


#include <stdio.h>
#include <string.h>

#define TABLE_LENGTH 10
#define TABLE_MAX_STRING_LENGTH 100

void save_table_to_file(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH],char * filename);
int load_table_from_file(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH], int *length,char * filename);
void print_table(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH],int length) ;
void add_to_table(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH], int *length, char *string, int score);

#endif