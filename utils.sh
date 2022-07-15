#!/bin/bash

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

function print_ok()
{
	echo -e "$GREEN$@$NC\n"
}

function print_ko()
{
	echo -e "$RED$@$NC\n"
}

function print_color()
{
	echo -e "$1$2$NC\n"
}
