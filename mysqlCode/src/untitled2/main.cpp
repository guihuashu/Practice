#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
using namespace std;

typedef struct s{
    int i;
    char j;
    float k;
}S;

int main()
{
    S s[5] = {0};
    cout<<sizeof (S)<<endl; // 优化后结构体的大小12
    cout<<sizeof (s)<<endl; // 数组大小: 12x5=60
    cout<<sizeof (s[0])<<endl;
    cout<<sizeof (s[1])<<endl;
    cout<<sizeof (s[2])<<endl;
    return 0;
}
