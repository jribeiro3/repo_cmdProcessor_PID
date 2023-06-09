
/* ****************************************************** */
/* SETR 22/23, Paulo Pedreiras                            */
/* Base code for Unit Testing                             */
/*    Simple example of command processor                 */
/*    Note that there are several simplifications         */
/*    E.g. Kp, Ti and Td usually are not integer values   */
/*    Code can (and should) be improved. E.g. error       */
/*        codes are "magic numbers" in the middle of the  */
/*        code instead of being (defined) text literals   */
/* ****************************************************** */

//******************************************************************************
/**
 * @file cmdproc.c
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/
//******************************************************************************

#include <stdio.h>//to use printf
#include <string.h>//to use the strcpy

#include "cmdproc.h"

//------------------------------------------------------------------------------
//Global variables declarations

//PID parameters -> external variables
//Kp: proportional gain
//Ti: integration period
//Td: derivation period
/* Note that in a real application these vars would be extern */
//can not be used as double because of lack of number separator
int Kp, Ti, Td;

//Process variables -> external variables
/* Note that in a real application these vars would be extern */
//can not be used as double because of lack of number separator
int setpoint, output, error;

/* Internal variables */
//In the book "Complete Reference of C" it is mentioned that char is by default unsigned
static char cmdString[MAX_CMD_STRING_SIZE];//string -> should it be unsigned???
//static unsigned char cmdStringLen = 0;//should not it be int instead of char???
static int cmdStringLen = 0;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//**********************************************************
//Processes the chars received so far looking for commands
//-Returns:
//   0: if a valid command was found and executed
//  -1: if empty string or incomplete command found
//  -2: if an invalid command was found
//  -3: if a CS error is detected (command not executed)
//  -4: if string format is wrong
//**********************************************************
int cmdProcessor(void)
	{
	int i;

	//Detect empty cmdString
	if(cmdStringLen == 0) return(-1);//error: the command is empty or incomplete

	//Find the index of SOF_SYM -> start of frame symbol -> may not be the 1st char of the cmdString
	for(i = 0; i < cmdStringLen; i++)//searches for SOF symbol along the cmd string
		{
		if(cmdString[i] == SOF_SYM) break;//the SOF symbol was found
		}

	//printf("hello!!!\n");

	//If a SOF_SYM was found, look for command
	if(i < cmdStringLen)
		{
		if( ((i + 1) < cmdStringLen) && (cmdString[i + 1] == 'P') ) /* P command detected */
			{
			//P command -> input {Kp; Ti; Td}
			printf("    Command P: ");

			//the command does not have all the correct fields -> missing parameters
			//parameters => {SOF; P; Kp; Ti; Td; EOF}
			if((i + 5) >= cmdStringLen) return(-1);//the command is incomplete

			//the cmdString does not have the EOF_SYM
			if(cmdString[i + 5] != EOF_SYM) return(CMD_STRING_INVALID);
			//should it be this error or should it be CMD_STRING_SIZE_ERROR, or ERROR, or CMD_STRING_FORMAT ???

			//printf("char: %c\n", cmdString[i + 2]);
			//convert char to int (typecasting conversion) -> (int)newChar -> conversion error ???
			if((cmdString[i + 2] >= '0') && (cmdString[i + 2] <= '9'))
				{
				Kp = (int)cmdString[i + 2];//proportional gain (typecasting conversion)
				//printf("Kp:%d\n", Kp);
				}
			else
				{
				return(CMD_STRING_FORMAT);//correct error???
				}

			//printf("char: %c\n", cmdString[i + 3]);
			//convert char to int (typecasting conversion) -> (int)newChar -> conversion error ???
			if( (cmdString[i + 3] >= '0') && (cmdString[i + 3] <= '9') )
				{
				Ti = (int)cmdString[i + 3];//integration period (typecasting conversion)
				//printf("Ti:%d\n", Ti);
				}
			else
				{
				return(CMD_STRING_FORMAT);//correct error???
				}

			//printf("char: %c\n", cmdString[i + 4]);
			//convert char to int (typecasting conversion) -> (int)newChar -> conversion error ???
			if( (cmdString[i + 4] >= '0') && (cmdString[i + 4] <= '9') )
				{
				Td = (int)cmdString[i + 4];//derivation period (typecasting conversion)
				//printf("Td:%d\n", Td);
				}
			else
				{
				return(CMD_STRING_FORMAT);//correct error???
				}

			printf("  Kp=%c, Ti=%c, Td=%c \n\r", Kp, Ti, Td);

			resetCmdString();
			return(SUCCESS);//a valid command was found and executed
			}

		if( ((i + 1) < cmdStringLen) && (cmdString[i + 1] == 'S') ) /* S command detected */
			{
			//S command -> output {Setpoint; Output; Error}
			printf("    Command S: ");

			//the command does not have all the correct fields
			//parameters => {SOF; S; EOF}
			if((i + 2) >= cmdStringLen) return(-1);//the command is incomplete

			//the cmdString does not have the EOF_SYM
			if(cmdString[i + 2] != EOF_SYM) return(CMD_STRING_INVALID);
			//should it be this or should it be CMD_STRING_SIZE_ERROR, or ERROR, or CMD_STRING_FORMAT ???

			printf("  Setpoint=%d, Output=%d, Error=%d\n", setpoint, output, error);
			resetCmdString();
			return(SUCCESS);//a valid command was found and executed
			}

		return(-1);//incomplete command
		}

	//if a SOF was not found
	/* cmd string not null and SOF not found */
	return(CMD_STRING_FORMAT);//command string format is wrong
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//**********************************************************
//Adds a char to the cmd string
//-Returns:
//   0: if success
//  -1: if cmdString full
//**********************************************************
//In the book "Complete Reference of C" it is mentioned that char is by default unsigned
int newCmdChar(char newChar)
	{
	//if not full, add char
	if(cmdStringLen < MAX_CMD_STRING_SIZE)
		{
		cmdString[cmdStringLen] = newChar;//char insertion
		cmdStringLen += 1;//update
		return(SUCCESS);//success
		}

	printf("    ERROR: cmdString FULL\n");
	//print_string();
	//print_usage();

	//if cmdString full, return error
	return(-1);//error: the cmdString is full
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Resets the command string
void resetCmdString(void)
	{
	cmdStringLen = 0;//usage of the string

	//is it necessary to overwrite the string ??
	strcpy(cmdString, "");//cleans the string

	return;
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void print_usage()
	{
	printf("    Usage: %d/%d\n", cmdStringLen, MAX_CMD_STRING_SIZE);
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void print_string()
	{
	printf("    string: '");
	for(int i = 0; i < cmdStringLen; i++) printf("%c", cmdString[i]);
	printf("'\n");
	}
//------------------------------------------------------------------------------
