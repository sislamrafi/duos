#include "../../kern/include/softfp.h"

//-10.56
double aaaa = 0.0;
uint64_t cnv_check0 = 0;
uint32_t cnv_check1 = 0;
double dchk = 0.5f;
    
DoubleExpand __dexpand(double n, __D2FLAGS d2flags)
{
    DoubleExpand dex = {0, 0, 0};
    union d2ul_t val;
    val.d = n;

    // double size is 8 byte here
    if (sizeof(double) != 8)
        return dex;

    if (d2flags & D2WITH_SIGN)
    {
        // get the sign bit
        int8_t sign = ((val.ul >> 63) & 0b1);
        // derive sign from sign bit
        sign = sign ? -1 : 1;
        dex.sign = sign;
    }

    // get 11 bit exponent
    int16_t exponent = (val.ul >> 52) & ~(1 << 11);

    // get 52 bit mantisa
    uint64_t mantisa = (val.ul & ~((uint64_t)0xFFF << 52));
    // set mantisa 52th bit to 1's
    mantisa |= (uint64_t)0b1 << 52;

    // get left right shift amount of mantisa
    int16_t shift_amount = exponent - 1023;

    if (d2flags & D2WITH_IPART)
    {
        // get int part
        dex.ipart = (uint32_t)(mantisa >> (52 - shift_amount));
    }

    if (d2flags & D2WITH_FPART)
    {
        // get floating part
        uint64_t temp_fpart = (mantisa << (12 + shift_amount));
        for (int i = 0; i < DOUBLE_FPART_CONVERTER_PRECISION; i++)
        {
            if ((temp_fpart >> (63 - i)) & 0b1)
            {
                dex.fpart += (LARGEST_FPART_VALUE_POSSIBLE >> i);
            }
        }
    }

    return dex;
}

int32_t __aeabi_d2iz(double n)
{
    DoubleExpand dex = __dexpand(n,D2WITH_IPART|D2WITH_SIGN);
    return (int32_t)dex.ipart * (int32_t)dex.sign;
}

int __aeabi_d2i(double n)
{
    DoubleExpand dex = __dexpand(n,D2WITH_IPART|D2WITH_SIGN);
    return (int)dex.ipart * (int32_t)dex.sign;
}

double __aeabi_f2d(float n)
{
    union d2ul_t val_d;
    union f2u_t val_f;
    val_d.d = 0;
    val_f.f = n;

    // set sign bit
    val_d.ul = (uint64_t)(val_f.u >> 31) << 63;
    // set mantisa bits
    val_d.ul |= (uint64_t)(val_f.u & ~((uint32_t)0x1FF << 23)) << 29;

    // get 8 bit exponent
    int16_t exponent = (val_f.u >> 23) & ~(1 << 8);
    // get left right shift amount of mantisa
    int16_t shift_amount = exponent - 127;
    // convert exponent to 11 bit
    exponent = shift_amount + 1023;

    val_d.ul |= (uint64_t)((uint16_t)0x7FF & (uint16_t)exponent) << 52;

    dchk = val_d.d;
    return val_d.d;
}
