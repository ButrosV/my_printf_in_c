#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

// HELPER FUNCTIONS
int char_count(unsigned char* array);
void copy_string(unsigned char* destination, unsigned char* source);
unsigned char* allocate_char_ptr_memory(int int_num);
int count_digits(size_t input, int num_sys);
int absolute_value(int signed_number);
void to_upper(unsigned char* source);


// CORE FUNCTIONS
int parse_number(size_t input, unsigned char* target_location, int num_sys);
void process_char (char* restrict char_ptr, int* digit_count_ptr, int other_args,  ...);
void process_numeric (char* restrict char_ptr, int input_number, 
int* digit_count_ptr, int numeric_system, int other_args,  ...);
void process_string (char* restrict char_ptr, unsigned char* input_string, int* digit_count_ptr);
void process_pointer (char* restrict char_ptr, size_t input_llint_value, 
int* digit_count_ptr, int numeric_system);
