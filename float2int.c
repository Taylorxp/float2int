int getSign(unsigned num)  //获得符号位
{
    int sign = num & (1 << 31);
    return sign == 0 ? 1 : -1;
}

int getExp(unsigned num)  //获得指数部分
{
    int exp = 0;
    for (int i = 23; i < 31; ++i)
        exp |= (num & (1 << i));
    exp = (exp >> 23) - 127;
    return exp;
}

int float2int(float ft)  // float强转为int
{
    unsigned num;
    memcpy(&num, &ft, sizeof(float));  //将float数据完整地拷贝到unsigned中

    int exp = getExp(num);  //获得float存储结构的指数部分
    if (exp < 0)            //如果指数小于0的话，实际值肯定是0.***,故而强转之后就为0
    {
        return 0;
    }
    else
    {
        int res = num & ((1 << 23) - 1);  //保留mantissa 注意运算符的优先级
        res |= 1 << 23;                   //将小数点前的1补上
        res >>= (23 - exp);               //整数部分右移到合适位置
        return res * getSign(num);
    }
}