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
SRC := $(shell find $(SRC_DIR) -type f )
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
