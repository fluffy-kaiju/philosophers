# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 08:35:24 by mahadad           #+#    #+#              #
#    Updated: 2022/06/15 16:35:02 by mahadad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               DEV TOOLS
# **************************************************************************** #

STUFF_TO_REMOVE =	\
					*.o\
					*.a\
					.DS_Store\
					.vscode\
					*.dSYM

remove_stuff:
	@for stuff in $(STUFF_TO_REMOVE); do \
	printf "remove all [%s]\n" $$stuff;\
		find . -name $$stuff -prune -exec rm -rf {} \; ;\
	done

git:
	@git pull
	@git diff
	@-git add .
	@git commit -am "Makefile push `date +'%Y-%m-%d %H:%M:%S'`"
	@-git push

# **************************************************************************** #

.PHONY: remove_stuff, git