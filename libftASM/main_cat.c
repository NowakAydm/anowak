#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "./libfts.h"

int	main(int ac, char **av)
{
	int fda;
	int fdb;
	int fdc;
	int fdd;

	printf("-----------------------\n");
	printf("          cat         \n");
	printf("-----------------------\n");

	fda = open("tests_cat/aaa", O_RDONLY);
	printf("aaa opened - fd = %d\n", fda);
	ft_cat(fda);
	printf("\n-----------------------");

	fdb = open("tests_cat/bbb", O_RDONLY);
	printf("\nbbb opened - fd = %d\n", fdb);
	ft_cat(fdb);
	printf("\n-----------------------");

	fdc = open("tests_cat/ccc", O_RDONLY);
	printf("\nccc opened - fd = %d\n", fdc);
	ft_cat(fdc);

	printf("\n-----------------------");

	fdd = open("ft_cat.o", O_RDONLY);
	if (fdd > 0)
	{
		printf("\nft_cat.o opened - fd = %d\n", fdd);
		ft_cat(fdd);
		close(fdd);
	}
	printf("\n-----------------------");

	printf("\nTEST NEG FD - fd = -42\n");
	ft_cat(-42);

	printf("\n-----------------------");

	printf("\nTEST FD non ouvert - fd = 60\n");
	ft_cat(60);

	close(fdc);
	close(fdb);
	close(fda);

	printf("\n\n");

	return (0);
}
