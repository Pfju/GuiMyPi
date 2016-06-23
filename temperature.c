#include "temperature.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_READ 500

/*
 * Parameters: void
 * Return: double - temperature
 * Description:
 * Access temperature.dat to read the temperature and return it.
 */
double GetTemperature(void)
{
	double temperature = 0;
	char arbuffer[MAX_READ];
	char artemperature[10];
	int iNumberofChars;
	int file_desc, close_err;
	int k, i;

	file_desc = open("temperature.dat", O_RDONLY);
	if(file_desc < 0)
	{
		printf("Cannot open file!\n");
		return 1;
	}

	/* reading entire file into arbuffer */
	iNumberofChars = read(file_desc, arbuffer, MAX_READ);
	/* close file descriptor again */
	close_err = close(file_desc);
	if(close_err < 0)
		printf("Cannot close file!\n");

	/* only reading the temperature from buffer */
	for(i = 69, k = 0; i <= 73; i++, k++)
	{
		artemperature[k] = arbuffer[i];
	}
	artemperature[k] = '\0';
	temperature = atof(artemperature);
	return (temperature/= 1000);
};
