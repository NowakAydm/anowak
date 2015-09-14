#include <stdio.h>
#include <stdlib.h>

#include "./libfts.h"

int	main(int ac, char **av)
{
	char *str;

	printf("-----------------------\n");
	printf("        strlen         \n");
	printf("-----------------------");
	str = NULL;
	printf("\n'%s' - len = %d", str, ft_strlen(str));
	str = "";
	printf("\n'%s' - len = %d", str, ft_strlen(str));

	str = "aa";
	printf("\n'%s' - len = %d", str, ft_strlen(str));

	str = "cette chaine fait 30 chars ...";
	printf("\n'%s' - len = %d", str, ft_strlen(str));

	printf("\n\n");
	return (0);
}
