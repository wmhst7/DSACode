#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
int m, n, len;
static const int sqn = 800;
char buffer[500010];
class node
{ //块状链表的一个节点
public:
    node *next = nullptr;
    int size = 0; //[0, size)
    char d[(sqn * 2) + 5];
    node()
    {
        size = 0;
        next = nullptr;
        //memset(d, 0, sizeof(d));
    }
    void push_back(char c)
    {
        d[size] = c;
        size++;
    }
};
node *head = nullptr;
void Print();

void check(node *p)
{
    if (p->size >= sqn * 2) //split
    {
        node *q = new node;
        for (int i = sqn; i < p->size; i++)
        {
            q->push_back(p->d[i]);
        }
        q->next = p->next;
        p->next = q;
        p->size = sqn;
    } //merge
    else if (p->size <= sqn / 2 && p->next != nullptr && p->next->size <= sqn / 2)
    {
        node *q = p->next;
        int key = p->size;
        for (int i = 0; i < q->size; i++)
        {
            p->d[key++] = q->d[i];
        }
        p->size = key;
        p->next = q->next;
        //delete q;
    }
}

void remove(int l, int r)
{ //remove: [l, r]
    //cout<<"remove:"<<l<<" "<<r<<endl;
    node *p = head, *q = nullptr;
    int total = p->size, key = 0, count = 0;
    while (total <= l && p->next != nullptr)
    {
        p = p->next;
        total += p->size;
    }
    total -= p->size;
    key = l - total;
    while (count < r - l + 1)
    { //删除中
        if (r - l + 1 - count <= p->size - key)
        { //case 1: 块内操作
            int num = r - l + 1 - count;
            memmove(p->d + key, p->d + key + num, p->size - num);
            count += num;
            p->size -= num;
        } //case 2: 块间操作
        else if (r - l + 1 - count > p->size - key)
        {
            count += p->size - key;
            p->size = key;
            p = p->next;
            key = 0;
        }
    }
    len -= r - l + 1;
    //检查删除空块
    p = head;
    while (p->next != nullptr)
    {
        if (p->next->size == 0)
        {
            q = p->next;
            p->next = q->next;
            //delete q;
        }
        else
        {
            p = p->next;
        }
    }
}

char get(const int pos) //[0, len)
{
    if (pos >= len)
    {
        return (char)0;
    }
    int total = head->size;
    node *p = head;
    while (pos >= total && p->next != nullptr)
    {
        p = p->next;
        total += p->size;
    }
    total -= p->size;
    if (pos - total < 0)
    { //负数key
        return (char)0;
    }
    return p->d[pos - total]; //[0, max), so don't - 1
}

void insert(const char c, const int pos)
{ //插在pos前面,即插入的是新pos位
    if(pos > len) return;
    node *p = head;
    int total = p->size, key = 0;
    while (total <= pos && p->next != nullptr)
    {
        p = p->next;
        total += p->size;
    }
    if(p == nullptr) return;
    total -= p->size;
    key = pos - total; //相对位置
    if(key < p->size){
        memmove(p->d + (key + 1), p->d + key, p->size - key);
    }
    // for (int i = p->size - 1; i >= key; i--)
    // {
    //     p->d[i + 1] = p->d[i];
    // }
    p->size++;
    len++;
    p->d[key] = c;
    check(p);
}

void dele(int l, int r)
{
    while (l >= 0 && r < len) //不同颜色的珠子
    {
        char c = get(l);
        while (l >= 0 && r < len) //扩大化string
        {
            if (c == get(l - 1))
            {
                l--;
                continue;
            }
            if (c == get(r + 1))
            {
                r++;
                continue;
            }
            char cl = get(l - 1);
            if (cl != 0 && cl == get(r + 1))
            {
                if (cl == get(l - 2))
                {
                    l = l - 2;
                    r = r + 1;
                    break;
                }
                else if (cl == get(r + 2))
                {
                    l = l - 1;
                    r = r + 2;
                    break;
                }
            }
            remove(l, r);
            return;
        }
    }
}

void process(int pos, char c)
{
    //Print();
    int l = pos - 1;
    int r = pos;
    if (c == get(l) && c == get(r))
    {
        dele(l, r);
    }
    else if (c == get(l) && c == get(l - 1))
    {
        dele(l - 1, l);
    }
    else if (c == get(r) && c == get(r + 1))
    {
        dele(r, r + 1);
    }
    else
    {
        insert(c, pos);
    }
}

void Print()
{
    //输出结果
    node *p = head;
    while (p != nullptr)
    {
        for (int i = 0; i < p->size; i++)
        {
            printf("%c", p->d[i]);
        }
        //cout << "(size = " << p->size << ")";
        p = p->next;
    }
    printf("\n");
}

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    scanf("%s", buffer);
    len = strlen(buffer);
    scanf("%d", &m);
    node *p = new node;
    head = p;
    for (int i = 0; i < len; i++)
    {
        if (i % sqn == 0 && i != 0)
        {
            p->next = new node;
            p = p->next;
        }
        p->push_back(buffer[i]);
    }
    int pos;
    char c;
    while (m--)
    {
        scanf("%d %c", &pos, &c);
        process(pos, c);
    }
    Print();
    return 0;
}
