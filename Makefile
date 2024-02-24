CC = cc
CFLAGS = -Wall -Wextra -Werror

# 実行ファイル名を `rush-02` に変更
TARGET = rush-02

# ソースファイル
SRC = num_to_text_converter.c dictionary_loader.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
