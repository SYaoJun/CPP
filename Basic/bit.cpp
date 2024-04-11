#include <stdlib.h>
#include <stdio.h>

/*
这个函数的作用是找到一个数字向上最接近的2的幂次。
*/
static uint32_t roundup_power_of_two(uint32_t val)
{
    // 10010 如果本身是10000，那么就是先变为01111 
    // 1. 其中val--是将从右到左第一个1置为0，这样做是为了方便做右移操作。10001
    // 2. 第一次右移一位，最高位和次高位的1肯定都是1，11000
    // 3. 第二次右移两位，此时因为最高位和次高位都是1，再右移两位，则总共有4位1了，即11110
    // 4. 最后第五次右移，可以将前16位和后16位都变为1
	val--;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	val++;
	return val;
}
int main(){
    printf("res = %d\n", roundup_power_of_two(100));
    printf("res = %d\n", roundup_power_of_two(3));
    printf("res = %d\n", roundup_power_of_two(12));
    printf("res = %d\n", roundup_power_of_two(55));
    printf("res = %d\n", roundup_power_of_two(0));
    return 0;
}