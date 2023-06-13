# pipex

## Introduction
Pipex is a 42 school student project, the aim of which is to understand more about UNIX mechanisms through the creation of a program that behaves like a simple pipe command.

## Features
- Lightweight implementation of UNIX pipe mechanism in C.
- Receives four arguments: file1, cmd1, cmd2, file2.
- Runs as follows: ```./pipex file1 cmd1 cmd2 file2```.
- Behaves exactly the same as the shell command: ```< file1 cmd1 | cmd2 > file2```.
- Mandatory and bonus part evaluations done separately.
- Error handling in cases such as segmentation faults, bus errors, double frees, etc.
- Support for multiple pipes and redirections in the bonus part.

## Installation

```sh
git clone https://github.com/your_username/pipex.git
cd pipex
make
```
This will compile the source files and generate the necessary executable.

## Usage
After compilation, execute the program as follows:

```sh
./pipex file1 cmd1 cmd2 file2
```
Replace file1, cmd1, cmd2 and file2 with your own arguments. cmd1 and cmd2 are shell commands with their parameters.

Examples
```c
./pipex infile "ls -l" "wc -l" outfile behaves like: < infile ls -l | wc -l > outfile.
./pipex infile "grep a1" "wc -w" outfile behaves like: < infile grep a1 | wc -w > outfile.
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

