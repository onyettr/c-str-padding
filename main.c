#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/**
 * @brief 				pad_string
 *
 * @param hex_num		Number to be printed
 * @param check_num		check number to test for
 * @param width			size of output buffer
 * @param pad_char		padding character
 * @param destination	output buffer
 * @notes				function to add an integer to a buffer. If the number is
 * 						equal to teh check number then if will instead pack the
 * 						pad character into the buffer
 * 						Done originally for printing '--------' if a number was
 * 						equal to Zero.
 */
void pad_string(uint32_t hex_num,
				uint32_t check_num,
				int width,
		        const char pad_char,
		        char *destination)
{
	/*
	 * Example: 32-bit integer to be printed as hex
     *                      1
     * 0 1 2 3 4 5  6 7 8 9 0
     * 0 x 8 0 0 0  0 0 0 0 \0
     */
	if (destination == NULL)
	{
		return;
	}

	memset(destination, pad_char, width);
	destination[width-1] = '\0';

    if (hex_num != check_num)
    {
    	sprintf(destination, "0x%08X", hex_num);
    }
}

/**
 * @brief pad_string_ret
 *
 * @param hex_num
 * @param check_num
 * @param pad_char
 * @return
 */
char *pad_string_ret (uint32_t hex_num,
					uint32_t check_num,
					const char pad_char)
{
   static char pad_string[11];

	/*
     *                      1
     * 0 1 2 3 4 5  6 7 8 9 0
     * 0 x 8 0 0 0  0 0 0 0 \0
     */
	memset(pad_string, pad_char, sizeof(pad_string));
	pad_string[sizeof(pad_string)-1] = '\0';

    if (hex_num != check_num)
    {
    	sprintf(pad_string, "0x%08X", hex_num);
    }

    return (char *)(pad_string);
}

int main (void)
{
  uint32_t hexnum = 0x80000000;
  uint32_t hexnum2 = 0xA0500000;
  char buffer[11];
  char first[11];
  char second[11];

  hexnum = 0x12345678;

  printf("+----------+\n");
  pad_string(hexnum, 0x0, 11, ' ', buffer);
  printf("|%10s|\n", buffer);
  printf("+----------+\n");

  hexnum = 0x00000000;

  pad_string(hexnum, 0x0, 11, '+', buffer);
  printf("|%10s|\n", buffer);
  printf("+----------+\n");

  printf("test1 %10s\n", pad_string_ret(hexnum,0x0,'['));
  hexnum = 0x000;

  printf("test2 %10s %10s\n",
		  pad_string_ret(hexnum,0x0,'-'),
		  pad_string_ret(hexnum2,0x0,'-')
		  );

  strcpy(first, pad_string_ret(hexnum, 0x0,'&'));
  strcpy(second,pad_string_ret(hexnum2,0x0,'%'));
  printf("test3 %10s %10s\n",first, second);

  pad_string(hexnum,0x0, sizeof(first),'*',first);
  pad_string(hexnum2,0x0, sizeof(second),'>',second);
  printf("test3 %10s %10s\n",first, second);
  exit(1);
}
