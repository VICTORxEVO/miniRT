/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:40:27 by ysbai-jo          #+#    #+#             */
/*   Updated: 2025/01/05 11:12:01 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

#define SP_OBJ 0
#define PL_OBJ 1
#define CY_OBJ 2

#define EPSILON 0.0001f

/** Program name displayed in error messages */
# define PRGM_NAME "miniRT"

# define PTR_CLEAR_ERR "clear_1data(): data pointer not found !!"
# define USAGE_WARN "usage: miniRT <map_path>"
# define FILEEXT_ER "file extention must me '.rt' !"
# define EMPTFILE_ERR " is empty !"
# define NOLIGHT_ERR " there is no light!"
# define NOCAM_ERR " there is no camera!"
# define NOAMB_ERR " there is no ambient!"
# define WHITESPACE     " \t\n\r\v\f"  // space, tab, newline, carriage return, vtab, formfeed



// #ifdef LINUX
    #define SCREEN_WIDTH 800.f
    #define SCREEN_HEIGHT 500.f
// #endif


#define STRIPE_X_PAT 1
#define STRIPE_Y_PAT 2
#define STRIPE_Z_PAT 3
#define RING_X_PAT 4
#define RING_Y_PAT 5
#define RING_Z_PAT 6
#define CHECKER_PAT 7

#define XK_RIGHT_CTRL 65508
#define XK_LEFT_CTRL 65507

// Regular text colors
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

// Bold text colors
# define BOLD_BLACK "\033[1;30m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_WHITE "\033[1;37m"

// Underlined text colors
# define UNDERLINE_BLACK "\033[4;30m"
# define UNDERLINE_RED "\033[4;31m"
# define UNDERLINE_GREEN "\033[4;32m"
# define UNDERLINE_YELLOW "\033[4;33m"
# define UNDERLINE_BLUE "\033[4;34m"
# define UNDERLINE_MAGENTA "\033[4;35m"
# define UNDERLINE_CYAN "\033[4;36m"
# define UNDERLINE_WHITE "\033[4;37m"

// Background colors
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"

// Reset color
# define END "\033[0m"

#endif