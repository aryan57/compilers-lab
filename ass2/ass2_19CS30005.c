/*
####################################
#### Aryan Agarwal              ####   
#### 19CS30005                  ####
#### CS39003 -> Assignment 2    ####
####################################
*/

#include "myl.h"
#define BUFF 100
#define MAX_PRECISION 10

int printStr(char *s)
{

	int i = 0;
	while (s[i] != '\0')
		i++;

	__asm__ __volatile__(
		"movl $1, %%eax \n\t"
		"movq $1, %%rdi \n\t"
		"syscall \n\t"
		:
		: "S"(s), "d"(i));

	return i;
}
int readInt(int *n)
{
	*n = 0; // intialising with zero so *n does not have garbage value if readInt returns ERR

	char buff[BUFF];
	int actual_read = 0;
	__asm__ __volatile__(
		"movl $0, %%eax \n\t"
		"movq $0, %%rdi \n\t"
		"syscall \n\t"
		: "=a"(actual_read)
		: "S"(buff), "d"(BUFF));

	buff[--actual_read] = '\0'; // initialising last character in buffer to 0

	int i = actual_read - 1;
	while (1) // removing ending whitespace
	{
		if (i < 0 || i >= BUFF)
			return ERR;
		if (buff[i] == ' ')
			i--;
		else
			break;
	}

	buff[i + 1] = '\0';
	actual_read = i + 1;

	i = 0;
	while (1) // removing beginning whitespace
	{
		if (i < 0 || i >= BUFF)
			return ERR;
		if (buff[i] == ' ')
			i++;
		else
			break;
	}
	if (i < 0 || i >= BUFF)
		return ERR;

	int flag = 1;
	if (buff[i] == '-') // if integer was -I
	{
		flag = -1;
		i++;
	}
	else if (buff[i] == '+') // if integer was +I
	{
		flag = 1;
		i++;
	}

	// absolute value of integer is from [i,..,actual_read)
	int value = 0;
	for (int k = i; k < actual_read; k++)
	{
		if (buff[k] < '0' || buff[k] > '9')
			return ERR;

		value *= 10;
		value += flag * (buff[k] - '0');
	}

	*n = value;
	return OK;
}

int readFlt(float *f)
{
	*f = 0.0; // intialising with zero so *f does not have garbage value if readFlt returns ERR

	char buff[BUFF];
	int actual_read = 0;
	__asm__ __volatile__(
		"movl $0, %%eax \n\t"
		"movq $0, %%rdi \n\t"
		"syscall \n\t"
		: "=a"(actual_read)
		: "S"(buff), "d"(BUFF));

	buff[--actual_read] = '\0'; // initialising last character in buffer to 0

	int i = actual_read - 1;
	while (1) // removing ending whitespace
	{
		if (i < 0 || i >= BUFF)
			return ERR;
		if (buff[i] == ' ')
			i--;
		else
			break;
	}

	buff[i + 1] = '\0';
	actual_read = i + 1;

	i = 0;
	while (1) // removing beginning whitespace
	{
		if (i < 0 || i >= BUFF)
			return ERR;
		if (buff[i] == ' ')
			i++;
		else
			break;
	}
	if (i < 0 || i >= BUFF)
		return ERR;

	int flag = 1;
	if (buff[i] == '-') // if floating number was -F
	{
		flag = -1;
		i++;
	}
	else if (buff[i] == '+') // if floating number was +F
	{
		flag = 1;
		i++;
	}

	// absolute value of floating number is from [i,..,actual_read)
	float value = 0;
	int dot_found = 0;
	int e_found = 0;
	float fraction_multiplier = 0.1;
	int exp_start = -1;
	int exp_end = actual_read;

	for (int k = i; k < actual_read; k++)
	{
		if (buff[k] == '.')
		{
			if (dot_found)
				return ERR;
			dot_found = 1;
			continue;
		}
		if (buff[k] == 'e')
		{
			if (k == i)
			{   /*
					means no digit or dot before e
				 	since there is no number before e, gcc considers it to be 0 
				*/
				*f = 0;
				return OK;
			}

			e_found = 1;
			exp_start = k + 1;
			break;
		}
		if (buff[k] < '0' || buff[k] > '9')
			return ERR;

		if (!dot_found)
		{
			value *= 10;
			value += buff[k] - '0';
		}
		else
		{
			value += fraction_multiplier * (buff[k] - '0');
			fraction_multiplier *= 0.1;
		}
	}

	if (e_found)
	{
		int exp_num = 0;
		int exp_flag = 1;

		if (exp_start < exp_end && buff[exp_start] == '-')
		{
			exp_flag = -1;
			exp_start++;
		}
		/*
			gcc ignores characters after first non digit after e
			so,
			1e2 = 100 (according to gcc)
			1e2ab = 100 (according to gcc)
			10e1ab12 = 100 (according to gcc)
			1e2.5 = 100 (according to gcc)
			1e2.5abc = 100 (according to gcc)
			100e = 100 (according to gcc)
			100e- = 100 (according to gcc)

			i am implmenting the same here
		*/
		for (int k = exp_start; k < exp_end; k++)
		{
			if (buff[k] < '0' || buff[k] > '9')
				break;
			exp_num *= 10;
			exp_num += buff[k] - '0';	
		}

		while (exp_num>0)
		{
			exp_num--;
			if(exp_flag==1)value*=10;
			else value/=10;
		}
		
	}

	*f = flag * value;
	return OK;
}

int printInt(int n)
{

	char buff[BUFF];
	char zero = '0';

	int i = 0, j, k;
	int is_lower_bound_32_bit = 0;
	if (n == 0)
		buff[i++] = zero;
	else
	{
		if (n < 0)
		{
			/*
				we only have to implment printInt for 32-bit signed integers
				doing n=-n for n=-(2^31), will set n=(2^31)
				which will result in integer overflow
			 	so just dealing the edge case differently
			 */
			if (n == -(1ll << 31))
			{
				is_lower_bound_32_bit = 1;
				n++;
				/*
					adding 1 to it so that n becomes -(2^31) +1
					so when we do n=-n
					n becomes (2^31)-1 which is in range of 32 bit signed integer
				*/
			}
			buff[i++] = '-';
			n = -n;
		}

		// putting digits in reverse order
		while (n)
		{
			if (i >= BUFF)
				return ERR;
			buff[i++] = zero + n % 10;
			n /= 10;
		}

		j = (buff[0] == '-') ? 1 : 0;
		k = i - 1;

		// reversing buff[j...k]
		while (j < k)
		{
			char temp = buff[j];
			buff[j] = buff[k];
			buff[k] = temp;
			j++;
			k--;
		}
	}
	if (i >= BUFF)
		return ERR;

	if (is_lower_bound_32_bit) // adding one again in buff character if n was -(2^31), to make it correct
		buff[i - 1]++;

	buff[i++] = '\0';

	return printStr(buff);
}

int printFlt(float f)
{
	int len = 0;

	if (f < 0)
	{
		printStr("-");
		f = -f;
		len++;
	}

	int integer_part = (int)f;
	float fraction_part = f - integer_part;
	int z = printInt(integer_part);
	if (z == ERR)
		return ERR;

	len += z;
	len += printStr(".");

	char buff[BUFF];
	int rem = MAX_PRECISION; // rem is the remaining digts after decimal left to print
	int i = 0;
	while (rem > 0) // traversing digits after the decimel
	{
		if (i >= BUFF)
			return ERR;
		fraction_part = 10 * fraction_part;
		integer_part = (int)fraction_part;
		if (integer_part > 9 || integer_part < 0)
			return ERR;
		buff[i++] = '0' + integer_part;
		fraction_part = fraction_part - integer_part;
		rem--;
	}

	if (i >= BUFF)
		return ERR;
	buff[i++] = '\0';

	len += printStr(buff);
	return len;
}