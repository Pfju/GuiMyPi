
#include <stdio.h>
#include <stdlib.h>
#include "temperature.h"

double GetTemperature(void)
{
	double temperature = 0;
	char arbuffer[500];
	char artemperature[10];
	int c, k;
	int i=0;
	FILE *fp;
	fp = fopen("/sys/bus/w1/devices/28-000005fd876a/w1_slave", "r");
	if( fp == NULL )
	{
		printf("Cannot open file!\n");
		return 1;
	}

	/* reading entire file into arbuffer */
	while( (c=fgetc(fp)) != EOF )
	{
		arbuffer[i++] = c;
	}
	fclose(fp);

	/* only reading the artemperature from arbuffer */
	for(i=69,k=0; i<=73; i++,k++)
	{
		artemperature[k] = arbuffer[i];
	}
	artemperature[k] = '\0';
	temperature = atof(artemperature);

return (temperature/= 1000);
};

