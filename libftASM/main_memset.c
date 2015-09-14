#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./libfts.h"

int	main(int ac, char **av)
{

	printf("-----------------------\n");
	printf("         memset         \n");
	printf("-----------------------\n");

	char *str = strdup("abcdef");
	printf("__ STR = '%s' __\n", str);
	printf("AVANT :\n");
	printf("%d - %d - %d - %d - %d - %d\n", str[0], str[1], str[2], str[3], str[4], str[5]);

	ft_memset(str, 42, 4);
	printf("\nft_memset(str, 42, 4)\n\n");


	printf("APRES :\n");
	printf("%d - %d - %d - %d - %d - %d\n", str[0], str[1], str[2], str[3], str[4], str[5]);

	printf("\n\n");

	return (0);
}
