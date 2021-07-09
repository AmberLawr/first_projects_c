
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


		0. take care of buffer only
				if (buffer == null)
					buffer = malloc(BUFFER_SIZE + 1)  for the \0, in order to treat buffer as a string
					read into buffer
					buffer[read-returnvalue] = \0
				else (buffer != empty)
					if (\0 at the beginning)
						free buffer
						malloc buffer BUFFER_SIZE + 1
						read into buffer
						buffer[read-returnvalue] = \0
					else    // 
						store current buffer value into temporary
						free buffer
						malloc buffer
						read again into buffer
						strjoin (temporary, buffer)
						set \0 at the end


		1. take care of line, rearrange buffer and return values
		if (*memchr(buffer) == \n) buffer contains \n
					if (line == empty) 
					{
						line = substring + \n
						buffer beginning = memmove (len(buffer) + 1) 
						return line
					}
					else (line != empty) 
					{
						strjoin (line, buffer) + \n
						buffer beginning = memmove (len(buffer) + 1)
						return line
					}
		else	when no \n found 
					if (line == empty) 
						line = strdup(buffer)
						buffer[0] = \0
						return (get_next_line)
						// line is not \n terminated so we need to run this function again somehow
					else (line != empty) 
						strjoin(line, buffer)
						buffer[0] = \0
						return (get_next_line)
						// line is not \n terminated so we need to run this function again somehow




*/
