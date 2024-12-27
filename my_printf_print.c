/*
    Replicate stdio library's printf() function behaviour - My Printf, Programmer: Butros, 15-Oct-2024.
    my_printf() core project function organizes function calls from other project modules.
    From 'main' cfunction all:
    - define a test case for my_printf() with various input types.
*/

#include "my_printf.h"


int my_printf(char* restrict format, ...)
/** Write a string to the terminal output.
 * 
 * @param format A string to be written as terminal output that may contain 
 *                  specifiers referring to following arguments:
 *                      %c: a single character
 *                      %d: a signed decimal number 
 *                      %o: an unsigned octal number 
 *                      %p: a pointer address as hexadecimal number
 *                      %s: an array of characters (string) 
 *                      %u: an unsigned decimal number
 *                      %x: an unsigned hexadecimal number.
 * @param ... optional list of values that will be converted and written to the
 *                  terminal output in accordance with specifiers provided in 'format'input.
 * @return total characters written to the terminal output.
 */
{
    if (!format) {  // NULL check, alternatively if (format == (void *)0)
        return 0;
    }         
    va_list arg_ptr;
    va_start(arg_ptr, format);
    unsigned char* bufffer_str;
    unsigned char bufffer_char;  
    int buffer_int, num_sys, num_total_digits = 0, no_other_args = 0;
    int* num_total_digits_ptr = &num_total_digits;
    size_t buffer_long_int;
    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'c':
                bufffer_char = va_arg(arg_ptr, int);
                process_char (format++, num_total_digits_ptr, 1, bufffer_char);
                break;
            case 'd':
                buffer_int = va_arg(arg_ptr, int);
                num_sys = 10;
                process_numeric (format++, buffer_int, num_total_digits_ptr, num_sys, 1, '-');
                break;        
            case 'o':
                buffer_int = va_arg(arg_ptr, int);
                num_sys = 8;
                process_numeric (format++, buffer_int, num_total_digits_ptr, num_sys, no_other_args);
                break;
            case 'p':
                buffer_long_int = va_arg(arg_ptr, size_t);
                num_sys = 16;
                process_pointer (format++, buffer_long_int, num_total_digits_ptr, num_sys);
                break;
            case 's':
                bufffer_str = va_arg(arg_ptr, unsigned char*);
                process_string (format++, bufffer_str, num_total_digits_ptr);
                break;
            case 'u': 
                buffer_int = va_arg(arg_ptr, int);
                num_sys = 10;
                process_numeric (format++, buffer_int, num_total_digits_ptr, num_sys, no_other_args);
                break;
            case 'x':
                buffer_int = va_arg(arg_ptr, int);
                num_sys = 16;
                process_numeric (format++, buffer_int, num_total_digits_ptr, num_sys, 1, 'U');
                break;
            default:
                format--;
                process_char (format++, num_total_digits_ptr, no_other_args);
                break;
            }
        }    
        else {
            process_char (format++, num_total_digits_ptr, no_other_args);
        }
    }
    va_end(arg_ptr);
    return num_total_digits;
}


int main()
{
    
    void* test_string = malloc(1 * sizeof(char));

    char* null_string = 0;

    char* string = 
    
    "\
    string: %s,\
    normal string: %s,\
    char: %c, \
    unsigned integer wrong input: %u\
    unsigned integer good input: %u\
    signed integer: %d\
    hex: %x\
    octal: %o\
    pointer: %p\
    ";

    my_printf(string, 
    null_string,
     " EXTRA ",
    'X',
    -13,
    13,
    -666,
    92,
    11,
    test_string
    );

    printf("\nbehaviour of printf with signed int:\
    null string: %s\
    normal string: %s\
    unsigned integer wrong input: %u\
    unsigned integer good input: %u\
    general (negative): %d\
    hex: %x\
    octal: %o\
    pointer: %p\
    \n",
    null_string, " EXTRA ", -13 ,13,-666, 92, 11, test_string);

    free(test_string);
    return 0;
}
