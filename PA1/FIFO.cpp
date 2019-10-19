#include <iostream>
#include <cstdlib>
#include <cstring>
#define SIZE 105
using namespace std;

class Queue
{
    int key[SIZE];
    int size, first, last, capacity;

public:
    Queue(int s)
    { //[first, last)
        capacity = s;
        size = 0;
        first = 0;
        last = 0;
    }
    int pop()
    {
        int tem = first;
        first == SIZE - 1 ? first = 0 : first++;
        size--;
        return key[tem];
    }
    void push(int i)
    {
        if (size == capacity)
        {
            pop();
        }
        size++;
        key[last] = i;
        last == SIZE - 1 ? last = 0 : last++;
    }
    bool find(int k)
    {
        if (first <= last)
        {
            for (int i = first; i < last; i++)
            {
                if (key[i] == k)
                    return true;
            }
        }
        else
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (i < last || i >= first)
                {
                    if (key[i] == k)
                        return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    int m, n, count = 0, d;
    scanf("%d %d", &n, &m);
    Queue Q(n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &d);
        if (!Q.find(d))
        {
            Q.push(d);
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}