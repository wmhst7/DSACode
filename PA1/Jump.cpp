#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#define ll long long
int N;
ll l[1000010], r[1000010];
ll T[1000010], t[1000010];
int buffer[1000010];

template <typename T>
class Queue
{
private:
    int _head, _tail;
    int _capacity;
    T *_elem;

public:
    Queue()
    {
        _head = 0;
        _tail = 0;
        _capacity = 1000010;
        _elem = (int *)buffer;
    }
    bool empty();
    bool push_back(const T);
    bool pop_before();
    bool pop_back();
    T &front();
    T &back();
    void show();
};

template <typename T>
bool Queue<T>::empty()
{
    return _head == _tail ? true : false;
}

template <typename T>
bool Queue<T>::push_back(const T t)
{
    if (_tail > _capacity - 1)
        return false;
    _elem[_tail] = t;
    _tail++;
    return true;
}

template <typename T>
bool Queue<T>::pop_before()
{
    if (_tail - _head <= 0)
        return false;
    _head++;
    return true;
}

template <typename T>
bool Queue<T>::pop_back()
{
    if (_tail - _head <= 0)
        return false;
    _tail--;
    return true;
}

template <typename T>
T &Queue<T>::front()
{
    return _elem[_head];
}

template <typename T>
T &Queue<T>::back()
{
    return _elem[_tail - 1];
}

template <typename T>
void Queue<T>::show()
{
    cout<<"Queue: ";
    for(int i = _head;i<_tail;i++){
        cout<<_elem[i]<<' ';
    }cout<<endl;
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i < N; i++)
    {
        scanf("%lld %lld %lld", &l[i], &r[i], &t[i]);
    }
    Queue<int> q;
    //先处理i = N, N-1
    T[N] = 0;
    T[N - 1] = t[N - 1];
    q.push_back(N);
    for (int i = N - 2; i >= 1; i--)
    {
        for (int j = l[i + 1]; j >= l[i]; j--)
        {
            while (!q.empty() && T[j] <= T[q.back()])
            {
                q.pop_back();
            }
            q.push_back(j);
            while (!q.empty() && q.front() > r[i])
            {
                q.pop_before();
            }
        }
        //q.show();
        if (q.empty())
        {
            T[i] = -1;
        }
        else
        {
            T[i] = t[i] + T[q.front()];
        }
    }
    //for (int i = 1; i <= N; i++)
        //cout << "T[" << i << "]: " << T[i] << endl;
    printf("%lld\n", T[1]);
    return 0;
}
