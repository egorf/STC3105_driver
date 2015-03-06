#include <stdio.h>
#include <unistd.h>
#include "STC3105.h"

int main()
{
	printf("hello!\n");

	STC3105 stc = STC3105();

	printf("STC connection established: %d\n", stc.testConnection());

	stc.initialize();

	while (1)
	{
		stc.readVoltage();
		stc.readCurrent();
		printf("Voltage = %.3f\n", stc.getVoltage());
		printf("Current = %.3f\n", stc.getCurrent());
		sleep(1);
	}
}