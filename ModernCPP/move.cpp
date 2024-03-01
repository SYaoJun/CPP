#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std;
int cmp(int a, int b){
    return a > b;
}
int main(){
   int n = 0, k = 0;
   scanf("%d%d", &n, &k);
   int arr[10];
   for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
   }

    for(int i = 0; i < n; i++){
        printf("arr=%d\n", arr[i]);
    }
    sort(arr, arr+n);
    for(int i = 0; i < n; i++){
        printf("sorted arr[%d]=%d\n", i, arr[i]);
    }
    printf("%d\n", arr[n-k]);
    return 0;
}