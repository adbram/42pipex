# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 18:25:35 by aberramo          #+#    #+#              #
#    Updated: 2023/11/05 19:10:20 by aberramo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEAULT_GOAL	= all
NAME			= pipex

SRCDIR			= src
OBJDIR			= obj

SRCS			= $(SRCDIR)/exec.c\
					$(SRCDIR)/ft_exit.c\
					$(SRCDIR)/ft_putstr_fd.c\
					$(SRCDIR)/ft_split.c\
					$(SRCDIR)/ft_strcpy.c\
					$(SRCDIR)/ft_strjoin.c\
					$(SRCDIR)/ft_strlen.c\
					$(SRCDIR)/ft_strncmp.c\
					$(SRCDIR)/main.c\
					$(SRCDIR)/parser.c\
					$(SRCDIR)/pipex.c
OBJS			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3
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
