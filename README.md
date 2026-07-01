*This project was created as part of the 42 curriculum by dimatos-.*

# Get Next Line

## Description

`get_next_line` is a function written in C that reads a complete line from a file descriptor.

The goal of the project is to implement the function:

```c
char	*get_next_line(int fd);
```

Each call to `get_next_line(fd)` returns the next available line from the given descriptor. This makes it possible to read a file, standard input (`stdin`), or any other valid descriptor line by line until the end of the content is reached or an error occurs.

The returned line includes the newline character `\n` when it exists in the file. If the file ends without a final `\n`, the last line is still returned without adding any extra characters.

This project is useful for practicing fundamental C concepts such as:

- the use of `read()`;
- manual memory management with `malloc()` and `free()`;
- handling dynamic strings;
- file descriptors;
- static variables;
- progressive data reading without loading the entire file at once.

## Instructions

### Main files

The mandatory part of the project contains the following files:

```text
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

### Compilation

The project must compile with the usual 42 flags:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

`BUFFER_SIZE` defines how many bytes `read()` reads on each call. It may be changed during the evaluation, so the function must work correctly with different values:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c
```

The project must also compile when `BUFFER_SIZE` is not specified, using a default value defined in the header.

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## Algorithm and justification

The main idea of the algorithm is to read only what is necessary on each call to `get_next_line`.

Instead of reading the entire file from the beginning, the function uses a static variable to keep, between calls, the content that has already been read but has not yet been returned to the user.

This persistent memory is usually called `stash`, `buffer_save`, or a similar name.

The general process is the following:

1. **Validate the descriptor and buffer size**  
   Before reading, the function checks that `fd` is valid and that `BUFFER_SIZE` has a useful value.

2. **Read from the descriptor until a complete line is found**  
   `read(fd, buffer, BUFFER_SIZE)` is used to read blocks of data. Each block read is appended to the content stored in the static variable.

3. **Stop reading when a `\n` appears**  
   When the accumulated content contains a newline, a complete line already exists and can be returned. There is no need to keep reading more data from the file.

4. **Extract the line to return**  
   The function creates a new string with the characters from the beginning of the stored content up to and including the first `\n`. If there is no `\n`, all accumulated content is returned until the end of the file.

5. **Update the static variable**  
   After extracting the line, only the remaining content is kept, meaning the characters that came after the `\n`. That remainder will be used in the next call.

6. **Free memory when it is no longer needed**  
   If the end of the file is reached or an error occurs, the dynamically allocated memory must be freed correctly to avoid memory leaks.

This algorithm is appropriate because it respects the progressive reading required by the project. The function does not load the entire file into memory; instead, it reads in chunks until it can return a single line. This allows it to work with both small and large files, as well as with `stdin`, where the total amount of available data is not always known in advance.

The use of a static variable is necessary because each call to `get_next_line` must remember what was left over from the previous read. Without this persistent memory, the characters read after a newline would be lost.

## Expected behavior

`get_next_line` must return:

- the line read, if everything goes well;
- `NULL` if there is nothing else to read;
- `NULL` if a read or memory allocation error occurs.

Important cases to test:

- empty file;
- file with a single line and no final `\n`;
- file with several lines;
- very long lines;
- `BUFFER_SIZE=1`;
- large `BUFFER_SIZE`;
- reading from `stdin`;
- repeated calls until `NULL` is returned.

## Restrictions

Authorized functions:

```text
read
malloc
free
```

Not allowed:

```text
libft
lseek
global variables
```

## Bonus

The bonus part adds support for multiple file descriptors at the same time.

Bonus files:

```text
get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h
```

The idea is that the function can read from several `fd`s while alternating calls, without mixing the lines from one descriptor with those from another.

For example:

```c
line1 = get_next_line(fd1);
line2 = get_next_line(fd2);
line3 = get_next_line(fd1);
line4 = get_next_line(fd2);
```

To achieve this, the bonus part must keep an independent reading state for each descriptor.

## Resources

Useful references for understanding the concepts used in this project:

- `man 2 read`
- `man 3 malloc`
- `man 3 free`
- Documentation about Unix/Linux file descriptors
- Documentation about static variables in C
- Documentation about dynamic memory management in C

### Use of AI

Artificial intelligence was used as a learning and documentation support tool.

It was used to:

- Better understand the project subject.
- Structure and improve the README.
- Clarify concepts related to variadic functions.
- Review explanations about the algorithm and technical decisions.
- Improve the wording of the documentation.

AI was not used as a replacement for understanding the code. The implementation, debugging, and final decisions were reviewed and understood manually as part of the learning process.
