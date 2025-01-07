#program name
NAME = miniRT

# Optimization flags
OPT_FLAGS := -O3 -march=native -ffast-math \
             -ftree-vectorize -fopt-info-vec \
             -funroll-loops -flto \
             -fno-signed-zeros \

# SIMD specific flags (advanced cpu instructions)
SIMD_FLAGS := -msse4.2 -mavx2 -mfma


#cc compiler with all flags
CCF = cc -Wall $(OPT_FLAGS) $(SIMD_FLAGS) # -Wextra # -Werror 
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
		@echo "compiling"
		@sleep 0.5
		@echo "$(NAME) is ready"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		@$(CCF) $(INC) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@echo "cleaning..."


fclean: clean
		@rm -f $(NAME)
		@echo "cleaning program..."


re: fclean all

clear: all clean

bclear: all clean

norm :
		@norminette $(SRC) includes/

run : clear
		@./miniRT maps/map.rt

rrun : clear
		@./miniRT maps/real.rt