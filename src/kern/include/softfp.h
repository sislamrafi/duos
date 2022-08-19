#ifndef KERN_SOFTFP_H
#define KERN_SOFTFP_H

#include <stdint.h>

#define DOUBLE_FPART_CONVERTER_PRECISION 32
#define LARGEST_FPART_VALUE_POSSIBLE (uint32_t)0x1DCD6500

enum __d_converter_flag_t{
    D2WITH_SIGN = 0b1,
    D2WITH_IPART = 0b10,
    D2WITH_FPART =0b100,
    D2WITH_ALL = 0b111
};

typedef enum __d_converter_flag_t __D2FLAGS;

union d2ul_t
{
    uint64_t ul;
    double d;
};

union f2u_t
{
    uint32_t u;
    float f;
};

typedef struct double_expand_type
{
    int8_t sign;
    uint32_t ipart;
    uint32_t fpart;
}DoubleExpand;


extern int32_t __aeabi_d2iz(double);
extern int __aeabi_d2i(double n);
extern double __aeabi_f2d(float);

extern DoubleExpand __dexpand(double,__D2FLAGS);

#endif