#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

//List Implementation Begin
#define LIST_NODE_DEFAULT_DATA 0
template <typename T>
class ListNode
{
public:
    T data;
    ListNode<T>* next;
    ListNode(T d = LIST_NODE_DEFAULT_DATA, ListNode<T>* n = nullptr)
    {
        data = d;
        next = n;
    }
};

template <typename T>
class List{
public:
    ListNode<T> *head, *tail;
    int size;

    List(){
        head = new ListNode<T>();
        tail = new ListNode<T>();
        head->next = tail;
        size = 0;
    }
    T operator[](int k){
        if(k < 0 || k >= size) return LIST_NODE_DEFAULT_DATA;
        ListNode<T> *p = head;
        int position = -1;
        while(position < k){
            p = p->next;
            position++;
        }
        return p->data;
    }
    void Insert(int k, T d){//插入值为d的节点，插入后其rank为k
        if(k < 0 || k > size) return;
        ListNode<T> *p = head, *q = head;
        int position = 0;
        while(position < k){
            p = p->next;
            position++;
        }
        q = p->next;
        p->next = new ListNode<T>(d, q);
        size++;
    }
    T Remove(int k){//移除不delete
        if(k < 0 || k >= size) return;
        ListNode<T> *p, *q = head;
        int position = -1;
        while(position < k-1){
            p = p->next;
            position++;
        }
        q = p->next;
        p->next = q->next;
        size--;
        return q;
    }
    void Print(){
        ListNode<T> *p= head;
        p = p->next;
        while(p != tail){
            cout<<p->data->data<<' ';
            p = p->next;
        }
        cout<<endl;
    }
    T Remove(T d){//移除第一个值为d的节点
        ListNode<T> *p = head->next, *q = head;
        while(p != tail){
            if(p->data == d){
                q->next = p->next;
                size--;
                break;
            }
            p = p->next;
            q = q->next;
        }
        return p->data;
    }
    int GetSize(){
        return size;
    }
};
//List Implementaion End

//Tree Implementation Begin
#define TREE_DEFAULT_DATA 0
template <typename T>
class TreeNode
{
public:
    TreeNode<T>* parent;
    List<TreeNode<T>*> children;
    T data;
    int height, size;

    TreeNode(T d = TREE_DEFAULT_DATA, TreeNode<T>* p = nullptr){
        data = d;
        parent = p;
        height = -1;
        size = -1;
    }
    void Add(int k, T d){//插入叶子节点作为rank k的儿子
        TreeNode<T>* node = new TreeNode(d, this);
        size++;
        height = max(height, node->height+1);
    }
    void Insert(int k, TreeNode<T> * node){//将node作为儿子插入，插入后其rank为k
        children.Insert(k, node);
        height = max(node->height+1, height);
        size += node->size;
        TreeNode<T> *p = parent, *q = this;
        int tem = node->size;
        while(p != nullptr){//更新祖先height,size 有问题
            p->height = max(q->height+1, p->height);
            p->size+=tem;
            p = p->parent;
            q = q->parent;
        }
    }
    TreeNode<T>* Remove(){//移除这个子树 
        TreeNode<T> *pa = this->parent, *p;
        this->parent = nullptr;
        pa->children.Remove(this);
        //更新height,size 有问题
        p = pa;
        int ds = size, temh;
        ListNode<TreeNode<int>*>* q;
        while(p != nullptr){
            p->size -= ds;
            temh = -1;
            q = p->children.head->next;
            while (q != p->children.tail)
            {
                temh = max(q->data->height, temh);
                q = q->next;
            }
            p->height = temh + 1;
            p = p->parent;
        }
        return this;
    }
};
//Tree Implementation End

//
TreeNode<int> TreeNodes[1000005]; 
int Root = -1;
int M, N;

int InitialHeight(int k){
    int h = 0;
    for(int i = 0; i < TreeNodes[k].children.GetSize();i++){
        TreeNode<int>* t = TreeNodes[k].children[i];
        if(t->height == -1){
            h = max(h, 1 + InitialHeight(t->data));
        }else{
            h = max(h, 1 + t->height);
        }
    }
    TreeNodes[k].height = h;
    return h;
}

int InitialSize(int k){
    int s = 1;
    for(int i = 0; i < TreeNodes[k].children.GetSize(); i++){
        TreeNode<int> *t = TreeNodes[k].children[i];
        if(t->size == -1){
            s += InitialSize(t->data);
        }else{
            s += t->size;
        }
    }
    TreeNodes[k].size = s;
    return s;
}

void Preload(){
    int a, b, s, h;
    for(int i=1;i<=N;i++){
        TreeNodes[i].data = i;
        cin>>a;
        for(int j = 1;j <= a;j++){
            cin>>b;
            TreeNodes[i].children.Insert(j-1, TreeNodes + b);
            TreeNodes[b].parent = TreeNodes + i;
        }
    }
    for(int i=1;i<=N;i++){
        if(TreeNodes[i].parent == nullptr) Root = i;
    }
    //初始化height,size
    InitialHeight(Root);
    InitialSize(Root);

}

int Search(){//读入并返回查找的节点的编号
    int tem = 0, pos = Root, num = 0;
    bool f = false;
    cin>>num;
    while(num > 0){
        num--;
        cin>>tem;
        if(tem < TreeNodes[pos].children.GetSize() && !f){
            pos = TreeNodes[pos].children[tem]->data;
        }else{
            f = true;
        }
    }
    return pos;
}

void Move(){
    int s = Search();
    TreeNode<int>* t = TreeNodes[s].Remove();
    int d = Search();
    int k;
    cin>>k;
    TreeNodes[d].Insert(k, t);
}

void QueryHeight(){
    int t = Search();
    cout<<TreeNodes[t].height<<endl;
}

void QuerySize(){
    int t = Search();
    cout<<TreeNodes[t].size<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin>>N>>M;
    Preload();
    int flag;
    for(int i = 0;i<M;i++){
        cin>>flag;
        switch (flag)
        {
        case 0:
            Move();
            break;
        
        case 1:
            QueryHeight();
            break;
        
        case 2:
            QuerySize();
            break;
        }
    }
    //DEBUG
    #ifdef DEBUG
    for (int i = 1; i <= N; i++)
    {
        cout << i << " size = " << TreeNodes[i].size << ", height = " << TreeNodes[i].height;
        cout << ", Children: ";
        TreeNodes[i].children.Print();
    }
    #endif
    return 0;
}