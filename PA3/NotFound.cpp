#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define MAXN 20000000
#define getbit(x, y) ((x) >> (y) & 1)

class Bitmap{
    private:
    int N;
    char * M;
    public:
    Bitmap(int n=MAXN){
        M = new char[N = (n+7)/8];
        memset(M, 0, N);
    }
    ~Bitmap(){
        delete [] M;
        M = NULL;
    }
    void set(int k){
        M[k>>3] |= (0x80 >> (k & 0x07));
    }
    int test(int k){
        return (M[k>>3] & (0x80 >> (k & 0x07))) ? 1 : 0;
    }
};

int l;
Bitmap bitmap1, bitmap2;
int str[30];

void bi_print(int num, int wid){
    for(int i=0;i<wid;i++){
        printf("%d",str[i]);
    }
    printf("\n");
}

bool check(int num, int wid){
    for(int i=wid-1;i>=0;i--){
        if(getbit(num, i)) str[wid - i - 1] = 1;
        else str[wid - i - 1] = 0;
    }
    bool f;
    for(int i=0;i<=l-wid;i++){
        f = true;
        for(int j=0;j<wid;j++){
            if(str[j] != bitmap1.test(i+j)){
                f = false;
                break;
            }
        }
        if(f){//存在此子串
            return false;
        }
    }
    return true;
}

int main(){
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    char ch;
    l = 0;
    do{
        ch = getchar();
        if(ch == '1') bitmap1.set(l);
        l++;
    }while(ch == '0' || ch == '1');
    l--;
    
    for(int wid=1;wid <= 24;wid++){
        for(int num = 0; num < (1<<wid);num++){
            if(check(num, wid)){
                bi_print(num, wid);
                return 0;
            }
        }
    }
    return 0;
}