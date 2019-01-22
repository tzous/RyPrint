#include "StdAfx.h"
#include "List.h"


template<typename Type>
void List<Type>::InputFront(const Type& elem)
{
    LinkNode<Type>* NewNode = new LinkNode<Type>(elem);
    if(NewNode==NULL)
    {
        cout << "创建结点失败" << endl;
    }
    NewNode->next = first;
    first = NewNode;
}
template<typename Type>
void List<Type>::InputRear(const Type& elem)
{
    LinkNode<Type>* NewNode = new LinkNode<Type>(elem);
    if(NewNode==NULL)
    {
        cout << "创建结点失败" << endl;
    }
    if(first==NULL)
    {
        first = NewNode;
    }
    else
    {
        LinkNode<Type>* rear = first;
        while(rear->next)
        {
            rear = rear->next;
        }
        rear->next = NewNode;
    }
}
template<typename Type>
bool List<Type>::Insert(int i, const Type& x)
{
    LinkNode<Type>* newNode = new LinkNode<Type>(x);
    if(i<1)
    {
        cout << "Location error" << endl;
        return false;
    }
    if(i==1)
    {
        newNode->next = first;
        first = newNode;
        return true;
    }
    else
    {
        LinkNode<Type>* pre = first;
        for(int j=1; j<i-1; j++)
        {
            pre=pre->next;
            if(pre==NULL)
                break;
        }
        if(pre==NULL)
        {
            cout << "Location error" << endl;
            return false;
        }
        newNode->next  = pre->next;
        pre->next = newNode;
        return true;
    }
}
 
template<typename Type>
bool List<Type>::Remove(int i, Type& x)
{
    LinkNode<Type>* del;
    LinkNode<Type>* pre;
    if(i<1)
    {
        cout << "Location error" << endl;
        return false;
    }
    if(i==1)
    {
        del = first;
        first = del->next;
        x = del->data;
        delete del;
        return true;
    }
    else
    {
        pre = first;
        for(int j=1; j<i-1; j++)
        {
            pre = pre->next;
            if(pre==NULL)
                break;
        }
        if(pre==NULL)
        {
            cout << "Location error" << endl;
            return false;
        }
 
        del = pre->next;
        x = del->data;
        pre->next = del->next;
        delete del;
        return true;
    }
}
template<typename Type>
//LinkNode<Type>* List<Type>::Search(const Type& x)
/*{
    LinkNode<Type>* iter = first;
    while(iter)
    {
        if(iter->data == x)
            return iter;
        iter = iter->next;
    }
    return iter;
}*/
bool List<Type>::Search(const Type& x)
{
    LinkNode<Type>* iter = first;
    while(iter)
    {
        if(iter->data == x)
        {
            PutLocation(iter);
            return true;
        }
        iter = iter->next;
    }
    cout << "Not found";
    return false;
}
template<typename Type>
LinkNode<Type>* List<Type>::Locate(int i)
{
    LinkNode<Type>* iter = first;
    int count = 0;
    while(iter)
    {
        count++;
        if(count == i)
        {
            return iter;
        }
        else
        {
            iter=iter->next;
        }
    }
    return iter;
}
template<typename Type>
bool List<Type>::GetData(int i, Type& x)const
{
    if(i<1)
    {
        cout << "Location error" << endl;
        return false;
    }
    else
    {
        LinkNode<Type>* nd = Locate(i);
        if(nd==NULL)
        {
            cout << "Location error" << endl;
            return false;
        }
        else
        {
            x = nd->data;
            return true;
        }
    }
 
}
template<typename Type>
bool List<Type>::SetData(int i, const Type& x)
{
    if(i<1)
    {
        cout << "Location error" << endl;
        return;
    }
    else
    {
        LinkNode<Type>* nd = Locate(i);
        if(nd==NULL)
        {
            cout << "Location error" << endl;
            return false;
        }
        else
        {
            nd->data = x;
            return true;
        }
    }
}
 
template<typename Type>
void List<Type>::MakeEmpty()
{
    LinkNode<Type>* del;
    while(first)
    {
        del = first;
        while(del->next)
        {
            del = del->next;
        }
        delete del;
    }
    return;
}
template<typename Type>
void List<Type>::CopyList(const List<Type>& L)
{
    if(L.first==NULL)
    {
        MakeEmpty();
    }
    else
    {
        LinkNode<Type>* iter = first;
        while(iter)
        {
            InputRear(iter->data);
            iter = iter->next;
        }
    }
}