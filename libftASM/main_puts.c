#include <stdio.h>

#include "./libfts.h"

int	main(int ac, char **av)
{
	int a;
	int b;

	printf("-----------------------\n");
	printf("         puts         \n");
	printf("-----------------------\n");

	char *str = NULL;
	a = puts(str);
	printf("puts    -> RET = %d\n", a);
	b = ft_puts(str);
	printf("ft_puts -> RET = %d\n", a);
	printf("-----------------------\n");

	str = "ABCDEFGHIJKLMNOPQRSTUVWXYZed";
	a = puts(str);
	printf("puts    -> RET = %d\n", a);
	b = ft_puts(str);
	printf("ft_puts -> RET = %d\n", a);
	printf("-----------------------\n");

	str = "Un truc\n  avec\n   des\n    retour\n     a\n      la\n       ligne";
	a = puts(str);
	printf("puts    -> RET = %d\n", a);
	b = ft_puts(str);
	printf("ft_puts -> RET = %d\n", a);

	printf("\n\n");

	return (0);
}
