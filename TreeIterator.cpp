#include <iostream>
using namespace std;

template<class T>
class BTNode
{
public:
    T data;
    BTNode<T>* lchild,*rchild,*prev,*next;
    BTNode()
    {
        data = NULL;lchild = NULL;
        rchild  = NULL;
        prev = NULL;
        next = NULL;
    }
    BTNode(T k)
    {
        data = k;
        lchild = NULL;
        rchild  = NULL;
        prev = NULL;
        next = NULL;
    }
};
template <class T>
class BST
{
    BTNode<T>* head;
public:
    class TreeIterator
    {
    public:
        BTNode<T>* mem;
        TreeIterator()
        {
            mem = NULL;
        }
        void make(BTNode<T>*& q)
        {
            mem = q;
        }
        void operator = (TreeIterator itr)
        {
            this->mem = itr.mem;
        }
        bool operator ==(TreeIterator itr)
        {
            return this->mem==itr.mem;
        }
        TreeIterator operator +(int k)
        {
            while(k--&&mem!=NULL)
            {
                mem = mem->next;
            }
            return *this;
        }
        TreeIterator operator -(int k)
        {
            while(k--&&mem!=NULL)
            {
                mem = mem->prev;
            }
            return *this;
        }
        T& operator *()
        {
            return this->mem->data;
        }
        TreeIterator operator[](int k)
        {
            return *(*(this)+k);
        }
        void operator ++(int k=0)
        {
            this->mem = this->mem->next;
        }
        void operator--(int k=0)
        {
            this->mem = this->mem->prev;
        }
        bool operator !=(TreeIterator itr)
        {
            return !(*this==itr);
        }
    };
private:
    TreeIterator beg,ends;
public:
    BST()
    {
        head = NULL;
        BTNode<T>* q = new BTNode<T>();
        ends.make(q);
    }
    void insertElementUtil(BTNode<T>*& t,T k)
    {
        if(t==NULL)
        {
            t = new BTNode<T>(k);
        }
        else if(t->data<k)
        {
            insertElementUtil(t->rchild,k);
            BTNode<T>* q = t->rchild;
            while(q->lchild!=NULL)
                q = q->lchild;
            t->next = q;
            q->prev = t;
        }
        else
        {
            insertElementUtil(t->lchild,k);
            BTNode<T>* q = t->lchild;
            while(q->rchild!=NULL)
            {
                q = q->rchild;
            }
            t->prev = q;
            q->next = t;
        }
    }
    void initialize()
    {
        BTNode<T>* q;
        q = head;
        while(q->lchild!=NULL)
            q = q->lchild;
        beg.make(q);
        q = head;
        while(q->rchild!=NULL)
            q = q->rchild;
        ends.mem->prev = q;
        q->next = ends.mem;
    }
    void insertElement(T k)
    {
        insertElementUtil(head,k);
        initialize();
    }
    TreeIterator treeBegin()
    {
        return beg;
    }
    TreeIterator treeEnd()
    {
        return ends;
    }

};
/// code for demo

int main()
{
    BST<int> Tree;
    int c;char ch;
    do
    {
        cout<<"enter"<<endl;
        cin>>c;
        Tree.insertElement(c);
        cout<<"continue?"<<endl;
        cin>>ch;
    }while(ch=='y');
    BST<int>::TreeIterator itr;
    for(itr = Tree.treeBegin();itr!=Tree.treeEnd();itr++)
    {
        cout<<*itr<<" ";
    }
    cout<<endl<<"descending = "<<endl;
    for(itr = Tree.treeEnd()-1;;itr--)
    {
        cout<<*itr<<" ";
        if(itr==Tree.treeBegin())
            break;
    }
    cout<<endl;
    return 0;
}
