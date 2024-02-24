CC = gcc
CFLAGS = -Wall -Wextra -Werror

# 実行ファイル名
TARGET = num_to_text_converter

# ソースファイル
SRC = num_to_text_converter.c dictionary_loader.c
OBJ = $(SRC:.c=.o)

# デフォルトターゲット
all: $(TARGET)

# オブジェクトファイルから実行ファイルを生成
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# .cから.oへの一般的な規則
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleanターゲット
clean:
	rm -f $(OBJ) $(TARGET)

# fcleanターゲット
fclean: clean

# reターゲット
re: fclean all

.PHONY: all clean fclean re
