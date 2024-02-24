// dictionary_loader.h
#ifndef DICTIONARY_LOADER_H
#define DICTIONARY_LOADER_H

typedef struct DictionaryEntry {
    int number;
    char *text;
    struct DictionaryEntry *next;
} DictionaryEntry;

extern DictionaryEntry *dictionaryHead;

void load_dictionary(const char *filename);
void addDictionaryEntry(int number, char *text);
char *findTextForNumber(int number);

#endif
