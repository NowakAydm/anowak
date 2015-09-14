#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./libfts.h"

int	main(int ac, char **av)
{

	printf("-----------------------\n");
	printf("        strdup         \n");
	printf("-----------------------\n");

	char *str = NULL;

	printf("AVANT :\n");
	printf("adress = %p\n'%s'\n", str, str);
	str = ft_strdup(str);
	printf("APRES :\n");
	printf("adress = %p\n'%s'\n", str, str);
	free(str);
	printf("-----------------------\n");

	str = "abcdef";

	printf("AVANT :\n");
	printf("adress = %p\n'%s'\n", str, str);
	str = ft_strdup(str);
	printf("APRES :\n");
	printf("adress = %p\n'%s'\n", str, str);
	free(str);
	printf("-----------------------\n");

	str = "Un truc beaucoup beaucoup beaucoup plus long avec\ndes\nretours a \nla\nligne t\no\nut partout :)";

	printf("AVANT :\n");
	printf("adress = %p\n'%s'\n", str, str);
	str = ft_strdup(str);	
	printf("APRES :\n");
	printf("adress = %p\n'%s'\n", str, str);
	free(str);
	printf("\n\n");

	return (0);
}
