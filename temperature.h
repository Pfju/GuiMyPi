#ifndef TEMPERATURE_HEADER
#define TEMPERATURE_HEADER

/*
function: GetTemperature(void)

Returns the temperature from GPIO#7
Kernel modules w1-gpio and w1-therm must be activated
Using 1-wire bus communication for information transition

params: none
return: double
*/
double GetTemperature(void);

#endif
