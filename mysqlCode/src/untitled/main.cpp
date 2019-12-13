#include <iostream>

using namespace std;

#define ITOC(a) #a
#define CC(a,b) (a##b)
int main()
{
    cout << "Hello World!" << endl;
    int i= 2;
    printf(ITOC(i));
    printf("\n");
    printf(CC(2,"bb"));
    return 0;

}
