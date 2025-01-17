# ft_printf
School 21 (42) project. Implementation libc's printf function.

More info:
* [`Subject`](https://github.com/rgalyeon/ft_printf/blob/master/ft_printf.en.pdf) 
* [`About codestyle`](https://github.com/rgalyeon/ft_printf/blob/master/norme.en.pdf)
* [`Examples`](#examples)

## Format Specifiers

A format specifier follows this prototype: `%[flags][width][.precision][length]type`
The following format specifiers are supported:

### Supported Types

| Type   | Output |
|--------|--------|
| d or i | Signed decimal integer |
| u      | Unsigned decimal integer	|
| o      | Unsigned octal |
| x      | Unsigned hexadecimal integer (lowercase) |
| X      | Unsigned hexadecimal integer (uppercase) |
| f      | Decimal floating point |
| c      | Single character |
| s      | String of characters |
| p      | Pointer address |
| b      | Binary representation of integer (Start print at most significant bit) |
| B      | Binary representation of integer (Print all bits) |
| r      | String of characters (Print non-printable characters) |
| n      | None (The number of characters written so far is stored into the integer indicated by the int * (or variant)|
| %      | A % followed by another % character will write a single % |

### Supported Flags

| Flags | Description |
|-------|-------------|
| '-'        | A negative field width flag; the converted value is to be left adjusted on the field boundary. The converted value is padded on the right with blanks, rather than on the left with blanks or zeros.  A - overrides a 0 if both are given. Right justification is the default. |
| '+'        | A sign must always be placed before a number produced by a signed conversion.  A + overrides a space if both are used. |
|' ' (space) | A blank should be left before a positive number produced by a signed conversion (__d__, __f__, or __i__). |
| '#'     | The value should be converted to an ''alternate form''. For __c__, __d__, __i__, __p__, __s__, __r__, __n__ and __u__ conversions, this option has no effect.  For __o__ conversions, the precision of the number is increased to force the first character of the output string to a zero. For __x__ and __X__ conversions, a non-zero result has the string '0x' (or '0X' for __X__ conversions) prepended to it. For __f__ conversion, the result will always contain a decimal point, even if no digits follow it (normally, a decimal point appears in the results of those conversions only if a digit follows). For __b__ and __B__ conversions, will be placed one space between each byte. |
| '0'     | Zero padding. For all conversions, the converted value is padded on the left with zeros rather than blanks.  If a precision is given with a numeric conversion (__d__, __i__, __o__, __u__, __i__, __x__, and __X__), the 0 flag is ignored. |

### Supported Width

| Width    | Description |
|----------|-------------|
| (number) | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger. |
| *        | The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. |

### Supported Precision

| Precision	| Description |
|-----------|-------------|
| .number   | For integer specifiers (__d__, __i__, __o__, __u__, __x__, __X__): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For __f__ specifier: this is the number of digits to be printed after the decimal point. By default, this is 6. For __s__: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. If the period is specified without an explicit value for precision, 0 is assumed. |
| .*        | The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. |


### Supported Length

The length sub-specifier modifies the length of the data type.

| Modifier | d i  | u o x X b B |
|----------|------|---------|
| hh       | signed char | unsigned char |
| h        | short | unsigned short |
| l        | long | unsigned long |
| ll       | long long | unsigned long long |

| Modifier | f |
|----------|---|
|l         |double|
|L         |long double |

### Return Value

Upon successful return, `ft_printf()` return the number of characters written, _excluding_ the terminating null character used to end the string. If any error is encountered, `-1` is returned.

### Examples

#### Standard specifiers (diouxXspcf)
```C
#include "ft_printf.h"

int main()
{
    ft_printf("1. Print int (%%d): %d\n", 42);
    ft_printf("2. Print uint (%%u): %10u\n", -42);
    ft_printf("3. Print unsigned octal (%%o): %o\n", 42);
    ft_printf("4. Print unsigned hex (%%x): %#x\n", 42);
    ft_printf("5. Print unsigned hex (%%X): %#X\n", 42);
    ft_printf("6. Print char (%%c): %c\n", 97);
    ft_printf("7. Print string (%%s): %s\n", "Hello, world!");
    ft_printf("8. Print pointer address (%%p): %p\n", NULL);
    ft_printf("9. Print float (%%f): %.30f\n", 0.3);
    return (0);
}
```

Output:
```
$> 1. Print int (%d): 42
$> 2. Print uint (%u): 4294967254
$> 3. Print unsigned octal (%o): 52
$> 4. Print unsigned hex (%x): 0x2a
$> 5. Print unsigned hex (%X): 0X2A
$> 6. Print char (%c): a
$> 7. Print string (%s): Hello, world!
$> 8. Print pointer address (%p): 0x0
$> 9. Print float (%f): 0.299999999999999988897769753748
```
#### Bonus specifiers (bBr)

```C
#include "ft_printf.h"

int main()
{
    ft_printf("1. Print binary (%%b): %b\n", 2142);
    ft_printf("2. Print binary (%%#b): %#b\n", 2142);
    ft_printf("3. Print binary (%%B): %B\n", 101);
    ft_printf("4. Print binary (%%#B): %#B\n", 101);
    ft_printf("5. Print string with non-printable chars (%%r): %r\n", "\t \b \n \r");
    return (0);
}
```
Output:

```
$> 1. Print binary (%b): 100001011110
$> 2. Print binary (%#b): 1000 01011110
$> 3. Print binary (%B): 00000000000000000000000001100101
$> 4. Print binary (%#B): 00000000 00000000 00000000 01100101
$> 5. Print string with non-printable chars (%r): ^9 ^8 ^10 ^13
```

### Feedback
If you find a `bug/error/typo` please contact me:
* [LinkedIn](https://www.linkedin.com/in/dmitry-filin/)
* [ВКонтакте](https://vk.com/rgalyeon)
