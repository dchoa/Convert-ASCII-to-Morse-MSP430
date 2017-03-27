#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>

#define TIMEUNIT 100000

//ENCODE TABLE
typedef struct
{
	char *morse;
	char *ascii;
}morse_table_t;
morse_table_t table[] = {
	{ ".-", "A" },
	{ "-...", "B" },
	{ "-.-.", "C" },
	{ "-..", "D" },
	{ ".", "E" },
	{ "..-.", "F" },
	{ "--.", "G" },
	{ "....", "H" },
	{ "..", "I" },
	{ ".---", "J" },
	{ "-.-", "K" },
	{ ".-..", "L" },
	{ "--", "M" },
	{ "-.", "N" },
	{ "---", "O" },
	{ ".--.", "P" },
	{ "--.-", "Q" },
	{ ".-.", "R" },
	{ "...", "S" },
	{ "-", "T" },
	{ "..-", "U" },
	{ "...-", "V" },
	{ ".--", "W" },
	{ "-..-", "X" },
	{ "-.--", "y" },
	{ "--..", "Z" }
};
//STRING MAINIPULATION
int length(char* ch)
{
	int i = 1;
	while (ch[i] != '\0')
		i++;
	return i;
}
char upper(char str)
{
	char result = NULL;
	if ((str >= 'a') && (str <= 'z'))
		return(str - 32);
}
char* toMorse(char Ascii)
{
   int i =0;
	for (i = 0; i <= 26; i++)
	{
		if (Ascii == *(table[i].ascii))
			return table[i].morse;
	}
}

int main()
{
	WDTCTL = WDTPW + WDTHOLD;
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR = BIT0 | BIT6;
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT6;
   
	char* str = "Whatever you want";
	while (1)
	{
		int i,j = 0;
		for (i = 0; i < length(str); i++)
		{
			if (str[i] == ' ')
				__delay_cycles(7 * TIMEUNIT);
			else
			{
				char* result = toMorse(upper(str[i]));
				for (j = 0; j < length(result); j++)
				{
					if (result[j] == '.')
					{
						P1OUT ^= BIT0;
						__delay_cycles(TIMEUNIT);
						P1OUT ^= BIT0;
						__delay_cycles(TIMEUNIT);
					}
					else
					{
						P1OUT ^= BIT6;
						__delay_cycles(3 * TIMEUNIT);
						P1OUT ^= BIT6;
						__delay_cycles(TIMEUNIT);
					}
				}
				__delay_cycles(3 * TIMEUNIT);
			}
		}
	}
return 0;
}