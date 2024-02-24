// dictionary_loader.h
#ifndef DICTIONARY_LOADER_H
#define DICTIONARY_LOADER_H

#include <stdio.h> // 必要に応じて追加

char *findTextForNumber(int number);

typedef struct DictionaryEntry {
    int number;
    char *text;
    struct DictionaryEntry *next;
} DictionaryEntry;

extern DictionaryEntry *dictionaryHead;

int load_dictionary(const char *filename); // 戻り値の型を int に変更
void addDictionaryEntry(int number, char *text);
char *findTextForNumber(int number);
void free_dictionary(void); // free_dictionary の宣言を追加

#endif
