#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#define MAXN 17000000
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
    void clean(int n=MAXN){
        memset(M, 0, (n+7)/8);
    }
};

int l;
Bitmap bitmap1, bitmap2;

void bi_print(int num, int wid){
    wid--;
    for(;wid>=0;wid--){
        printf("%d", getbit(num, wid));
    }
    printf("\n");
}

void scan(int wid){
    bitmap2.clean(1<<wid);
    int t = 0, cnt = 0;
    for(int j=0;j<wid;j++){
        if(bitmap1.test(j)){
            t |= (1 << (wid - j - 1));
        }
    }
    cnt++;
    bitmap2.set(t);
    for(int i=1;i<=l-wid;i++){
        t <<= 1;
        t &= ~(1 << wid);
        t += bitmap1.test(i + wid - 1);
        if(!bitmap2.test(t)){
            bitmap2.set(t);
            cnt++;
        }
        if(cnt >= (1 << wid)){
            return;
        }
    }
}

inline char nc(){
    static const int n = 1024;
    static char buf[n], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf)+fread(buf, 1, n, stdin), p1 == p2) ? EOF : *p1++;
}

int main(){
    char ch;
    l = 0;
    do{
        ch = nc();
        if(ch == '1') bitmap1.set(l);
        l++;
    }while(ch != '\n');
    l--;
    for(int wid=1;wid <= 24;wid++){
        scan(wid);
        for(int num = 0;num < (1 << wid);num++){
            if(!bitmap2.test(num)){
                bi_print(num, wid);
                return 0;
            }
        }
    }
    return 0;
}