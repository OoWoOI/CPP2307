/*************************************************************************
	> File Name: 07.myprintf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 08:27:35 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <inttypes.h>

int myprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int char_count = 0; // 记录写入的字符数量

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = va_arg(args, int);
                    putchar(c);
                    char_count++;
                    break;
                }
                case 'd': {
                    int d = va_arg(args, int);
                    if (d == INT32_MIN) {
                        putchar('-');
                        putchar('2');
                        d = 147483648; 
                        char_count += 2;
                    } else if (d < 0) {
                        putchar('-');
                        d = -d;
                        char_count++;
                    }
                    int divisor = 1;
                    while (d / divisor >= 10)
                        divisor *= 10;
                    while (divisor > 0) {
                        putchar(d / divisor + '0');
                        d %= divisor;
                        divisor /= 10;
                        char_count++;
                    }
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                        char_count++;
                    }
                    break;
                }
                case 'l': {
                    format++;
                    switch (*format) {
                        case 'l':
                            format++;
                            if (*format == 'd') {
                                long long ll = va_arg(args, long long);
                                if (ll == LLONG_MIN) {
                                    putchar('-');
                                    putchar('9');
                                    ll = 223372036854775808LL; 
                                    char_count += 2;
                                } else if (ll < 0) {
                                    putchar('-');
                                    ll = -ll;
                                    char_count++;
                                }
                                unsigned long long divisor = 1;
                                while (ll / divisor >= 10)
                                    divisor *= 10;
                                while (divisor > 0) {
                                    putchar(ll / divisor + '0');
                                    ll %= divisor;
                                    divisor /= 10;
                                    char_count++;
                                }
                            }
                            break;
                        case 'f': {
                            double lf = va_arg(args, double);
                            int int_part = (int)lf;
                            int fract_part = (int)((lf - int_part) * 1000000); 
                            if (lf < 0) {
                                putchar('-');
                                lf = -lf;
                                char_count++;
                            }
                            int divisor = 1;
                            while (int_part / divisor >= 10)
                                divisor *= 10;
                            while (divisor > 0) {
                                putchar(int_part / divisor + '0');
                                int_part %= divisor;
                                divisor /= 10;
                                char_count++;
                            }
                            putchar('.');
                            char_count++;
                            divisor = 100000;
                            while (fract_part / divisor == 0) {
                                putchar('0');
                                divisor /= 10;
                                char_count++;
                            }
                            while (divisor > 0) {
                                putchar(fract_part / divisor + '0');
                                fract_part %= divisor;
                                divisor /= 10;
                                char_count++;
                            }
                            break;
                        }
                    }
                    break;
                }
                default:
                    putchar(*format);
                    char_count++;
            }
        } else {
            putchar(*format);
            char_count++;
        }
        format++;
    }

    va_end(args);
    return char_count;
}

void test_myprintf_v1() {
    long long big_number = 12345678901234LL;
    double pi = 3.141592653589793;
    myprintf("hello word !\n"); 
    myprintf("LONG LONG: %lld\n", big_number);
    myprintf("FLOAT: %lf\n", pi);
    myprintf("INT32_MIN: %d\n", INT32_MIN);
    myprintf("INT32_MAX: %d\n", INT32_MAX);
    myprintf("LLONG_MIN: %lld\n", LLONG_MIN);
    myprintf("%c\n", 'A');
    return ;
}

void test_myprintf_v2() {
   
    int ret;
    //打印字符常量
    printf("System:\n");
    ret = printf("hello word\n");
    printf("成功打印：%d\n", ret);
    printf("MySelf:\n");
    ret = myprintf("hello word\n");
    printf("成功打印：%d\n", ret);
    putchar(10);  
    //打印整型变量 
    int a = INT32_MIN, b = INT32_MAX;
    printf("System:\n");
    ret = printf("a = %d, b = %d\n", a, b);
    printf("成功打印：%d\n", ret);
    printf("MySelf:\n");
    ret = myprintf("a = %d, b = %d\n", a, b);
    printf("成功打印：%d\n", ret);
    putchar(10);
    //打印字符
    char c1 = 'a', c2 ='3';
    printf("System:\n");
    ret = printf("c1 = %c, c2 = %c\n", c1, c2);
    printf("成功打印：%d\n", ret);
    printf("MySelf:\n");
    ret = myprintf("c1 = %c, c2 = %c\n", c1, c2);
    printf("成功打印：%d\n", ret);
    putchar(10);
    //打印字符串
    char s1[150] = "adasdc asd as a", s2[150] ="sdadas asda sdaas";
    printf("System:\n");
    ret = printf("s1 = %s, s2 = %s\n", s1, s2);
    printf("成功打印：%d\n", ret);
    printf("MySelf:\n");
    ret = myprintf("s1 = %s, s2 = %s\n", s1, s2);
    printf("成功打印：%d\n", ret);
    return ;
}

int main() {
    test_myprintf_v2();
    return 0;
}

