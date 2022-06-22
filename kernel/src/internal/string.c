#include "string.h"
#include <stdbool.h>
#include "tty.h"

const char* int_to_str_ex(int num, char* str, int radix) {
    if(!str) return 0;
    int n = num;
    int i = 0;
    bool isneg = false;
    if(n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if(n < 0 && radix == 10) {
        isneg = true;
        n = -n;
    }
    while(n != 0) {
        int rem = n % radix;
        str[i++] = (rem > 9)? (rem - 10) + 'A' : rem + '0';
        n /= radix;
    }
    if(isneg) str[i++] = '-';
    str[i] = '\0';
    int start = 0;
    int end = i - 1;
    while(start < end) {
        char tmp = *(str + start);
        *(str + start) = *(str + end);
        *(str + end) = tmp;
        start++;
        end--;
    }
    return str;
}

const char* long_to_str_ex(long long n, char* str, int radix) {
    if(!str) return 0;
    int i = 0;
    bool isneg = false;
    if(n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if(n < 0 && radix == 10) {
        isneg = true;
        n = -n;
    }
    while(n != 0) {
        int rem = n % radix;
        str[i++] = (rem > 9)? (rem - 10) + 'A' : rem + '0';
        n /= radix;
    }
    if(isneg) str[i++] = '-';
    str[i] = '\0';
    int start = 0;
    int end = i - 1;
    while(start < end) {
        const char tmp = *(str + start);
        *(str + start) = *(str + end);
        *(str + end) = tmp;
        start++;
        end--;
    }
    return str;
}

char global_ntoa_buf[65];

const char* int_to_str(int n, int radix) {
    return int_to_str_ex(n, global_ntoa_buf, radix);
}

const char* long_to_str(long long n, int radix) {
    return long_to_str_ex(n, global_ntoa_buf, radix);
}

int str_to_int(char* str, int radix) {
    if(radix < 2) return 0;
    unsigned char i = 0;
    int res = 0;
    bool isneg = false;
    if(str[i] == '-' && radix == 10) {
        isneg = true;
        i++;
    }
    for(; str[i] != '\0'; ++i) {
        char inc;
        if(str[i] >= 'a') inc = 10 + str[i] - 'a';
        else if(str[i] >= 'A') inc = 10 + str[i] - 'A';
        else inc = str[i] - '0';
        res = res * radix + inc;
    }
    return isneg? -res : res;
}

long str_to_long(char* str, int radix) {
    if(radix < 2) return 0;
    unsigned char i = 0;
    long res = 0;
    bool isneg = false;
    if(str[i] == '-' && radix == 10) {
        isneg = true;
        i++;
    }
    for(; str[i] != '\0'; ++i) {
        char inc;
        if(str[i] >= 'a') inc = 10 + str[i] - 'a';
        else if(str[i] >= 'A') inc = 10 + str[i] - 'A';
        else inc = str[i] - '0';
        res = res * radix + inc;
    }
    return isneg? -res : res;
}

long long str_to_llong(char* str, int radix) {
    if(radix < 2) return 0;
    unsigned char i = 0;
    long long res = 0;
    bool isneg = false;
    if(str[i] == '-' && radix == 10) {
        isneg = true;
        i++;
    }
    for(; str[i] != '\0'; ++i) {
        char inc;
        if(str[i] >= 'a') inc = 10 + str[i] - 'a';
        else if(str[i] >= 'A') inc = 10 + str[i] - 'A';
        else inc = str[i] - '0';
        res = res * radix + inc;
    }
    return isneg? -res : res;
}