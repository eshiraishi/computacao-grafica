#include <iostream>
#include "misc.h"

using namespace std;

int main()
{
    real a;
    cout << "Digite o valor de a: ";
    cin >> a;
    auto b{globalTwo * pot2(a)};
    cout << "O valor de 2*a^2==" << b << "\n" << endl;
    return 0;
}
