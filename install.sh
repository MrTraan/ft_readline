#!/bin/bash
if [ $# -eq 0 ]; then
	echo "usage: ./install.sh {path_to_libft}"
	exit 1
fi
sed -e "s/PATH_TO_LIBFT/${1//\//\\/}/" -i ".backup" Makefile
