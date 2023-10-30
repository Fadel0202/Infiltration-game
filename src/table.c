#include <stdio.h>
#include <string.h>

#define TABLE_LENGTH 10
#define TABLE_MAX_STRING_LENGTH 100

void save_table_to_file(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH],char * filename) {
  FILE *fp;
  int i;
  fp = fopen(filename, "wb");
  for (i = 0; i < TABLE_LENGTH; i++) {
    fwrite(table[i], sizeof(char), TABLE_MAX_STRING_LENGTH, fp);
    fwrite(&scores[i], sizeof(int), 1, fp);
  }
  fclose(fp);
}

int load_table_from_file(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH], int *length,char * filename) {
  FILE *fp;
  char buffer[TABLE_MAX_STRING_LENGTH];

  fp = fopen(filename, "rb");
  if (fp == NULL) {
    return 0;
  }

  *length = 0;
  while (fread(buffer, TABLE_MAX_STRING_LENGTH, 1, fp) == 1 && *length < TABLE_LENGTH) {
    strncpy(table[*length], buffer, TABLE_MAX_STRING_LENGTH);
    if (fread(&scores[*length], sizeof(int), 1, fp) != 1) {
      break;
    }
    if(scores[*length] < 0 || scores[*length] >= 5000 ){
      break;
    }
    (*length)++;
  }
  fclose(fp);

  return 1;
}


void print_table(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH],int length) {
  int i;
  for ( i = 0; i < length; i++) {
    printf("%s %d\n", table[i], scores[i]);
  }
}

void add_to_table(char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH], int scores[TABLE_LENGTH], int *length, char *string, int score) {
  int i, j;
  if (*length < TABLE_LENGTH || score < scores[*length - 1]) {
    strncpy(table[*length], string, TABLE_MAX_STRING_LENGTH);
    scores[*length] = score;
    (*length)++;

    for (i = 0; i < *length - 1; i++) {
      for (j = 0; j < *length - i - 1; j++) {
        if (scores[j] > scores[j + 1]) {
          int temp = scores[j];
          scores[j] = scores[j + 1];
          scores[j + 1] = temp;

          char temp_string[TABLE_MAX_STRING_LENGTH];
          strncpy(temp_string, table[j], TABLE_MAX_STRING_LENGTH);
          strncpy(table[j], table[j + 1], TABLE_MAX_STRING_LENGTH);
          strncpy(table[j + 1], temp_string, TABLE_MAX_STRING_LENGTH);
        }
      }
    }
  }
}

