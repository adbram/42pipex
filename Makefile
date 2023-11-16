# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 18:25:35 by aberramo          #+#    #+#              #
#    Updated: 2023/11/16 14:25:51 by aberramo         ###   ########.fr        #
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

SRCDIR_BONUS	= src_bonus
OBJDIR_BONUS	= obj_bonus
SRCS_BONUS		= $(SRCDIR_BONUS)/exec_bonus.c\
					$(SRCDIR_BONUS)/ft_exit_bonus.c\
					$(SRCDIR_BONUS)/ft_putstr_fd_bonus.c\
					$(SRCDIR_BONUS)/ft_split_bonus.c\
					$(SRCDIR_BONUS)/ft_strcpy_bonus.c\
					$(SRCDIR_BONUS)/ft_strjoin_bonus.c\
					$(SRCDIR_BONUS)/ft_strlen_bonus.c\
					$(SRCDIR_BONUS)/ft_strncmp_bonus.c\
					$(SRCDIR_BONUS)/main_bonus.c\
					$(SRCDIR_BONUS)/parser_bonus.c\
					$(SRCDIR_BONUS)/pipex_bonus.c
OBJS_BONUS		= $(patsubst $(SRCDIR_BONUS)/%.c, $(OBJDIR_BONUS)/%.o, $(SRCS_BONUS))

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3
MKDIR			= mkdir
RM				= rm
RMFLAGS			= -f

$(NAME) : $(OBJDIR) $(OBJS)
	@$(RM) $(RMFLAGS) $(OBJDIR_BONUS)/* bonus
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR) :
	@$(MKDIR) $(OBJDIR)

$(OBJDIR_BONUS) :
	@$(MKDIR) $(OBJDIR_BONUS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_BONUS)/%.o : $(SRCDIR_BONUS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

bonus : $(OBJDIR_BONUS) $(OBJS_BONUS)
	@$(RM) $(RMFLAGS) $(OBJDIR)/*
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)
	@touch $@

clean :
	$(RM) $(RMFLAGS) $(OBJDIR)/* $(OBJDIR_BONUS)/* bonus

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

re : fclean all

.PHONY : all clean fclean re
