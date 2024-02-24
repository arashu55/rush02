// dictionary_loader.c の改善版

#include "dictionary_loader.h" // ヘッダーファイルをインクルード
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// グローバル変数の定義
DictionaryEntry *dictionaryHead = NULL;

// 辞書エントリを連結リストに追加する関数
void addDictionaryEntry(int number, char *text) {
    DictionaryEntry *newEntry = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
    newEntry->number = number;
    newEntry->text = strdup(text); // strdup でテキストのコピーを作成
    newEntry->next = dictionaryHead; // 新しいエントリをリストの先頭に追加
    dictionaryHead = newEntry;
}

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
            int number = atoi(token); // 数値に変換
            char *text = strtok_r(NULL, ":", &saveptr);
            if (text) {
                addDictionaryEntry(number, text); // 連結リストに追加
            }
        }
    }
    fclose(file);
    return 0; // 成功時は0を返す
}

char *findTextForNumber(int number) {
    DictionaryEntry *current = dictionaryHead;
    while (current != NULL) {
        if (current->number == number) {
            return current->text;
        }
        current = current->next;
    }
    return NULL; // 見つからない場合
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
