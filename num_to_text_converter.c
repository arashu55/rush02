#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "dictionary_loader.h"

#define BUFFER_SIZE 1024
#define MAX_SECTIONS 10
#define SECTION_LENGTH 4  // 3桁の数字 + 終端のヌル文字

// 数値が正の整数であるかどうかをチェックする関数
int is_positive_integer(const char *str) {
    while (*str) {
        if (!isdigit((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

void convert_section_to_text(char* sectionStr, char* buffer);

char* convert_number_to_text(char* numberStr);

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3 || !is_positive_integer(argv[argc - 1])) {
        printf("Error: Incorrect number of arguments or argument is not a positive integer.\n");
        return 1;
    }

    // 辞書ファイルの処理
    if (argc == 3) {
        load_dictionary(argv[1]);
    } else {
        load_dictionary("numbers.dict");
    }

    load_dictionary("numbers.dict");
    // 引数の数値文字列を英語のテキストに変換して結果を出力
    char *convertedText = convert_number_to_text(argv[argc - 1]);
    printf("%s\n", convertedText);

    free_dictionary();
    return 0;

}

void split_number(char* numberStr, char sections[MAX_SECTIONS][SECTION_LENGTH]) {
    int numLen = strlen(numberStr);
    int sectionIndex = 0;

    // 末尾から3桁ずつセクションを取り出す
    for (int i = numLen; i > 0; i -= 3) {
        if (i - 3 < 0) {
            strncpy(sections[sectionIndex], numberStr, i);
            sections[sectionIndex][i] = '\0';  // 終端文字を追加
        } else {
            strncpy(sections[sectionIndex], &numberStr[i - 3], 3);
            sections[sectionIndex][3] = '\0';  // 終端文字を追加
        }
        sectionIndex++;
    }

    // 逆順で格納されたセクションを正しい順序にする
    for (int i = 0; i < sectionIndex / 2; i++) {
        char temp[SECTION_LENGTH];
        strcpy(temp, sections[i]);
        strcpy(sections[i], sections[sectionIndex - i - 1]);
        strcpy(sections[sectionIndex - i - 1], temp);
    }
}
// 数値を英語のテキストに変換するメイン関数
char* convert_number_to_text(char* numberStr) {
    static char result[1024] = {0};
    memset(result, 0, sizeof(result));
    
    int numLen = strlen(numberStr);
    int sectionCount = (numLen + 2) / 3; // 3桁ごとにセクションを分割
    char* units[] = {"", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion", "decillion", "undecillion"};
    
    for (int i = 0; i < sectionCount; ++i) {
        int sectionStart = numLen - 3 * (i + 1);
        sectionStart = sectionStart < 0 ? 0 : sectionStart;
        int sectionLen = numLen - 3 * i > 3 ? 3 : numLen % 3;
        sectionLen = sectionLen == 0 ? 3 : sectionLen;

        char sectionStr[4] = {0};
        strncpy(sectionStr, &numberStr[sectionStart], sectionLen);

        if (strcmp(sectionStr, "000") != 0) { // セクションが"000"でない場合
            if (i > 0) {
                strcat(result, " ");
                strcat(result, units[i]);
                strcat(result, " ");
            }
            strcat(result, findTextForNumber(sectionStr)); // 単位に対応するテキストを追加
        }
    }
    // 逆順で結果を再構築する必要がある場合は、ここで処理
    // 結果が逆順になっている場合、ここで文字列を反転させる
    return result;
}

// この関数は数値のセクション（例: 1234 -> "one thousand two hundred thirty four"）を処理します
void convert_section_to_text(char* sectionStr, char* buffer) {
    // sectionStrが空でないことを確認
    if (sectionStr == NULL || buffer == NULL) return;

    // 数値を整数に変換
    int number = atoi(sectionStr);

    // 百の位、十の位、一の位を処理
    int hundreds = number / 100;
    int tens = (number % 100) / 10;
    int ones = number % 10;

    // 百の位があれば処理
    if (hundreds > 0) {
        char numberStr[20]; // 文字列バッファを十分なサイズで用意する
        sprintf(numberStr, "%d", hundreds); // 数値を文字列に変換
        strcat(buffer, findTextForNumber(numberStr));
        strcat(buffer, " hundred ");
    }

    // 10以上20未満の特殊な範囲の処理
    if (tens == 1) {
        int specialNumber = number % 100;
        char numberStr[20]; // 文字列バッファを十分なサイズで用意する
        sprintf(numberStr, "%d", specialNumber); // 数値を文字列に変換
        strcat(buffer, findTextForNumber(numberStr));
    } else {
        // 十の位を処理
        if (tens > 1) {
            char numberStr[20]; // 文字列バッファを十分なサイズで用意する
            sprintf(numberStr, "%d", tens * 10); // 数値を文字列に変換
            strcat(buffer, findTextForNumber(numberStr));
            strcat(buffer, " ");
        }
        // 一の位を処理
        if (ones > 0) {
            char numberStr[20]; // 文字列バッファを十分なサイズで用意する
            sprintf(numberStr, "%d", ones); // 数値を文字列に変換
            strcat(buffer, findTextForNumber(numberStr));
        }
    }
    // 最後に余計な空白をトリムする処理を追加することも考慮する
}
