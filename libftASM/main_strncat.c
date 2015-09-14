#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./libfts.h"

int	main(int ac, char **av)
{

	printf("-----------------------\n");
	printf("         strncat        \n");
	printf("-----------------------\n");

	char	*a = strdup("abc");
	char	*b = strdup("DEF");

	printf("s1 = '%s'\n", a);
	printf("s2 = '%s'\n", b);

	printf("   =>  str = ft_strncat(s1, s2, 1)\n");
	printf("       str = '%s'\n", (a = ft_strncat(a, b, 1)));
	printf("       str[5] = %d", a[5]);
	

	printf("\n\n");

	return (0);
}
