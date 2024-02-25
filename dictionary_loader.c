// dictionary_loader.c の改善版

#include "dictionary_loader.h" // ヘッダーファイルをインクルード
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// グローバル変数の定義
DictionaryEntry *dictionaryHead = NULL;

void addDictionaryEntry(char *number, char *text) {
    DictionaryEntry *newEntry = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
    strcpy(newEntry->number, number);  // 数値を文字列としてコピー
    newEntry->text = strdup(text);
    newEntry->next = dictionaryHead;
    dictionaryHead = newEntry;
}

// エラーコードを返すように関数のシグネチャを変更
int load_dictionary(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    
    if (!file) {
        printf("Error opening dictionary file.\n");
        return -1; // エラーコードを返す
    }

    char *saveptr; // strtok_r用のポインタ
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // 改行文字を削除
        char *token = strtok_r(line, ":", &saveptr);
        if (token) {
            char *text = strtok_r(NULL, ":", &saveptr);
            if (text) {
                addDictionaryEntry(token, text); // 連結リストに追加
            }
        }
    }
    fclose(file);
    return 0; // 成功時は0を返す
}

void free_dictionary() {
    DictionaryEntry *current = dictionaryHead;
    while (current != NULL) {
        DictionaryEntry *next = current->next;
        free(current->text); // 文字列のメモリを解放
        free(current); // 辞書エントリ自体のメモリを解放
        current = next;
    }
    dictionaryHead = NULL; // ヘッドポインタをNULLにリセット
}

// 辞書から数字の文字列に対応するテキストを検索する関数
char *findTextForNumber(char *numberStr) {
    DictionaryEntry *current = dictionaryHead;
    while (current != NULL) {
        if (strcmp(current->number, numberStr) == 0) {
            return current->text; // 対応するテキストを返す
        }
        current = current->next;
    }
    return NULL; // 見つからなかった場合はNULLを返す
}
