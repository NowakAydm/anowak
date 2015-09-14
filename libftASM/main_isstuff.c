#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./libfts.h"

int	main(int ac, char **av)
{

	printf("-----------------------\n");
	printf("        isstuff        \n");
	printf("-----------------------\n");
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  0  |  32 |  47 |  48 |  57 |  58 |  64 |  65 |  90 |  91 |  96 |  97 | 122 | 123 | 127 | 128 | 255 |\n");
	printf("|     | ' ' | '/' | '0' | '9' | ':' | '@' | 'A' | 'Z' | '[' | '`' | 'a' | 'z' | '{' | del |     |     |\n");
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | isalnum\n", isalnum(0), isalnum(32), isalnum(47), isalnum(48), isalnum(57), isalnum(58), isalnum(64), isalnum(65), isalnum(90), isalnum(91), isalnum(96), isalnum(97), isalnum(122), isalnum(123), isalnum(127), isalnum(128), isalnum(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_isalnum\n", ft_isalnum(0), ft_isalnum(32), ft_isalnum(47), ft_isalnum(48), ft_isalnum(57), ft_isalnum(58), ft_isalnum(64), ft_isalnum(65), ft_isalnum(90), ft_isalnum(91), ft_isalnum(96), ft_isalnum(97), ft_isalnum(122), ft_isalnum(123), ft_isalnum(127), ft_isalnum(128), ft_isalnum(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | isalpha\n", isalpha(0), isalpha(32), isalpha(47), isalpha(48), isalpha(57), isalpha(58), isalpha(64), isalpha(65), isalpha(90), isalpha(91), isalpha(96), isalpha(97), isalpha(122), isalpha(123), isalpha(127), isalpha(128), isalpha(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_isalpha\n", ft_isalpha(0), ft_isalpha(32), ft_isalpha(47), ft_isalpha(48), ft_isalpha(57), ft_isalpha(58), ft_isalpha(64), ft_isalpha(65), ft_isalpha(90), ft_isalpha(91), ft_isalpha(96), ft_isalpha(97), ft_isalpha(122), ft_isalpha(123), ft_isalpha(127), ft_isalpha(128), ft_isalpha(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | isascii\n", isascii(0), isascii(32), isascii(47), isascii(48), isascii(57), isascii(58), isascii(64), isascii(65), isascii(90), isascii(91), isascii(96), isascii(97), isascii(122), isascii(123), isascii(127), isascii(128), isascii(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_isascii\n", ft_isascii(0), ft_isascii(32), ft_isascii(47), ft_isascii(48), ft_isascii(57), ft_isascii(58), ft_isascii(64), ft_isascii(65), ft_isascii(90), ft_isascii(91), ft_isascii(96), ft_isascii(97), ft_isascii(122), ft_isascii(123), ft_isascii(127), ft_isascii(128), ft_isascii(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | isdigit\n", isdigit(0), isdigit(32), isdigit(47), isdigit(48), isdigit(57), isdigit(58), isdigit(64), isdigit(65), isdigit(90), isdigit(91), isdigit(96), isdigit(97), isdigit(122), isdigit(123), isdigit(127), isdigit(128), isdigit(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_isdigit\n", ft_isdigit(0), ft_isdigit(32), ft_isdigit(47), ft_isdigit(48), ft_isdigit(57), ft_isdigit(58), ft_isdigit(64), ft_isdigit(65), ft_isdigit(90), ft_isdigit(91), ft_isdigit(96), ft_isdigit(97), ft_isdigit(122), ft_isdigit(123), ft_isdigit(127), ft_isdigit(128), ft_isdigit(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | isprint\n", isprint(0), isprint(32), isprint(47), isprint(48), isprint(57), isprint(58), isprint(64), isprint(65), isprint(90), isprint(91), isprint(96), isprint(97), isprint(122), isprint(123), isprint(127), isprint(128), isprint(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_isprint\n", ft_isprint(0), ft_isprint(32), ft_isprint(47), ft_isprint(48), ft_isprint(57), ft_isprint(58), ft_isprint(64), ft_isprint(65), ft_isprint(90), ft_isprint(91), ft_isprint(96), ft_isprint(97), ft_isprint(122), ft_isprint(123), ft_isprint(127), ft_isprint(128), ft_isprint(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | isupper\n", isupper(0), isupper(32), isupper(47), isupper(48), isupper(57), isupper(58), isupper(64), isupper(65), isupper(90), isupper(91), isupper(96), isupper(97), isupper(122), isupper(123), isupper(127), isupper(128), isupper(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_isupper\n", ft_isupper(0), ft_isupper(32), ft_isupper(47), ft_isupper(48), ft_isupper(57), ft_isupper(58), ft_isupper(64), ft_isupper(65), ft_isupper(90), ft_isupper(91), ft_isupper(96), ft_isupper(97), ft_isupper(122), ft_isupper(123), ft_isupper(127), ft_isupper(128), ft_isupper(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | islower\n", islower(0), islower(32), islower(47), islower(48), islower(57), islower(58), islower(64), islower(65), islower(90), islower(91), islower(96), islower(97), islower(122), islower(123), islower(127), islower(128), islower(255));
	printf("|  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  | ft_islower\n", ft_islower(0), ft_islower(32), ft_islower(47), ft_islower(48), ft_islower(57), ft_islower(58), ft_islower(64), ft_islower(65), ft_islower(90), ft_islower(91), ft_islower(96), ft_islower(97), ft_islower(122), ft_islower(123), ft_islower(127), ft_islower(128), ft_islower(255));
	printf("x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x-----x\n");
	printf("\n\n");
	return (0);
}
