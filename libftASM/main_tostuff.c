#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./libfts.h"

int	main(int ac, char **av)
{

	printf("-----------------------\n");
	printf("        tostuff        \n");
	printf("-----------------------\n");

	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  0  |  32 |  47 |  48 |  57 |  58 |  64 |  65 |  90 |  91 |  96 |  97 | 122 | 123 | 177 | 178 | 255 |\n");
	printf("|     | ' ' | '/' | '0' | '9' | ':' | '@' | 'A' | 'Z' | '[' | '`' | 'a' | 'z' | '{' | del |     |     |\n");
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d | %d | %d | %d | %d | toupper\n", toupper(0), toupper(32), toupper(47), toupper(48), toupper(57), toupper(58), toupper(64), toupper(65), toupper(90), toupper(91), toupper(96), toupper(97), toupper(122), toupper(123), toupper(177), toupper(178), toupper(255));
	printf("|  %d  |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d |  %d | %d | %d | %d | %d | ft_toupper\n", ft_toupper(0), ft_toupper(32), ft_toupper(47), ft_toupper(48), ft_toupper(57), ft_toupper(58), ft_toupper(64), ft_toupper(65), ft_toupper(90), ft_toupper(91), ft_toupper(96), ft_toupper(97), ft_toupper(122), ft_toupper(123), ft_toupper(177), ft_toupper(178), ft_toupper(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d |  %d |  %d |  %d |  %d |  %d |  %d | %d |  %d |  %d |  %d | %d | %d | %d | %d | %d | tolower\n", tolower(0), tolower(32), tolower(47), tolower(48), tolower(57), tolower(58), tolower(64), tolower(65), tolower(90), tolower(91), tolower(96), tolower(97), tolower(122), tolower(123), tolower(177), tolower(178), tolower(255));
	printf("|  %d  |  %d |  %d |  %d |  %d |  %d |  %d |  %d | %d |  %d |  %d |  %d | %d | %d | %d | %d | %d | ft_tolower\n", ft_tolower(0), ft_tolower(32), ft_tolower(47), ft_tolower(48), ft_tolower(57), ft_tolower(58), ft_tolower(64), ft_tolower(65), ft_tolower(90), ft_tolower(91), ft_tolower(96), ft_tolower(97), ft_tolower(122), ft_tolower(123), ft_tolower(177), ft_tolower(178), ft_tolower(255));

	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");

	printf("\n\n");
	return (0);
}
