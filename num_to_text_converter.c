#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "dictionary_loader.h"

#define BUFFER_SIZE 1024

// 数値が正の整数であるかどうかをチェックする関数
int is_positive_integer(const char *str) {
    while (*str) {
        if (!isdigit((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

void convert_section_to_text(unsigned long long section, char* buffer);

char* convert_number_to_text(unsigned long long number);

int main(int argc, char *argv[]) {
    if (argc != 2 || !is_positive_integer(argv[1])) {
        printf("Error: Incorrect number of arguments or argument is not a positive integer.\n");
        return 1;
    }

    long number = strtol(argv[1], NULL, 10);
    if (number < 0 || number > UINT_MAX) {
        printf("Error: Number out of range.\n");
        return 1;
    }

    load_dictionary("numbers.dict");
    char *result = convert_number_to_text(number);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("The number %ld cannot be converted.\n", number);
    }
    free_dictionary();
    return 0;
}

char* convert_number_to_text(unsigned long long number) {
    static char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer)); // バッファをクリア

    if (number == 0) {
        strcpy(buffer, findTextForNumber(0));
        return buffer;
    }

    // 数値がunsigned intの範囲を超える場合のエラー処理
    if (number > UINT_MAX) {
        printf("Error: Number out of range.\n");
        return NULL;
    }

    unsigned long long section;
    int unitIndex = 0;
    const char* units[] = {"", "thousand", "million", "billion", "trillion"}; // 必要に応じて単位を拡張

    while (number > 0) {
        section = number % 1000; // 最後の3桁を取得
        if (section > 0) {
            char sectionText[128] = "";
            convert_section_to_text(section, sectionText);
            if (unitIndex > 0) {
                strcat(buffer, units[unitIndex]);
                strcat(buffer, " ");
            }
            strcat(buffer, sectionText);
        }
        number /= 1000; // 次の3桁へ
        unitIndex++;
    }

    return buffer;
}

void convert_section_to_text(unsigned long long section, char* buffer) {
    if (section == 0) return;

    int hundred = section / 100;
    int rest = section % 100;

    if (hundred > 0) {
        strcat(buffer, findTextForNumber(hundred));
        strcat(buffer, " hundred");
    }
    if (rest > 0) {
        if (hundred > 0) strcat(buffer, " and ");
        // 20以下または10の倍数の場合、直接テキストを追加
        if (rest <= 20 || rest % 10 == 0) {
            strcat(buffer, findTextForNumber(rest));
        } else {
            // 21から99までの数で、1の位と10の位を分けて処理
            int tens = rest / 10 * 10;
            int ones = rest % 10;
            strcat(buffer, findTextForNumber(tens));
            strcat(buffer, "-");
            strcat(buffer, findTextForNumber(ones));
        }
    }
}
// 辞書からテキストを検索する関数
char *findTextForNumber(int number) {
    DictionaryEntry *current = dictionaryHead;
    while (current != NULL) {
        if (current->number == number) {
            return current->text; // 対応するテキストを見つけた場合は返す
        }
        current = current->next; // 次のエントリへ
    }
    return NULL; // 見つからない場合はNULLを返す
}
