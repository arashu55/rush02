// dictionary_loader.h
#ifndef DICTIONARY_LOADER_H
#define DICTIONARY_LOADER_H

#include <stdio.h> // 必要に応じて追加

typedef struct DictionaryEntry {
    char number[128];  // 数値を文字列として格納
    char *text;
    struct DictionaryEntry *next;
} DictionaryEntry;

extern DictionaryEntry *dictionaryHead;

int load_dictionary(const char *filename); // 戻り値の型を int に変更
void addDictionaryEntry(char *number, char *text); // dictionary_loader.hの修正
char *findTextForNumber(char* numberStr);
void free_dictionary(void); // free_dictionary の宣言を追加

#endif
