/*
	
	Calling your function get_next_line in a loop will then allow you to read the text
	available on the file descriptor one line at a time until the end of it.

	Your function should return the line that has just been read. If there is nothing
	else to read or if an error has occurred it should return NULL.

		Glossar:
		line = one complete line until \n, may varry in size
		42 Byte = fixed BUFFER_SIZE

		1. if \n: return the whole line plus \n
		2. if line and EOF: return line until EOF 
		3. if error: return NULL
		4. if EOF: return NULL

		static char *buffer;
		char 		*line;
		line = 0;
		
		0. take care of buffer only
				if (buffer == null)
					buffer = malloc(BUFFER_SIZE + 1)  for the \0, in order to treat buffer as a string
					Bytesread = read(fd, buffer, BUFFER_SIZE)
					buffer[Bytesread] = \0
				else (buffer != empty)
					if (\0 at the beginning)
						Bytesread = read(fd, buffer, BUFFER_SIZE)
						buffer[Bytesread] = \0
					else    // 
						temporary = strdup(buffer)
						Bytesread = read(fd, buffer, BUFFER_SIZE)
						buffer[Bytesread] = \0
						temporary2 = strjoin (temporary, buffer)
						free buffer
						free temporary;
						buffer = temporary2
						// bc of strjoin no need for: set \0 at the end


		1. take care of line, rearrange buffer and return values
		if (memchr(buffer, /n)) buffer contains \n
					length = memchr(buffer, \n) - buffer;
					line = substring(buffer, 0, length + 1) 
					buffer = memmove (len(buffer) + 1)
					return line
		else	when no \n found 
					line = strdup(buffer)
					buffer[0] = \0
					newpart = get_next_line(fd);
					joinedline = strjoin(line, newpart);
					free(line);
					free(newpart);
					return (joinedline)




*/
