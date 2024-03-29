# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 13:03:02 by aarribas          #+#    #+#              #
#    Updated: 2022/10/04 17:53:51 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#files
INCLUDES_SRCS	=	pipex.h
INCLUDES_DIR	=	includes/
INCLUDES		=	$(addprefix	$(INCLUDES_DIR), $(INCLUDES_SRCS))


FUNCTIONS_SRCS	=	ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c
FUNCTIONS_DIR	=	functions/
FUNCTIONS		=	$(addprefix $(FUNCTIONS_DIR), $(FUNCTIONS_SRCS))
OBJ_F			=	$(FUNCTIONS:.c=.o)

MANDATORY_SRCS	=	pipex.c child_process.c utils.c
MANDATORY_DIR	=	mandatory/
MANDATORY		=	$(addprefix $(MANDATORY_DIR), $(MANDATORY_SRCS))
OBJ_M			=	$(MANDATORY:.c=.o)

#main
NAME	=	pipex
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra 
OBJS	=	$(SRCS:.c=.o)
RM		=	rm -rf

%.o: %.c $(INCLUDES) Makefile
				${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_F) $(OBJ_M)
				$(CC) $(OBJ_F)	$(OBJ_M) -o $(NAME)
				

all:		$(NAME)

clean:	
		$(RM)	$(OBJ_F)
		$(RM)	$(OBJ_M)

fclean:		clean
			$(RM) $(NAME)	

re:			fclean	all

.PHONY:		all clean fclean bonus re
