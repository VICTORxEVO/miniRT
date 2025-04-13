#program name
NAME = miniRT



#cc compiler with all flags
CCF = cc -Wall  -Wextra -Werror 
EXTRA_LIBS = -lm
MLX_FLG = -L ./mlx  -l mlx_Linux -l Xext -l X11 -l m -l z -O3
USER_FLG = -D USER=\"$(USER)\"

# Directories
SRC_DIR := source
OBJ_DIR := objects

# Source and Object Files
SRC := source/rendering/vector.c \
	source/rendering/interset.c \
	source/rendering/mlx.c \
	source/rendering/utils.c \
	source/rendering/color3.c \
	source/rendering/color2.c \
	source/rendering/getters.c \
	source/rendering/redering.c \
	source/rendering/cylinder.c \
	source/rendering/light.c \
	source/rendering/camera.c \
	source/rendering/vector1.c \
	source/rendering/color1.c \
	source/parsing/check.c \
	source/parsing/shapes_parse.c \
	source/parsing/parsing1.c \
	source/parsing/utils/utils.c \
	source/parsing/utils/utils1.c \
	source/parsing/shapes_parse1.c \
	source/parsing/parsing.c \
	source/miniRT.c \
	source/clear/clear.c \
	source/clear/pexit.c \
	source/clear/clear1.c \
	source/clear/galloc.c \
	source/utils/utils_convert.c \
	source/utils/utils_lst.c \
	source/external/ft_atoi.c \
	source/external/ft_strlcpy.c \
	source/external/ft_substr.c \
	source/external/ft_strlcat.c \
	source/external/ft_strchr.c \
	source/external/ft_split.c \
	source/external/ft_strdup.c \
	source/external/ft_isalpha.c \
	source/external/ft_isprint.c \
	source/external/get_next_line/get_next_line_utils.c \
	source/external/get_next_line/get_next_line.c \
	source/external/ft_memcpy.c \
	source/external/ft_strlen.c \
	source/external/ft_strncmp.c \
	source/external/ft_split_malloc.c \
	source/external/ft_isalnum.c \
	source/external/ft_itoa.c \
	source/external/ft_putstr_fd.c \
	source/external/ft_strrchr.c \
	source/external/ft_strnstr.c \
	source/external/ft_isdigit.c \
	source/external/ft_strtrim.c \
	source/external/ft_striteri.c \
	source/external/ft_strjoin.c \
	source/external/ft_isascii.c \
	source/external/ft_strcmp.c 

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


#include header
INC = -I ./includes

DEBUG = GDB
#debuging
ifeq ($(DEBUG), GDB)
	CCF += -g3
else ifeq ($(DEBUG), ALL)
	CCF += -g3 -fsanitize=address
endif

.PHONY: all clean fclean re clear

all: $(NAME)

$(NAME): $(OBJ)
		@$(CCF) $(OBJ) $(INC) $(MLX_FLG) $(EXTRA_LIBS) -o $@
		@echo "linking..."
		@sleep 0.5
		@echo "$(NAME) is ready"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		@printf "\rcompiling %s" "$<"
		@$(CCF) $(OPT_FLAGS) $(INC) -c $< -o $@
		@sleep 0.02
		@printf "\r\033[K"
clean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning..."


fclean: clean
		@rm -f $(NAME)
		@echo "cleaning program..."


re: fclean all

clear: all clean

bclear: all clean

run: all clean
		./miniRT maps/real.rt

norm :
		@norminette $(SRC) includes/
