/*
####################################
#### Aryan Agarwal              ####   
#### 19CS30005                  ####
#### CS39003 -> Assignment 2    ####
####################################
*/

#include "myl.h"

int main()
{
	int n = 0;
	float f = 0.0;
	char str[] = "aryan agarwal 123456";

	int result = 0;
	int choice = 0;

	while (1)
	{
		printStr("\n### Main Menu ###\n\n");
		printStr("\t[1] printStr\n");
		printStr("\t[2] readInt\n");
		printStr("\t[3] printInt\n");
		printStr("\t[4] readFlt\n");
		printStr("\t[5] printFlt\n");
		printStr("\n");
		printStr("\t[0] EXIT\n\n");
		printStr("\tEnter your choice : ");

		if (readInt(&choice) == ERR)
		{
			printStr("\tInvalid choice!\nBye:)\n");
			return 0;
		}

		switch (choice)
		{
		case 1:
			printStr("\tThe specified string is : ");
			result = printStr(str);
			printStr("\n");
			printStr("\tNo. of characters printed in the above printStr : ");
			printInt(result);
			printStr("\n");

			break;
		case 2:
			printStr("\tEnter an integer : ");
			result = readInt(&n);
			if (result == ERR)
				printStr("\tYou have entered an invalid integer\n");
			else
				printStr("\tInteger scanned sucessfully\n");

			break;
		case 3:
			printStr("\tLast entered integer : ");
			result = printInt(n);
			printStr("\n");
			if (result == ERR)
				printStr("\tError in printing the given integer.\n");
			else
			{
				printStr("\tNo. of characters printed in the above printInt : ");
				printInt(result);
				printStr("\n");
			}
			break;
		case 4:
			printStr("\tEnter a floating number : ");
			result = readFlt(&f);
			if (result == ERR)
				printStr("\tYou have entered an invalid floating number\n");
			else
				printStr("\tFloating number scanned sucessfully\n");
			break;
		case 5:
			printStr("\tLast entered floating number : ");
			result = printFlt(f);
			printStr("\n");
			if (result == ERR)
				printStr("\tError in printing the given floating number.\n");
			else
			{
				printStr("\tNo. of characters printed in the above printFlt : ");
				printInt(result);
				printStr("\n");
			}
			break;

		default:
			printStr("Bye:)\n");
			return 0;
		}

	}

	return 0;
}
