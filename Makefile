# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihuang <ihuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 22:03:28 by ihuang            #+#    #+#              #
#    Updated: 2018/12/03 11:27:53 by ihuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c get_flags.c handle1.c handle2.c helpers1.c helpers2.c \
ftoa.c ftoa2.c
OBJS = ft_printf.o get_flags.o handle1.o handle2.o helpers1.o helpers2.o \
ftoa.o ftoa2.o
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): make_libft
	@echo "Compiling ft_printf OBJS ..."
	@cp ./libft/libft.a $(NAME);
	@gcc $(FLAGS) -c $(SRCS)
	@echo "Compiling $(NAME) ..."
	@ar rc $(NAME) $(OBJS)
	@echo "Done."

make_libft:
	@make -C libft/

clean:
	@echo "Cleaning libft OBJS ..."
	@make -C libft/ clean
	@echo "Cleaning ft_printf OBJS ..."
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft/ fclean
	@echo "Cleaning $(NAME) ..."
	@rm -rf $(NAME)
	@echo "All cleaned."

re: fclean all

again:
	@echo "Compiling $(NAME) ..."
	@rm -rf $(NAME)
	@gcc -g $(FLAGS) -c $(SRCS)
	@ar rc $(NAME) $(OBJS)

test: again
	@echo "Compiling test ..."
	@gcc $(FLAGS) -o test test.c $(NAME) ./libft/libft.a
	@echo "Executing test:\n"
	@./test

debug:
	gcc $(FLAGS) -g -c $(SRCS)
	ar rc $(NAME) $(OJBS)

test2:
	rm -rf $(NAME)
	gcc -g -c $(SRCS)
	ar rc $(NAME) $(OBJS)
	@echo "Compiling test ..."
	@gcc -g $(FLAGS) -o test test.c $(NAME) ./libft/libft.a
	@echo "Executing test:\n"
	@./test
