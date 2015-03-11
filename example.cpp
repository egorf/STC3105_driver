#include <stdio.h>
#include <unistd.h>
#include "STC3105.h"

int main()
{
	printf("hello!\n");

	STC3105 stc = STC3105();

	printf("STC connection established: %d\n", stc.testConnection());

	stc.initialize();
	printf("State-Of-Charge base = %d\n", stc.readStateOfChargeBase());
	printf("Voltage: Current: Charge: \n");

	int time = 0;
	while (1)
	{
		stc.readVoltage();
		stc.readCurrent();
		stc.readStateOfCharge();
		printf("%.3f V  %.3f A  %.3f A.h %d s \n", stc.getVoltage(), stc.getCurrent(), stc.getStateOfCharge(), time);
		time += 4;
		sleep(4);
	}
}
