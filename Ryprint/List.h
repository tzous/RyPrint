#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;
 
//��struct����LinkNode��.ʹ�����ַ���ʹ����ʧȥ��װ��,����������.
//��Link���а�first��װ�������ڲ�,���ڸ�Link������LinkNodeʵ������ΪLinkʵ����˽�г�Ա,��֤�������ֱ�ӷ���.
 
//���ģ��Ķ���
template<typename Type>
struct LinkNode
{
    Type data;
    LinkNode<Type>* next;
    LinkNode(const Type& item, LinkNode<Type>* ptr=NULL)//���ڳ�ʼ��data��next
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
//������ģ��Ķ���
template<typename Type>
class List
{
private:
    LinkNode<Type>* first;//����ͷָ��
public:
    List()//���캯��
    {
        first = NULL;
    }
    List(const List<Type>& L)//�������캯��
    {
        first = NULL;
        CopyList(L);
    }
    List<Type>operator=(const List<Type>& L)//��ֵ���������
    {
        if(this==&L)
            return *this;
        MakeEmpty();
        CopyList(L);
        return *this;
    }
    ~List()//��������
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
 
    //���������ɾ���
    void InputFront(const Type& elem);
    void InputRear(const Type& elem);
    bool Insert(int i, const Type& x);
    bool Remove(int i, Type& x);
    //LinkNode<Type>* Search(const Type& x);
    bool Search(const Type& x);
    LinkNode<Type>* Locate(int i);
    bool GetData(int i, Type& x)const;
    bool SetData(int i, const Type& x);
 
    //��ո����б���
    void MakeEmpty();
    void CopyList(const List<Type>& L);
 
    //��������״̬
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
 
    //��ǰָ����ָ�����������е�λ��
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
 
    //��������
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
    //��Ҫ������ Max ��i Ӧ����ÿ���ڲ�ѭ�������ֵʱ��Ӧ�ñ���ʼ����
 
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
 
    //����������������
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
 
    cin >> x >> i;//��iλ�ò���ֵΪx�Ľ��
    L1.Insert(i, x);
    cout << L1;
 
    cin >> i;//Ҫɾ�������ֵ�λ��
    L1.Remove(i, x);
    cout << L1;
 
    cin >> x;//Ҫ���ҵ�����x
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