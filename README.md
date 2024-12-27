# My Printf imitation
***

## Goal of the project
Replicate `stdio` library's `printf()` function behavior.

**Project Functionality Description:**

The `my_printf()` function outputs formatted text to `stdout` based on a provided format string. The format string can contain ordinary characters (copied as-is to the output) and conversion specifications, which specify how subsequent arguments should be formatted.

Each conversion specification starts with a percent sign (`%`) and is followed by a character that defines the type of argument to be processed:

- **d, o, u, x**: Convert an `int` (or appropriate variant) to signed decimal (`d`), unsigned octal (`o`), unsigned decimal (`u`), or unsigned hexadecimal (`x`).
- **c**: Convert an `int` to an unsigned `char` and print the corresponding character.
- **s**: Convert a `char *` to a string, printing characters until the null terminator (`\0`).
- **p**: Convert a `void *` pointer to a hexadecimal representation.

Arguments are fetched based on the conversion specifications, and type promotion may occur where necessary.

- No LLMs used apart from generating the game description above:)

## Pseudo logic
Define a set of helper and core business functions that produce necessary inputs for `my_printf()` in the main module. 
- **Helper functions** deal wih:
    - Counting the characters and digits;
    - Own implementation of string copy functionality;
    - Memory allocation for pointers;
    - Own implementation absolute value;
    - Own implementation of character conversion to upper case;

- **Business functions** deal with:
    - Converting input number into specified numerical system and storing it as a string array;
    - Parsing characters and writing to terminal for `my_printf()` `%c` specifier;          
    - Parsing input numbers and writing to terminal for `my_printf()` `%d`, `%o`, `%u` and `%x` specifiers;
    - Parsing pointer input and writing it to terminal for `my_printf()` `%p` specifier;
    - Parsing string input and writing it terminal for `my_printf()` `%s` specifier;

- **Core function**:
    - `my_printf()` - utilize C language variadic functionality and switch statement to organize **Business function** calls and write output to the terminal in accordance with user input and specifiers;

- ***Optional local testing function**:
    - `main()` - uncomment/comment out or edit according to testing requirements.

**Makefile**: to compile relevant files into a target `./my_printf` program.

## Installation
**Dependencies**:
- GCC compiler
- make support for GNU

Download/pull files:
```
.
├── Makefile
├── README.md
├── my_printf_print.c
├── my_printf.h
├── my_printf_business_print.c
└── my_printf_helpers_print.c
```

- Depending if you use Windows or Linux systems, comment/uncomment relevant cleanup calls in Makefile (rows 18 or 19 and 23 or 24)
- From folder containing all above files run following terminal command to compile program:
 ```
make
```
to remove .o and .exe files after the use of program, run from the terminal
 ```
make fclean
```

## Usage
Run exe file from the terminal:
```
./my_printf
```
Also you may:
1) uncomment `main()` function in my_printf.c file,
2) provide inputs for `my_printf()` function within `main()`,
3) compile/make and run.

Alternatively:
- import the module to any of your programs and use as you wish:)

***
### Author
Butros
***