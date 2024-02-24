#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "dictionary_loader.h"

// 数値が正の整数であるかどうかをチェックする関数
int is_positive_integer(const char *str) {
    while (*str) {
        if (!isdigit((unsigned char)*str)) // 非数字の文字があれば0を返す
            return 0;
        str++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Incorrect number of arguments.\n");
        return 1;
    }

    if (!is_positive_integer(argv[1])) {
        printf("Error\n"); // 正の整数でない場合はエラーを出力
        return 1;
    }

    long number = atol(argv[1]);

    // 数値が0またはunsigned intの範囲を超える場合はエラーを出力
    if (number <= 0 || number > UINT_MAX) {
        printf("Number out of range\n");
        return 1;
    }
    // num_to_text_converter.c の一部

    // 辞書ファイルの読み込み
    load_dictionary("numbers.dict");

    long number = strtol(argv[1], NULL, 10); // コマンドライン引数から数値を受け取る

    char *result = convert_number_to_text(number); // 数値を文字列に変換する関数を呼び出す

    if (result != NULL) {
        printf("%s\n", result); // 結果を出力
    } else {
        printf("The number %ld cannot be converted.\n", number);
    }

    // 数値を文字列に変換する関数
    char* convert_number_to_text(unsigned long long number) {
        static char buffer[1024] = {0}; // 結果を格納するバッファ
        char temp[128]; // 一時的な文字列を格納するバッファ

        // 辞書データの読み込み
        DictionaryEntry *dictionary = load_dictionary("numbers.dict");

        if (number == 0) {
            strcpy(buffer, find_dictionary_text(dictionary, 0)); // "zero" の特別なケース
            return buffer;
        }

        load_dictionary("numbers.dict");

        // この関数は、数値を文字列に変換する具体的な処理を行います。
    char* convert_number_to_text(unsigned long long number) {
        static char buffer[1024] = {0}; // 結果を格納するバッファ
        memset(buffer, 0, sizeof(buffer)); // バッファをクリア

        // 辞書データの読み込み（既に main で呼び出されているため、ここでは不要）
        // DictionaryEntry *dictionary = load_dictionary("numbers.dict");

        if (number == 0) {
            strcpy(buffer, "zero");
            return buffer;
        }

        // 千の単位以上の数値を処理
        const char *units[] = {"", "thousand", "million", "billion", "trillion", "quadrillion","quintillion", "sextillion", "septillion", "octillion","nonillion", "decillion", "undecillion"};
        unsigned long long unit_value = 1;
        int unit_index = 0;

        while (number > 0) {
            if (number % 1000 > 0) {
                char temp[128] = {0};
                // ここで number % 1000 の値を単語に変換（後述）
                convert_three_digits_to_text(number % 1000, temp, dictionary);
                if (unit_index > 0) {
                    strcat(temp, " ");
                    strcat(temp, units[unit_index]);
                    strcat(temp, " ");
                }
                strcat(temp, buffer); // 新しい単位を追加
                strcpy(buffer, temp);
            }
            number /= 1000;
            unit_index++;
        }
    // 辞書データの解放は main 関数内で行う
    free_dictionary(dictionary);

    return buffer;
    }

    void convert_three_digits_to_text(unsigned int number, char *result, DictionaryEntry *dictionary) {
    strcpy(result, ""); // 結果を格納する文字列を初期化
    if (number >= 100) {
        // 百の位を処理
        strcat(result, findTextForNumber(number / 100, dictionary));
        strcat(result, " hundred ");
        number %= 100; // 残りの数値を更新
    }
    if (number >= 20) {
        // 十の位を処理
        if (result[0] != '\0') strcat(result, "and ");
        strcat(result, findTextForNumber(number - number % 10, dictionary)); // 十の位に対応する文字列を追加
        number %= 10; // 残りの数値を更新
    }
    if (number > 0) {
        // 一の位を処理
        if (result[0] != '\0') strcat(result, "and ");
        strcat(result, findTextForNumber(number, dictionary)); // 一の位に対応する文字列を追加
    }
}





        // 辞書データの解放
        free_dictionary(dictionary);

        return buffer;
    }

    // 辞書からテキストを検索する補助関数（架空の関数、実際の辞書検索ロジックに置き換える）
    char* find_dictionary_text(DictionaryEntry *dictionary, unsigned long long number) {
        // 辞書データから number に対応する文字列を検索して返す
        // 実際には、辞書データ構造と検索アルゴリズムに基づいて実装する
    return "";
}