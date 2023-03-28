
/* ****************************************************** */
/* SETR 22/23, Paulo Pedreiras                            */
/* Base code for Unit Testing                             */
/*   A few tests to the cmdProcessor                      */
/*      just to illustrate how it works                   */
/*   Should be improved (e.g. test more cases)            */
/*                                                        */
/* Compile with: gcc cmdproc.c main.c -o main             */
/*                                                        */
/* ****************************************************** */

#include <stdio.h>
#include "cmdproc.h"

//extern char Kp, Ti, Td;//isn't extern declared in the .h???
//i think this line can not be in here

void chars_left();//displays the amount of free space of the cmdString
//void print_usage();

int main(void)
	{
	int res;

	printf("Command processor test app\n\r");
	resetCmdString();
	//newCmdChar('P');
	newCmdChar('#');//SOF -> start of frame symbol
	//newCmdChar('P');
	newCmdChar('1');
	//newCmdChar(' ');
	newCmdChar('2');
	newCmdChar('3');
	//newCmdChar('t');
	//newCmdChar('P');

	//newCmdChar('1');
	//newCmdChar(' ');
	//newCmdChar('2');
	//newCmdChar('3');
	//newCmdChar('t');
	//
	printf("  char 1: '%d'\n", (unsigned char)('P' + '1' + '2' + '3'));
	//'P'=0x50; '1'=0x31; '2'=0x32; '3'=0x33;
	//(unsigned char)('P' + '1' + '2' + '3') = 0xE6=230 (decimal) -> not in ASCII table
	newCmdChar((unsigned char)('P' + '1' + '2' + '3'));
	//
	newCmdChar('!');//EOF -> end of frame symbol
	res = cmdProcessor();
	//printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	printf("  *cmdProcessor output to command '#P123!': return=%d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	printf("\n");
	if((res != SUCCESS) && (cmdStringLen == MAX_CMD_STRING_SIZE)) resetCmdString();
	chars_left();

	newCmdChar('#');
	newCmdChar('D');
	newCmdChar('!');
	res = cmdProcessor();
	printf("  *cmdProcessor output to D (typo, should be S): % d\n\r", res);
	if((res != SUCCESS) && (cmdStringLen == MAX_CMD_STRING_SIZE)) resetCmdString();
	chars_left();

	newCmdChar('+');
	newCmdChar('S');
	newCmdChar('!');
	res = cmdProcessor();
	printf("  *cmdProcessor output to S with wrong SOF: % d\n\r", res);
	if((res != SUCCESS) && (cmdStringLen == MAX_CMD_STRING_SIZE)) resetCmdString();
	chars_left();

	return(0);
	}

void chars_left()//displays the amount of free space of the cmdString
	{
	printf("    space left: %d\n", MAX_CMD_STRING_SIZE - cmdStringLen);
	}

/*
void print_usage()
	{
	printf("    Usage: %d/%d\n\n", cmdStringLen, MAX_CMD_STRING_SIZE);
	}
*/


//every time the cmdProcessor is called and an error happens, should we reset the cmdString ???
//reset only when already full ???
