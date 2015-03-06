#include "STC3105.h"

STC3105::STC3105(uint8_t address, float sense_resistor)
{
	this->devAddr = address;
	this->sense_resistor = sense_resistor;
	voltage = 0;
	current = 0;
}

bool STC3105::testConnection()
{
	uint8_t rx;
	int8_t status = I2Cdev::readByte(devAddr, STC3105_REG_ID, &rx);

	return (status > 0) ? true : false;
}

void STC3105::initialize()
{
	enableOperatingMode();
}

void STC3105::enableOperatingMode(bool enable)
{
	I2Cdev::writeBit(devAddr, STC3105_REG_MODE, 4, enable ? 1 : 0);
}

void STC3105::enablePowerSaving(bool enable)
{
	I2Cdev::writeBit(devAddr, STC3105_REG_MODE, 2, enable ? 1 : 0);
}

void STC3105::enableAlarm(bool enable)
{
	I2Cdev::writeBit(devAddr, STC3105_REG_MODE, 3, enable ? 1 : 0);
}

float STC3105::readVoltage()
{
	uint8_t data[2] = {0, 0}; // TO READ
	int vlt = 0;

	I2Cdev::readBytes(devAddr, STC3105_REG_VOLTAGE_LOW, 2, data);
	vlt = data[1] << 8 | data[0];

	voltage = 0.00244 * (float)vlt;

	return voltage;
}

float STC3105::readCurrent()
{
	uint8_t data[2] = {0, 0}; // TO READ
	int crt = 0;
	float voltage_drop;

	I2Cdev::readBytes(devAddr, STC3105_REG_CURRENT_LOW, 2, data);
	crt = data[1] << 8 | data[0];

	// on the sense resistor
	voltage_drop = 0.000001 * 11.77 * (float)crt;

	return current / sense_resistor;
}

float STC3105::getVoltage()
{
	return voltage;
}

float STC3105::getCurrent()
{
	return current;
}

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