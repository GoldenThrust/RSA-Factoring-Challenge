#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>

void factorize(const char *buffer);

int main(int argc, char **argv)
{
       	FILE *fptr;
       	char *line = NULL;
       	size_t size = 0;
       
	if (argc != 2)
       	{
		fprintf(stderr, "Usage: ./factors <filename>\n");
	       	exit(EXIT_FAILURE);
	}
	fptr = fopen(argv[1], "r");
	if (fptr == NULL)
	{
		fprintf(stderr, "Error: can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &size, fptr) != -1)
	{
		factorize(line);
	}

	free(line);
	fclose(fptr);

	return 0;
}

void factorize(const char *buffer)
{
	mpz_t num, i, j, remainder, hnum, divnum;
 	mpz_inits(num, i, j, remainder, hnum, divnum, NULL);

	mpz_set_ui(j, 2);
	mpz_set_str(num, buffer, 10);
	mpz_tdiv_q(hnum, num, j);

	mpz_tdiv_r(remainder, num, j);
	mpz_tdiv_q(divnum, num, j);
	if (mpz_cmp_ui(remainder, 0) == 0)
	{
		gmp_printf("%Zd=%Zd*%Zd\n", num, divnum, j);
	}
	else
	{
	for (mpz_set_ui(i, 3); mpz_cmp(i, hnum) < 0; mpz_add_ui(i, i, 2))
	{
		mpz_tdiv_r(remainder, num, i);
		mpz_tdiv_q(divnum, num, i);

		if (mpz_cmp_ui(remainder, 0) == 0)
		{
			gmp_printf("%Zd=%Zd*%Zd\n", num, divnum, i);
			break;
		}
	}
	}
	mpz_clears(num, i, j, remainder, hnum, divnum, NULL);
}
