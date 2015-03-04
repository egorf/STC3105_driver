CC = g++

all:
	$(CC) $(INCLUDES) STC3105.cpp I2Cdev.cpp -o testSTC

clean:
	rm testSTC
