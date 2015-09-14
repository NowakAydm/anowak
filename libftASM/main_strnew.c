#include <stdio.h>
#include <stdlib.h>

#include "./libfts.h"

int	main(int ac, char **av)
{
	char *str = NULL;

	ft_puts("-----------------------");
	ft_puts("        strnew         ");
	ft_puts("-----------------------");

	ft_puts("AVANT :");
	printf("%p\n", str);
	str = ft_strnew(100);
	ft_puts("APRES :");
	printf("%p\n", str);	str = ft_strnew(100);
	ft_puts("APRES :");
	printf("%p\n", str);
	printf("\n\n");

	free(str);
	return (0);
}
