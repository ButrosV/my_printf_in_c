/*
    Helper functions for My Printf, Programmer: Butros, Nov-2024.
    Function list:
        int char_count(unsigned char* array);
        void copy_string(unsigned char* destination, unsigned char* source);
        unsigned char* allocate_char_ptr_memory(int int_num);
        int count_digits(size_t input, int num_sys);
        int absolute_value(int signed_number);
        void to_upper(unsigned char* source);
*/

#include "my_printf.h"


int char_count(unsigned char* array)
/**
 * A helper function to count characters
 * @param array pinter to an array of characters (string)
 * @return int of character count
 */
{
    int count = 0;
    while (array[count] != '\0') {
        count++;
    }
    return count;
}


void copy_string(unsigned char* destination, unsigned char* source)
/**
 * A helper to copy a string
 * @param destination a pointer to destination location, vhere string will be copied
 * @param source a pointer to string that will be copied
 * @return void
 */
{
    unsigned char* temp_dest = destination;
    while (*source) {
        *temp_dest = *source;
        temp_dest++;
        source++;
    }
    return;
}


unsigned char* allocate_char_ptr_memory(int int_num)
/**
 * A helper function to allocate memory for a 1d character pointer array
 * @param int_num expected number of character pointers in array
 * @return pointer (int) array with reserved memory consisting of '0' values
 *      (use free() after end of function lifecycle)
 */
{
    unsigned char* temp_array = calloc(int_num, sizeof(int));
    if (temp_array == NULL) {
        write(1, "String array memory allocation failed.", 50);
    }
    return temp_array;
}


int count_digits(size_t input, int num_sys)
/**
 * A helper function to count digits
 * @param input input number
 * @param num_sys numeric system (decimal = 10, hex = 16, octal = 8)
 * @return integer value of digit count
 */
{
    int digit_count = 0;
    size_t temp_num = input;
    if (temp_num == 0) {
        digit_count++;
    }
    while (temp_num > 0) {
        temp_num = temp_num / num_sys;
        digit_count++;
    }
        
    return digit_count;
}


int absolute_value(int signed_number)
/**
 * A helper function returns absolute value of number
 * @param signed_number input number
 * @return absolute integral value
 */
{
    if (signed_number >= 0) {
        return signed_number;
    }
    else {
        return signed_number * -1;
    }
}


void to_upper(unsigned char* source)
/**
 * A helper function:
 *      Convert lower characters to upper in a string 
 *      containing any ASCII character
 * @param source pointer tp a string containing ASCII characters
 */
{
    while (*source) {
        if (*source >= 'a' && *source <= 'z') {
        *source = *source - 'a' + 'A';
        }
        source++;
    }
}
