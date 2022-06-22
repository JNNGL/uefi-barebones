#ifndef KERNEL_INTERNAL_STRING_H
#define KERNEL_INTERNAL_STRING_H

const char* int_to_str_ex(int n, char* str, int radix);
const char* long_to_str_ex(long long n, char* str, int radix);
const char* int_to_str(int n, int radix);
const char* long_to_str(long long n, int radix);

int str_to_int(char* str, int radix);
long str_to_long(char* str, int radix);
long long str_to_llong(char* str, int radix);

#endif