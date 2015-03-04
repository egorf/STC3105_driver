#include "STC3105.h"

STC3105::STC3105(uint8_t address)
{
	this->devAddr = address;
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
	uint8_t mode_reg = 0;

	// read current mode register state
	I2Cdev::readByte(devAddr, STC3105_REG_MODE, &mode_reg);

	// change the corresponding bit
	mode_reg = enable ? (mode_reg | (1 << 4)) : (mode_reg & ~(1 << 4));

	// write new mode register value
	I2Cdev::writeByte(devAddr, STC3105_REG_MODE, mode_reg);
}

void STC3105::enablePowerSaving(bool enable)
{
	uint8_t mode_reg = 0;

	// read current mode register state
	I2Cdev::readByte(devAddr, STC3105_REG_MODE, &mode_reg);

	// change the corresponding bit
	mode_reg = enable ? (mode_reg | (1 << 2)) : (mode_reg & ~(1 << 2));

	// write new mode register value
	I2Cdev::writeByte(devAddr, STC3105_REG_MODE, mode_reg);
}

void STC3105::enableAlarm(bool enable)
{
	uint8_t mode_reg = 0;

	// read current mode register state
	I2Cdev::readByte(devAddr, STC3105_REG_MODE, &mode_reg);

	// change the corresponding bit
	mode_reg = enable ? (mode_reg | (1 << 3)) : (mode_reg & ~(1 << 3));

	// write new mode register value
	I2Cdev::writeByte(devAddr, STC3105_REG_MODE, mode_reg);	
}

float STC3105::readVoltage()
{
	uint8_t data[2] = {0, 0}; // TO READ
	int vlt = 0;

	I2Cdev::readBytes(devAddr, STC3105_REG_VOLTAGE_LOW, 2, data);
	vlt = data[1] << 8 | data[0];

	return voltage = 0.00244 * (float)vlt;
}

float STC3105::readCurrent()
{
	uint8_t data[2] = {0, 0}; // TO READ
	int crt = 0;

	I2Cdev::readBytes(devAddr, STC3105_REG_CURRENT_LOW, 2, data);
	crt = data[1] << 8 | data[0];

	return current = 0.000001 * 11.77 * (float)crt;
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