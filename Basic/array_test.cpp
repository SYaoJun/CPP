#include <iostream>

int main(){
    int **data;
    data = new int*[10]; // A|B|C|D...|int*
    int arr[] = {100,200,300};
    data[0] = arr;
    int brr[] = {400,500,600};
    data[1] = brr;
    std::cout<<data[1][1]<<std::endl;
    return 0;
}