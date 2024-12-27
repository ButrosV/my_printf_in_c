/*
    Business functionality functions for My Printf, Programmer: Butros, Nov-2024.
    Function list:
        int parse_number(size_t input, unsigned char* target_location, int num_sys);
        void process_char (char* restrict char_ptr, int* digit_count_ptr, int other_args,  ...);
        void process_numeric (char* restrict char_ptr, int input_number, 
        int* digit_count_ptr, int numeric_system, int other_args,  ...);
        void process_string (char* restrict char_ptr, unsigned char* input_string, int* digit_count_ptr);
        void process_pointer (char* restrict char_ptr, size_t input_llint_value, 
        int* digit_count_ptr, int numeric_system);
*/

#include "my_printf.h"

const char* null_message = "(null)";


int parse_number(size_t input, unsigned char* target_location, int num_sys)
/**
 * 1) Parse input number into string representing decimal or octal value, 
 * 2) store the string into provided pointer location
 * 3) count input decimal digits
 * @param input_decimal input decimal number
 * @param target_location char pointer where to store coverted integer
 * @param num_sys numeric system (decimal: 10, octal: 8)
 * @return integer value of 'input_decimal' digit count
 */
{
    size_t temp_num = input;
    int digit;
    int array_len = count_digits(temp_num, num_sys);
    unsigned char* rev_digits = allocate_char_ptr_memory(array_len);
    unsigned char* rev_digits_start = rev_digits;
    if (temp_num == 0) {
        *rev_digits = '0';
        rev_digits++;
    }  
    while (temp_num > 0) {
        digit = temp_num % num_sys;
        temp_num = (temp_num - digit) / num_sys;
        if (digit < 10) {
            *rev_digits = digit + '0';
        }
        else {
            *rev_digits = digit + 'a' - 10;
        }
        rev_digits++;
    }
    *rev_digits = '\0';
    while (rev_digits != rev_digits_start) {
        rev_digits--;        
        *target_location = *rev_digits;
        target_location++;
    }
    *target_location = '\0';
    free(rev_digits);
    return array_len;
}


void process_char (char* restrict char_ptr, int* digit_count_ptr, int other_args,  ...)
{
/**
 * write a single character to the terminal output 
 * 1) check if other arguments are present
 * 2.1) write to output character from input restrict 'char_ptr' value if no  other arguments are present
 * 2.2) write to output character from optional argument if  other arguments are present
 * 3) Update value of 'digit_count_ptr' for each character written (1)
 * @param char_ptr pointer to a current character written by my_printf function
 * @param digit_count_ptr pointer to a value of current written digit count
 * @param other_args indicates presence of optional arguments, if other_args > 0
 */
    va_list arg_ptr;
    unsigned char bufffer_char;
    va_start(arg_ptr, other_args);
    if (other_args > 0) {
        other_args++;
        bufffer_char = va_arg(arg_ptr, int);
    }
    else {
        bufffer_char = *char_ptr;
    }
    write(1, &bufffer_char, sizeof(char));    
    *digit_count_ptr+=1;
    va_end(arg_ptr);
    return;
}


void process_numeric (char* restrict char_ptr, int input_number, 
int* digit_count_ptr, int numeric_system, int other_args,  ...)
{
/**
 * write a number to the terminal output and move current 
 *                  my_printf function pointer to the next position
 * @param char_ptr pointer to a current character written by my_printf function
 * @param input_number a number that is converted to string output
 * @param digit_count_ptr pointer to a value of current written digit count
 * @param numeric_system numeric system for number output: 
 *                               8 for octal,
 *                               10 for decimal,
 *                               16 for hexadecimal
 * @param other_args indicates presence of optional arguments, 
 *              if other_args > 0 are followed by:
 *                 '-': if input number is negative, '-' is added to number output
 *                  'U': string character values are converted to upper case
 */
    va_list arg_ptr;
    unsigned char buffer_char;
    unsigned char* buffer_str;
    int num_specifier_digits;
    va_start(arg_ptr, other_args);
    if (other_args > 0 && input_number < 0) {
        buffer_char = va_arg(arg_ptr, int);
        input_number = absolute_value(input_number);
        write(1, &buffer_char, 1);
        *digit_count_ptr += 1;
    }
    buffer_str = allocate_char_ptr_memory(count_digits(input_number, numeric_system) + 3);
    num_specifier_digits = parse_number(input_number, buffer_str, numeric_system);
    if (other_args > 0 && va_arg(arg_ptr, int) == 'U') {
        to_upper(buffer_str);        
    }
    write(1, buffer_str, num_specifier_digits);
    free(buffer_str); 
    *digit_count_ptr += num_specifier_digits;
    va_end(arg_ptr);
    char_ptr++;
    return;
    }


void process_string (char* restrict char_ptr, unsigned char* input_string, int* digit_count_ptr)
/**
 * 1.1) write an input string to the terminal output or
 * 1.2) write corresponding message to the terminal output if input string is NULL
 * 2) and move current my_printf function pointer to the next position
 * @param char_ptr pointer to a current character written by my_printf function
 * @param input_string a pointer to string to be written as terminal output
 * @param digit_count_ptr pointer to a value of current written digit count
 */
{
    unsigned char* buffer_str, * temp_string;
    int num_specifier_digits;
    if (input_string == 0) {
        num_specifier_digits = char_count((unsigned char* ) null_message);  // cast signed constant to signed char
        buffer_str = allocate_char_ptr_memory(num_specifier_digits);
        temp_string = (unsigned char*) null_message;  // cast signed constant to signed char
    }
    else {
        num_specifier_digits = char_count(input_string);
        buffer_str = allocate_char_ptr_memory(num_specifier_digits);
        temp_string = input_string;
    }
    copy_string(buffer_str, temp_string);
    write(1, buffer_str, num_specifier_digits);
    free(buffer_str);
    *digit_count_ptr += num_specifier_digits;
    char_ptr++;
    return;
}


void process_pointer (char* restrict char_ptr, size_t input_llint_value, 
int* digit_count_ptr, int numeric_system)
/**
 * write a pointer address to the terminal output and move current 
 *                  my_printf function pointer to the next position
 * @param char_ptr pointer to a current character written by my_printf function
 * @param input_number a number that is converted to string output
 * @param digit_count_ptr pointer to a value of current written digit count
 * @param numeric_system numeric system for number output: 
 *                               8 for octal,
 *                               10 for decimal,
 *                               16 for hexadecimal
 * @param other_args indicates presence of optional arguments, 
 *              if other_args > 0 are followed by:
 *                 '-': if input number is negative, '-' is added to number output
 *                  'U': string character values are converted to upper case
 */
{
    unsigned char* buffer_str;
    int num_specifier_digits;
    buffer_str = allocate_char_ptr_memory(count_digits(input_llint_value, numeric_system));
    num_specifier_digits = parse_number(input_llint_value, buffer_str, numeric_system);
    write(1, "0x", sizeof(char) * 2);
    write(1, buffer_str, num_specifier_digits);
    free(buffer_str);
    *digit_count_ptr = *digit_count_ptr + num_specifier_digits + 2;
    char_ptr++;
    return;
    }
