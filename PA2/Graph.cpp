#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;


int main()
{
    //ios::sync_with_stdio(false);
    auto a = ((unsigned int) -1);
    cout<<hex<<((unsigned int) -1)<<endl;
    cout<<hex<<a / ((1<<(1<<2))+1)<<endl;
    return 0;
}