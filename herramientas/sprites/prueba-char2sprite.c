#include <stdio.h>
#include <stdlib.h>

int char2sprite(char c)
{
	if (c < '!' || c > '_')
		return -1;
	return (int)c - 33;
}

void
main()
{
	char *str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";

	int i = 0;
	char tmp = str[0];
	while (tmp != '\0')
	{
		printf("%c = %d\n", tmp, char2sprite(tmp));
		i++;
		tmp = str[i];
	}

	exit(0);
}
