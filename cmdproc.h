
//******************************************************************************
/**
 * @file cmdproc.h
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/
//******************************************************************************

#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

//------------------------------------------------------------------------------
//Defines
//Other defines should be return codes of the functions
// E.g. #define CMD_EMPTY_STRING -1
#define MAX_CMD_STRING_SIZE 10 		//Maximum size of the command string
#define SOF_SYM '#'					//Start of Frame Symbol
#define EOF_SYM '!'					//End of Frame Symbol


#define SUCCESS 0 					//valid command found and executed
#define CMD_STRING_SIZE_ERROR -1 	//incomplete or empty command
#define CMD_STRING_INVALID -2 		//invalid command
#define ERROR -3 					//command error detected (command not executed)
#define CMD_STRING_FORMAT -4 		//wrong command format

/*
cmdProcessor return values
-> 0: VALID
->-1: EMPTY or INCOMPLETE
->-2: INVALID
->-3: CMD_STRING_ERROR (command not executed)
->-4: CMD_STRING_FORMAT

newCmdChar return values
-> 0: SUCCESS
->-1: CMD_STRING_FULL
*/
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Functions
int cmdProcessor(void);//processes the cmdString
int newCmdChar(char newChar);//adds a char to the cmdString
void resetCmdString(void);//resets the cmdString

void print_usage();
void print_string();

//In the book "Complete Reference of C" it is mentioned that char is by default unsigned
//------------------------------------------------------------------------------

#endif
