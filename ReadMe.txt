

This is an example file to explain using Unity in Keil for STM32 projects

Projectmain.c 	- Application file
Retarget.c		- Functions for redirecting serial port to Keil debug printf viewer
Serial.c		- Serial port driver with build switch for ITM transfer.
Unity.c			- Unity unit test framework.
Test.c			- Example unit test function