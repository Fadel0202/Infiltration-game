#include <stdio.h>
#include <string.h>

#define TABLE_LENGTH 10
#define MAX_STRING_LENGTH 100

void save_table_to_file(char table[TABLE_LENGTH][MAX_STRING_LENGTH], int scores[TABLE_LENGTH]) {
  FILE *fp;
  fp = fopen("test", "wb");
  for (int i = 0; i < TABLE_LENGTH; i++) {
    fwrite(table[i], sizeof(char), MAX_STRING_LENGTH, fp);
    fwrite(&scores[i], sizeof(int), 1, fp);
  }
  fclose(fp);
}

void load_table_from_file(char table[TABLE_LENGTH][MAX_STRING_LENGTH], int scores[TABLE_LENGTH]) {
  FILE *fp;
  fp = fopen("test", "rb");
  for (int i = 0; i < TABLE_LENGTH; i++) {
    fread(table[i], sizeof(char), MAX_STRING_LENGTH, fp);
    fread(&scores[i], sizeof(int), 1, fp);
  }
  fclose(fp);
}