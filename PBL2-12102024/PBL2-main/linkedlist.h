#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

template <typename T>
struct Node 
{
    T data;
    Node<T>* next;
    Node(T x) : data(x), next(nullptr) {};
};

template <typename T>
class LinkList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    Node<T>* operator [](int index);
    Node<T>* Find(T x); 
    LinkList();
    ~LinkList();
    int Length() {return size;}; 
    void AddFirst(T x);
    void AddLast(T x);
    void AddMiddle(T x, T val);
    void DeleteFirst();
    void DeleteLast();
    void Delete(T x);
    void Sort(bool asc = true, int choice = 0);
    template <typename U>
    friend ostream& operator << (ostream &out, const LinkList<U>& list);
};

template <typename T>
LinkList<T>::LinkList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkList<T>::~LinkList() 
{
    Node<T>* cur = head;
    while (cur) 
    {
        Node<T>* next = cur->next;
        delete cur;
        cur = next;
    }
}

template <typename T>
void LinkList<T>::AddFirst(T x) 
{
    Node<T>* NewNode = new Node<T>(x);
    if (head == nullptr)
        head = tail = NewNode;
    else 
    {
        NewNode->next = head;
        head = NewNode;
    }
    size++;
}

template <typename T>
Node<T>* LinkList<T> :: operator[](int index)
{
    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp;
}

template <typename T>
void LinkList<T>::AddLast(T x) 
{
    Node<T>* NewNode = new Node<T>(x);
    if (head == nullptr)
        head = tail = NewNode;
    else 
    {
        tail->next = NewNode;
        tail = NewNode;
    }
    size++;
}

template <typename T>
void LinkList<T>::DeleteFirst() 
{
    Node<T>* tmp = head;
    head = head->next;
    if (head == nullptr) 
    tail = nullptr;
    delete tmp;
    --size;
}

template <typename T>
void LinkList<T>::Delete(T x) 
{
    if (head == nullptr) return;
    if (head->data == x) 
    DeleteFirst();
    else {
        Node<T>* cur = head;
        while (cur->next != nullptr) 
        {
            if (cur->next->data == x) 
            {
                Node<T>* tmp = cur->next;
                cur->next = tmp->next;
                tmp->next = nullptr;
                if (tmp == tail) tail = cur;
                delete tmp;
                --size;
                return;
            } 
            else cur = cur->next;
        }
    }
}

template <typename T>
void LinkList<T>::Sort(bool asc, int choice) 
{
    if (!head) return;
    Node<T>* pre_l = nullptr; 
    Node<T>* l = head;        
    while (l != nullptr) 
    {
        Node<T>* pre_r = l;  
        Node<T>* r = l->next; 
        while (r != nullptr) 
        {
            if (Compare(l->data, r->data, asc, choice)) 
            {
                if (pre_l != nullptr) 
                pre_l->next = r; 
                else head = r; 
                pre_r->next = r->next;
                r->next = l;          
                l = r;
                r = pre_r->next; 
                continue;        
            }
            pre_r = r; 
            r = r->next; 
        }
        pre_l = l;
        l = l->next; 
    } 
}

template <typename T>
Node<T>* LinkList<T>::Find(T x)
{
    Node<T>* cur = head;
    while (cur != nullptr) 
    {
        if (cur->data == x) 
        return cur; 
        cur = cur->next;
    }
    return nullptr;
}

template <typename U>
ostream& operator << (ostream &out, const LinkList<U>& list)
{
    Node<U>* cur = list.head;
    while (cur != nullptr) 
    {
        out << cur->data << endl;
        cur = cur->next;
    }
    return out;
}
#endif