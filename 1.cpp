#include <iostream>
using namespace std;


int main(){
    char * ch = new char[20];
    for(int i=0;i<5;i++)
        ch[i] = 'a'+i;
    printf("%s", ch);
    return 0;
}