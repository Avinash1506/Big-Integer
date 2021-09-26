#include <iostream>
#include "bigInt.h"
using namespace std;

int main()
{
    BigI x,y,z;
    int t;
    cin>>t;
    while(t--){
            cin>>x;
            cin>>y;
            BigI z=x+y;
            cout<<z<<"\n";
    }
    return 0;
}
