# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/30 09:24:07 by hbally            #+#    #+#              #
#    Updated: 2018/11/30 17:56:39 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	fdf	

BINDIR				=	bin

PROJDIR				=	~/dev/42_fdf

SRCSDIR   			=	srcs

SRCS			   :=	$(SRCSDIR)/main.c			\
						$(SRCSDIR)/get_input.c		\
						$(SRCSDIR)/build_map.c		\
						$(SRCSDIR)/get_next_line.c

OBJSDIR   			=	objs

OBJS  			   :=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

INCLUDES			=   -I libft/includes 			\
						-I includes					\
						-I minilibx_macos			\

LIBS				=	-L libft/ -lft				\
						-L minilibx_macos/ -lmlx 	\
						-framework OpenGL			\
						-framework AppKit

CFLAGS			   +=	-Wall -Werror -Wextra

CC					=	gcc

all					:	$(BINDIR)/$(NAME)

$(BINDIR)/$(NAME)	: 	$(OBJS)
						make -C minilibx_macos/
						make -C libft/
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJS)

.PHONY				:	run
run					:	$(BINDIR)/$(NAME)
						clear
						@$(PROJDIR)/$(BINDIR)/fdf $(PROJDIR)/maps/test.fdf

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY				:	clean
clean				:
						rm -f $(OBJS)
						make clean -C minilibx_macos/
						make clean -C libft/

.PHONY				:	fclean
fclean				:	clean
						rm -f $(BINDIR)/$(NAME)
						make fclean -C libft/

re					:	fclean all
