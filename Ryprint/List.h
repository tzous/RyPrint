#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
 
//用struct定义LinkNode类.使用这种方法使该类失去封装性,但简化了描述.
//在Link类中把first封装在了其内部,属于该Link的所有LinkNode实例都成为Link实例的私有成员,保证不被外界直接访问.
 
//结点模板的定义
template<typename Type>
struct LinkNode
{
    Type data;
    LinkNode<Type>* next;
    LinkNode(const Type& item, LinkNode<Type>* ptr=NULL)//用于初始化data和next
    {
        data = item;
        next = ptr;
    }
    /*    LinkNode(LinkNode<Type>* ptr=NULL)
        {
            next = ptr;
        }
    */
};
//单链表模板的定义
template<typename Type>
class List
{
private:
    LinkNode<Type>* first;//链表头指针
public:
    List()//构造函数
    {
        first = NULL;
    }
    List(const List<Type>& L)//拷贝构造函数
    {
        first = NULL;
        CopyList(L);
    }
    List<Type>operator=(const List<Type>& L)//赋值运算符符号
    {
        if(this==&L)
            return *this;
        MakeEmpty();
        CopyList(L);
        return *this;
    }
    ~List()//析构函数
    {
        LinkNode<Type>* p;
		p=first;
        while(p)
        {          
            first=p->next;
            delete p;
			p=first;
        }
    }
 
    //单链表的增删查改
    void InputFront(const Type& elem);
    void InputRear(const Type& elem);
    bool Insert(int i, const Type& x);
    bool Remove(int i, Type& x);
    //LinkNode<Type>* Search(const Type& x);
    bool Search(const Type& x);
    LinkNode<Type>* Locate(int i);
    bool GetData(int i, Type& x)const;
    bool SetData(int i, const Type& x);
 
    //清空复制列表结点
    void MakeEmpty();
    void CopyList(const List<Type>& L);
 
    //链表自身状态
    int Length() const
    {
        LinkNode<Type>* s=first;
        int count=1;
        while(s->next)
        {
            count++;
            s = s->next;
        }
        return count;
    }
    bool IsEmpty() const
    {
        return first==NULL;
    }
    bool IsFull() const
    {
        return false;
    }
 
    //当前指针所指向结点在链表中的位置
    int GetLocation(const LinkNode<Type>* iter)
    {
        LinkNode<Type>* p = first;
        int L = Length();
        int count = 0;
        while(count <= L)
        {
            count++;
            if(p==iter)
            {
                return count;
            }
            p = p->next;
        }
        return 0;
    }
    bool PutLocation(const LinkNode<Type>* iter)
    {
        LinkNode<Type>* p = first;
        int L = Length();
        int count = 0;
        while(count <= L)
        {
            count++;
            if(p==iter)
            {
                cout << count;
                return true;
            }
            p = p->next;
        }
        return false;
    }
 
    //排序（升序）
    /*    void Sort()
        {
            LinkNode<Type>* Max = new LinkNode<Type> (first->data);
            LinkNode<Type>* iter1;
            LinkNode<Type>* iter2 = first;
            int i;
            Type x;
             while(iter2)
            {
                iter1 = iter2;
                while(iter1)
                {
                    if(Max->data < iter1->data)
                    {
                        Max->data = iter1->data;
                        i = GetLocation(iter1);
                    }
                    iter1 = iter1->next;
                }
                if(Locate(i)!=iter2)
                {
                    Remove(i, x);
                    InputFront(Max->data);
                    //iter2 = iter2->next;
                }
                else
                {
                    iter2 = iter2->next;
                    Remove(i, x);
                    InputFront(Max->data);
                }
                Max->data = iter2->data;
            }
        }
    */
    //主要问题是 Max 和i 应该在每次内层循环找最大值时都应该被初始化。
 
    void Sort()
    {
        LinkNode<Type>* iter1;
        LinkNode<Type>* iter2 = first;
        LinkNode<Type>* Max = new LinkNode<Type> (iter2->data);
        int i=GetLocation(iter2);
        Type x;
        while(iter2)
        {
            iter1 = iter2;
            while(iter1)
            {
                if(Max->data < iter1->data)
                {
                    Max->data = iter1->data;
                    i = GetLocation(iter1);
                }
                iter1 = iter1->next;
            }
            //cout<<Max->data<<endl;
            if(Locate(i)!=iter2)
            {
                Remove(i, x);
                InputFront(Max->data);
                //iter2 = iter2->next;
            }
            else
            {
                iter2 = iter2->next;
                Remove(i, x);
                InputFront(Max->data);
            }
            //LinkNode<Type>* iter=iter2;
 
            if(iter2)
            {
                Max->data = iter2->data;
                i=GetLocation(iter2);
            }
 
        }
    }
 
    //输入输出运算符重载
    friend ostream& operator<<(ostream& out, const List<Type>& L)
    {
        LinkNode<Type>* iter = L.first;
        while(iter)
        {
            out << iter->data << " ";
            iter = iter->next;
        }
        out << endl;
        return out;
    }
    friend istream& operator>>(istream& in, List<Type>& L)
    {
        return in;
    }
};

/*
int main()
{
    List<int> L1;
    int n1;
    int x, i;
    cin >> n1;
    for(int i = 0; i < n1; i++)
    {
        int num;
        cin >> num;
        L1.Insert(i+1,num);
    }
 
    cin >> x >> i;//在i位置插入值为x的结点
    L1.Insert(i, x);
    cout << L1;
 
    cin >> i;//要删除的数字的位置
    L1.Remove(i, x);
    cout << L1;
 
    cin >> x;//要查找的数字x
    L1.Search(x);
    cout << endl;
 
    L1.Sort();
    cout << L1;
 
    int n2;
    cin >> n2;
    for(int i = 0; i < n2; i++)
    {
        int num;
        cin >> num;
        L1.InputFront(num);
    }
    L1.Sort();
    cout << L1;
 
    return 0;
}
*/