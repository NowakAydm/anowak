#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./libfts.h"

int	main(int ac, char **av)
{

	printf("-----------------------\n");
	printf("         strcat        \n");
	printf("-----------------------\n");

	char	*a = strdup("abc");
	char	*b = strdup("DEF");

	printf("s1 = '%s'\n", a);
	printf("s2 = '%s'\n", b);

	printf("          ==>\n");
	printf("                str = '%s'\n", (a = ft_strcat(a, b)));
	printf("                str[6] = %d", a[6]);
	

	printf("\n\n");

	return (0);
}
