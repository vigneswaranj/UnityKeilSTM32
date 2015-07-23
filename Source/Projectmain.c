
#include <stdio.h>
/*Unity Framework*/
#include<setjmp.h>
#include "unity.h"
/*Test functions*/
#include "Test.h"

void runTest(UnityTestFunction test)
{
	if(TEST_PROTECT())
	{
		test();
	}
}

int main()
{
	
	/*Print to show STM32 Redirecting serial port*/
	printf("Hello world \n");
	
	/**/
	UnityBegin("Test.c");
	RUN_TEST(testWillAlwaysPass);
	
	return (UnityEnd());

}
