# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 18:25:35 by aberramo          #+#    #+#              #
#    Updated: 2023/10/23 19:10:57 by aberramo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEAULT_GOAL	= all
NAME			= pipex

SRCDIR			= src
OBJDIR			= obj
INCDIR			= inc

SRCS			= $(SRCDIR)/main.c\
					$(SRCDIR)/pipex.c\
					$(SRCDIR)/checker.c
OBJS			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

INCFLAGS		= -I$(INCDIR)
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 $(INCFLAGS)
MKDIR			= mkdir
RM				= rm
RMFLAGS			= -f

$(NAME) : $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR) :
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(RMFLAGS) $(OBJDIR)/*

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

re : fclean all

.PHONY : all clean fclean re
