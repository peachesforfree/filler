
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *line;
	while (get_next_line(0, &line))
	{
		dprintf(2,"\t%s\n", line);
	}
	return (0);


}
