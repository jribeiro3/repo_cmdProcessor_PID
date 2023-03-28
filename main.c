
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

//******************************************************************************
/**
 * @file main.c
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
*/
//******************************************************************************

#include <stdio.h>//to use printf, scanf, getchar

#include "cmdproc.h"

//----------------------------------------------------------
//local variables declaration
int menuOption, c, ret;
//----------------------------------------------------------

//----------------------------------------------------------
//Functions declaration
static void printMenu();
static void readMenuOption();
void print_usage();
void print_string();
//----------------------------------------------------------

//******************************************************************************
int main()
	{
	printf("Command processor test app\n\r");
	resetCmdString();

	printMenu();
	while(1)
		{
		//printMenu();
		readMenuOption();//read the input of the menu option

		switch(menuOption)
			{
			//----------------------------------------------
			case(1)://cmdString insertion
				printf("  ->cmdString insertion\n");

				char newChar;
				printf("  element: ");
				scanf("%c", &newChar);

				//flushes the stdin
				while(((c = getchar()) != '\n') && (c != EOF));

				if(newCmdChar(newChar) == -1) printf("Full\n");

				break;
			//----------------------------------------------
			case(2)://cmdString usage
				printf("  ->cmdString usage\n");
				print_usage();
				break;
			//----------------------------------------------
			case(3)://cmdString print
				printf("  ->cmdString print\n");
				print_string();
				break;
			//----------------------------------------------
			case(4)://cmdString process
				printf("  ->cmdString process\n");
				ret = cmdProcessor();

				switch(ret)
					{
					case 0:
						printf("    Valid command\n");
						break;
					case -1:
						printf("    Empty or incomplete command\n");
						break;
					case -2:
						printf("    Invalid command\n");
						break;
					case -3:
						printf("    Error detected\n");
						break;
					case -4:
						printf("    Wrong format of the command\n");
						break;
					default:
						printf("    Default\n");
						break;
					}

				break;
			//----------------------------------------------
			case(5)://cmdString reset
				printf("  ->cmdString reset\n");
				resetCmdString();
				break;
			//----------------------------------------------
			case(9)://help
				printf("  ->help\n");
				printMenu();
				break;
			//----------------------------------------------
			case(0)://Exit
				printf("  Exit!!!\n");
				return(0);
			//----------------------------------------------
			default:
				break;
			//----------------------------------------------
			}
		menuOption = -1;//resets the menuOption
		}
	return(0);
	}
//******************************************************************************

//------------------------------------------------------------------------------
static void printMenu()
	{
	printf("+===============================================+\n"
		   "|            Manipulation functions             |\n"
		   "+===============================================+\n"
		   "| 1: Insert char in cmdString                   |\n"
		   "| 2: Print cmdString usage                      |\n"
		   "| 3: Print cmdString                            |\n"
		   "| 4: Process cmdString                          |\n"
		   "| 5: Reset cmdString                            |\n"
		   "| 9: Help                                       |\n"
		   "| 0: Quit                                       |\n"
		   "+===============================================+\n\n");
	}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
static void readMenuOption()
	{
	menuOption = -1;
	do
		{
		printf("Option: ");
		scanf("%d", &menuOption);

		//flushes the stdin
		while(((c = getchar()) != '\n') && (c != EOF));

		if((menuOption < 0) || (menuOption > 9)) printf("  Invalid value!\n");
		}
	while((menuOption < 0) || (menuOption > 9));
	//printf("Selected: %d\n", menuOption);
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

//every time the cmdProcessor is called and an error happens, should we reset the cmdString ???
//reset only when already full ???
