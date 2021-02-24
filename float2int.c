int getSign(unsigned num)  //��÷���λ
{
    int sign = num & (1 << 31);
    return sign == 0 ? 1 : -1;
}

int getExp(unsigned num)  //���ָ������
{
    int exp = 0;
    for (int i = 23; i < 31; ++i)
        exp |= (num & (1 << i));
    exp = (exp >> 23) - 127;
    return exp;
}

int float2int(float ft)  // floatǿתΪint
{
    unsigned num;
    memcpy(&num, &ft, sizeof(float));  //��float���������ؿ�����unsigned��

    int exp = getExp(num);  //���float�洢�ṹ��ָ������
    if (exp < 0)            //���ָ��С��0�Ļ���ʵ��ֵ�϶���0.***,�ʶ�ǿת֮���Ϊ0
    {
        return 0;
    }
    else
    {
        int res = num & ((1 << 23) - 1);  //����mantissa ע������������ȼ�
        res |= 1 << 23;                   //��С����ǰ��1����
        res >>= (23 - exp);               //�����������Ƶ�����λ��
        return res * getSign(num);
    }
}