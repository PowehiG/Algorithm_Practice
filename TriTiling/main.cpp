#include <iostream>
using namespace std;
int main()
{
    int L;
    int num[35];
    num[0] = 1;
    num[1] = 0;
    num[2] = 3;
    for (int i = 3; i < 35; i++)
    {
        if (i % 2 == 1)
            num[i] = 0;
        else
            num[i] = 4 * num[i - 2] - num[i - 4];
    }
    while(cin >> L && L != -1)
    {
        cout << num[L] << endl;
    }
    return 0;
}
