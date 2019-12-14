#include "crc32.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#define uint unsigned int
#define uchar unsigned char
using namespace std;
int n;
uint crc_salt;
char salt[5];

/*
base: 19
_map:
null 0 1 2 3 4 5 6 7 8 9  t  s  i  n  g  h  u  a(char)
    30 ...              116                     (ascii)
  0  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18(int)

store password:
x x x x x x(high)
0 1 2 3 4 5(high)
*/

int _map[120];
char _imap[20] = "00123456789tsinghua";
void pre_map(){
    memset(_map, 0, sizeof(_map));
    for(int i='0';i<='9';i++){
        _map[i] = i - '0' + 1;
    }
    _map['t'] = 11;_map['s'] = 12;_map['i'] = 13;_map['n'] = 14;
    _map['g'] = 15;_map['h'] = 16;_map['u'] = 17;_map['a'] = 18;
    _imap[0] = 0;
}

int password2int(const char * str){
    int r = 0;
    for(int i = 0;i < strlen(str);i++){
        r += _map[str[i]] * (pow(19, i));
    }
    return r;
}

bool int2password(char * str, int pw){
    int i = 0;
    while(pw > 0){
        str[i] = _imap[pw - (pw/19) * 19];
        pw /= 19; 
        if(str[i] == 0) return false;
        i++;
    }
    str[i] = '\0';
    return true;
}

//Hash Map Implementation Begin
class HashItem{
public:
    uint key;
    int value;
    HashItem * next = nullptr;
    HashItem(uint k, int v):key(k), value(v){}
};
class HashTable{
//key -> CRC32(uint), value -> password(int)
private:
    int Size = 4000000;//length
    HashItem ** table;
    int hash(uint key){
        return key % Size;
    }
public:
    HashTable(){
        table = new HashItem*[Size];
        for(int i=0;i<Size;i++){
            table[i] = nullptr;
        }
    }
    void put(uint k, int v){
        int h = hash(k);
        if(table[h]){
            HashItem * hp = table[h];
            while(true){//Go Along
                if(hp -> key == k){
                    if(hp -> value != v) hp -> value = -2;//Duplicate
                    break;
                }else if(hp->next == nullptr){
                    hp -> next = new HashItem(k, v);
                    break;
                }else{
                    hp = hp->next;
                }
            }
        }else{
            table[h] = new HashItem(k, v);
        }
    }
    int get(uint k){//-1 : No, -2 : Duplicated, Other : password(int)
        int h = hash(k);
        HashItem * hp = table[h];
        if(hp == nullptr) return -1;
        while(true){
            if(hp -> key == k){
                return hp->value;
            }else if(hp -> next == nullptr){
                return -1;
            }else{
                hp = hp->next;
            }
        }
    }
};
//Hash Map Implementaion End
HashTable hashtable;

//Circle Array 
class CircleArray{
public:
    char M[8];
    int now = 0;
    void push_back(char s){
        now++; now %= 8;
        M[now] = s;
    }
    void print(){
        cout<<"now = "<<now<<endl;
        for(int i = 0;i<8;i++){
            cout<<M[i]<<' ';
        }cout<<endl;
    }
};
CircleArray fpasswords;

void pre_put(){
    //"" -> "aaaaa"
    char str[6];
    int m = password2int("aaaaa");
    //cout<<"m : "<<m<<endl;
    for(int i = 1;i <= m;i++){
        if(int2password(str, i) == false) continue;
        // if(m - i < 100 || i < 100)
        //     cout<<str<<' '<<i<<' '<<password2int(str)<<endl;
        uint crc = crc32(0, (uchar *)str, strlen(str));
        hashtable.put(crc32(crc, (uchar *)salt, strlen(salt)), i);
    }
}

void query(uint password){
    //find
    int result = hashtable.get(password);
    char str[10];
    if(result == -1){
        printf("No\n");
    }else if(result == -2){
        printf("Duplicate\n");
    }else{
        int2password(str, result);
        printf("%s\n", str);
        fpasswords.push_back(str[0]);
    }
}

void weakpassword(){
    char str[10];
    str[8] = '\0';
    int n = fpasswords.now;
    for(int i = 0;i < 8;i++){
        str[i] = fpasswords.M[(n + i + 1) % 8];
    }
    for(int i = 0;i<3;i++){
        if(_map[str[i]]){
            //cout<<"weak: "<<str+i<<endl;
            uint crc = crc32(0, (uchar *)(str + i), 8 - i);
            hashtable.put(crc32(crc, (uchar *)salt, strlen(salt)), password2int(str+i));
        }
    }
}

int main(){
    char buffer[10];
    pre_map();
    scanf("%d", &n);
    scanf("%s", salt);
    pre_put();
    uint password;
    for(int i=0;i<n;i++){
        scanf("%s", buffer);
        password = 0;
        for(int j=0;j<8;j++){
            if(buffer[j] < 60){
                password += (1u << ((7 - j) * 4)) * (buffer[j] - '0');
            }else{
                password += (1u << ((7 - j) * 4)) * (buffer[j] - 'a' + 10);
            }
        }
        //cout<<"password: "<<password<<endl;
        query(password);
        weakpassword();
    }
    cout<<password2int("aaaaaaaa")<<endl;
    return 0;
}