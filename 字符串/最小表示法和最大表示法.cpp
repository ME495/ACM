/*
ѭ���ַ�������С��ʾ���������������������
����һ���ַ���S����S��ѭ����ͬ���ַ���S�����ֵ�����С��һ����
*/

//�����ַ���S'������ĸ��id
int get_min(char s[],int len)
{
    int i = 0, j = 1, l;
    while(i < len && j < len)
    {
        for(l = 0; l < len; l++)
            if(s[(i + l) % len] != s[(j + l) % len]) break;
        if(l >= len) break;
        if(s[(i + l) % len] > s[(j + l) % len])
        {
            if(i + l + 1 > j) i = i + l + 1;
            else i = j + 1;
        }
        else if(j + l + 1 > i) j = j + l + 1;
        else j = i + 1;
    }
    return i < j ? i : j;
}

//�����ַ���S'������ĸ��id
int get_max(char s[],int len)
{
    int i = 0, j = 1, k = 0;
    while(i < len && j < len && k < len)
    {
        int t = s[(i+k)%len]-s[(j+k)%len];
        if(!t) k++;
        else
        {
            if(t > 0)
            {
                if(j+k+1 > i) j = j+k+1;
                else j = i+1;
            }
            else if(i+k+1 > j) i = i+k+1;
            else i = j+1;
            k = 0;
        }
    }
    return i < j ? i : j;
}
