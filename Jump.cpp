#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long
int N;
ll l[1000010], r[1000010], t[1000010], T[1000010], elem[1000010];

struct queue
{
    int _head;
    int _tail;

    void show()
    {
        // cout << "queue: ";
        // for (int i = _head; i < _tail; i++)
        // {
        //     cout << elem[i] << ' ';
        // }
        // cout << endl;
    }

    queue()
    {
        _head = 0;
        _tail = 0;
    }

    void enqueue(int data)
    {
        elem[_tail] = data;
        _tail++;
        //cout<<"enqueue ";
        show();
    }

    void dequeue()
    {
        if (_tail - _head > 0)
            _head++;
        //cout<<"dequeue ";
        show();
    }

    void dequeue_t()
    {
        if (_tail - _head > 0)
            _tail--;
        //cout<<"dequeue_t ";
        show();
    }

    ll head()
    {
        if(_tail - _head == 0)
            return -1;
        return elem[_head];
    }

    ll tail()
    {
        return elem[_tail - 1];
    }

    bool isempty()
    {
        return _head == _tail ? true : false;
    }
};

int main()
{
    scanf("%d", &N);
    for (int i = 1; i < N; i++)
    {
        scanf("%lld %lld %lld", &l[i], &r[i], &t[i]);
    }
    queue q;
    //先处理i = N, N-1
    T[N] = 0;
    T[N-1] = t[N-1];
    q.enqueue(N);
    for (int i = N - 2; i >= 1; i--)
    {
        for (int j = l[i+1] - 1; j >= l[i]; j--)
        {
            // cout<<"i = "<<i<<" j = "<<j<<endl;
            // cout<<"l[i] = "<<l[i]<<" r[i] = "<<r[i]<<endl;
            while (!q.isempty() && T[q.tail()] >= T[j])
            {
                q.dequeue_t();
            }
            q.enqueue(j);
            while (!q.isempty() && q.head() > r[i])
            {
                q.dequeue();
            }
        }
        if (q.head() == -1)
        {
            T[i] = INF;
        }
        else
        {
            T[i] = T[q.head()] + t[i];
        }
        //cout << "T[" << i << "] = " << T[i] << ", q.head = " << q.head() << endl;
    }
    cout<<T[1]<<endl;    
    return 0;
}


