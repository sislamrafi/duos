#include "../include/kstdio.h"
/**
 * first argument define the type of string to kprintf and kscanf,
 * %c for charater
 * %s for string,
 * %d for integer
 * %x hexadecimal
 * %f for floating point number
 */

void stdout_ch(char ch)
{
    UART_SendChar(USART2, ch);
}

void stdout_string(char *ch)
{
    _USART_WRITE(USART2, ch);
}

uint8_t stdin_string(char *buff, uint16_t size){
    return _USART_READ(USART2,buff,size);
}

int strlen(char *str){
    int size_tt = 0;
    for(size_tt; str[size_tt]!=0; size_tt++);
    return size_tt;
}

char *itoa(int32_t val, int base)
{

    static char buf[32] = {0};

    uint8_t sign = val >= 0 ? 0 : 1;
    val = val >= 0 ? val : val * -1;

    int i = 30;

    if (val == 0)
        buf[i--] = '0';

    for (; val && i; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    if (sign)
        buf[i--] = '-';

    return &buf[i + 1];
}

char *ftoa(double n, uint8_t base, int afterpoint)
{
    static char buf[32] = {0};

    DoubleExpand dex = __dexpand(n,D2WITH_ALL);

    // Extract integer part
    int32_t ipart = (int32_t)dex.ipart * (int32_t)dex.sign;
    int32_t fpart = (int32_t)dex.fpart;

    char *icpart = itoa(ipart, base);
    int i = 0;
    for (int j = 0; icpart[j] != 0; j++, i++)
        buf[i] = icpart[j];
    buf[i++] = '.';

    fpart = fpart<0?fpart*-1:fpart;
    char *fcpart = itoa(fpart<0?fpart*-1:fpart, base);
    int len = strlen(fcpart);
    //calculate padding
    int padding = 9-len;
    for (int j = padding; padding>0; padding--, i++)
        buf[i] = '0';

    for (int j = 0; fcpart[j] != 0; j++, i++)
        buf[i] = fcpart[j];
    buf[i] = 0;

    return &buf;
}

int atoi(const char *str, int8_t base_t)
{
    int sign = 1, base = 0, i = 0;

    // if whitespaces then ignore.
    while (str[i] == ' ')
    {
        i++;
    }

    // sign of number
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }

    // checking for valid input
    while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))
    {
        // handling overflow test case
        // if (base > INT_MAX / 10
        //     || (base == INT_MAX / 10
        //     && str[i] - '0' > 7))
        // {
        //     if (sign == 1)
        //         return INT_MAX;
        //     else
        //         return INT_MIN;
        // }
        int num = ('F' - str[i] < 6) ? (str[i++] - 'A') + 10 : (str[i++] - '0');
        // printf("%d\n",num);
        base = (int)base_t * base + num;
    }
    return base * sign;
}

float atof(char *str,int8_t base_t){
    int i = 0;
    char* dotch;
    for(i;str[i]!=0;i++){
        if(str[i]=='.'){
            str[i]='\0';
            dotch = &str[i];
            break;
        }
    }

    int fpart = atoi(dotch+1,base_t);
    int size_tt = strlen(dotch+1);

    float n = (float)fpart;
    for(size_tt; size_tt>0; size_tt--){
        n/=base_t;
    }

    n+=(float)atoi(str,base_t);

    *dotch = '.';

    return n;
}

void *memset(void *b, char c, int len)
{
    char *b_char = (char *)b;

    if (b == NULL) return NULL;

    while(*b_char && len > 0)
    {
        *b_char = c;
        b_char++;
        len--;
    }

    return b; //as this pointer has not changed
}

void kprintf(uint8_t *format, ...)
{
    va_list arguments;
    va_start(arguments, format);


    for (int k = 0; format[k] != 0; k++)
    {
        if (format[k] != '%')
        {
            stdout_ch(format[k]);
        }
        else
        {
            char code = format[++k];
            switch (code)
            {
            case 'd':
                stdout_string(itoa(va_arg(arguments, int), 10));
                break;
            case 'x':
                stdout_string(itoa(va_arg(arguments, int), 16));
                break;
            case 'c':
                stdout_ch((char)va_arg(arguments, int));
                break;
            case 's':
                stdout_string(va_arg(arguments, char *));
                break;
            case 'f':
                stdout_string(ftoa(va_arg(arguments, double), 10, 6));
                break;
            default:
                break;
            }
        }
    }

    va_end(arguments);
}

void kscanf(uint8_t *format, ...)
{
    va_list arguments;
    va_start(arguments, format);

    const size_buff_scanf = 100;
    char buff[size_buff_scanf];

    volatile uint8_t cur_read_size = 0;

    for (int k = 0; format[k] != 0; k++)
    {
        if (format[k] != '%')
        {
            continue;
        }
        else
        {
            char code = format[++k];
            switch (code)
            {
            case 'd':
                cur_read_size = stdin_string(buff,size_buff_scanf-1);
                int *ii = va_arg(arguments, int*);
                *ii=atoi(buff,10);
                //kprintf("\nWriting data. bytes:(%s) Size:(%d)",buff,cur_read_size);
                break;
            case 'x':
                cur_read_size = stdin_string(buff,size_buff_scanf-1);
                int *ij = va_arg(arguments, int*);
                *ij=atoi(buff,16);
                break;
            case 'c':
                cur_read_size = stdin_string(buff,3);
                char *ch = va_arg(arguments, char*);
                *ch = buff[0];
                break;
            case 's':
                cur_read_size = 0;
                char *str = va_arg(arguments, char*);
                cur_read_size = stdin_string(str,size_buff_scanf-1);
                break;
            case 'f':
                cur_read_size = stdin_string(buff,size_buff_scanf-1);
                float *ik = va_arg(arguments, uint32_t*);
                *ik=atof(buff,10);
                break;
            default:
                break;
            }
        }
    }

    va_end(arguments);
}
