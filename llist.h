#ifndef LLIST_H
#define LLIST_H

#include <cstddef>
#include <iostream>

template <typename DataType>
struct Node
{
    DataType data;
    Node *next;
};

template <typename DataType>
class LList
{
    private:
        Node<DataType> *head; // HERE WILL BE YOUR CODE

    public:

    LList();                         // construct new collection
    ~LList();                        // free resources
    void forceNodeDelete(Node<DataType>* node);

    LList(const LList &copyList);
    LList& operator=(const LList& copyList);
    LList(LList&& moveList) noexcept;
    LList& operator=(LList&& moveList) noexcept;

    void push_back(DataType val);         // add new value at the end:  [1 2 3 4] -> [1 2 3 4 5]
    void push_front(DataType val);        // add new value at the begin [1 2 3 4] -> [5 1 2 3 4]
    void pop_back();          // remove at the end          [1 2 3 4] -> [1 2 3]
    void pop_front();         // remove at the front        [1 2 3 4] -> [2 3 4]
    size_t size() const;             // get actual number of items [1 2 3 4] -> 4
    DataType& operator[](size_t idx);     // get rw access ot specific item addressing by idx
    DataType  operator[](size_t idx) const; //get read-only access
    void erase_at(size_t idx);       // remove item at specific position: [1 2 3 4], 2 -> [1 2 4]
    void insert_at(size_t idx, int val); // insert item at specific position: [1 2 3 4], 1, 5 -> [1 5 2 3 4]
    void reverse();                  // reverse item sequense: [1 2 3 4] -> [4 3 2 1]
};

template <typename DataType>
LList<DataType>::LList()
{
    head = nullptr;
}
template <typename DataType>
LList<DataType>::~LList()
{
    forceNodeDelete(head);
}
template <typename DataType>
void LList<DataType>::forceNodeDelete(Node<DataType>* node)
{
    if (node == nullptr) {
        return;
    }

    Node<DataType> *buf = node;
    while (buf)
    {
        buf = buf->next;
        delete node;
        node = buf;
    }
}
template <typename DataType>
LList<DataType>::LList(const LList &copyList)
{
    Node<DataType> *newHead = new Node<DataType>;
    newHead->data = copyList.head->data;
    this->head = newHead;
    this->head->next = nullptr;
    Node<DataType> *currCopy = copyList.head;
    Node<DataType> *curr = this->head;
    while (currCopy->next != nullptr)
    {
        Node<DataType> *newNode = new Node<DataType>;
        newNode->data = currCopy->next->data;
        newNode->next = nullptr;
        curr->next = newNode;
        curr = curr->next;
        currCopy = currCopy->next;
    }
}
template <typename DataType>
LList<DataType>& LList<DataType>::operator=(const LList &copyList)
{
    if (this == &copyList)
        return *this;
    LList buf(copyList);
    Node<DataType> *newHead = new Node<DataType>;
    newHead->next = nullptr;
    newHead->data = buf.head->data;
    head = newHead;
    Node<DataType> *curr = head;
    Node<DataType> *currCopy = buf.head;
    while (currCopy->next != nullptr)
    {
        curr->next = new Node<DataType>;
        curr->next->data = currCopy->next->data;
        curr->next->next = nullptr;
        curr = curr->next;
        currCopy = currCopy->next;
    }
    return *this;
}
template <typename DataType>
LList<DataType>::LList(LList&& moveList) noexcept
{

    head = moveList.head;
    moveList.head = nullptr;
}
template <typename DataType>
LList<DataType>& LList<DataType>::operator=(LList&& moveList) noexcept
{
    if (this == &moveList)
    {
        return *this;
    }
    forceNodeDelete(head);
    this->head = moveList.head;
    moveList.head = nullptr;
    return *this;
}
template <typename DataType>
void LList<DataType>::push_back(DataType val)
{
    Node<DataType> *nd = new Node<DataType>;

    nd->data = val;
    nd->next = NULL;

    if (head == NULL)
    {
        head = nd;
    }
    else
    {
        Node<DataType> *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = nd;
    }
}
template <typename DataType>
size_t LList<DataType>::size() const
{
    size_t res = 1;
    Node<DataType> *current = head;
    while (current->next != NULL)
    {
        current = current->next;
        res++;
    }
    return res;
}
template <typename DataType>
void LList<DataType>::push_front(DataType val)
{
    Node<DataType> *nd = new Node<DataType>;

    nd->data = val;
    nd->next = head;
    head = nd;
}
template <typename DataType>
void LList<DataType>::pop_back()
{
    Node<DataType> *current = head;
    size_t res = size();
    if (res == 1)
    {
        delete head;
        return;
    }
    for (size_t i = 0; i < res - 2; i++)
    {
         current = current->next;
    }
    delete current->next;
    current->next = NULL;

}
template <typename DataType>
void LList<DataType>::pop_front()
{
    size_t res = size();
        if (res == 1)
        {
        delete head;
                return;
        }

    Node<DataType> *current = head;
    current = current->next;
    head = current;
}
template <typename DataType>
DataType& LList<DataType>::operator[](size_t idx)
{
    Node<DataType> *current = head;
    for (size_t i = 0; i < idx; i++)
    {
        current = current->next;
    }
    int &res = current->data;
    return res;
}
template <typename DataType>
DataType LList<DataType>::operator[](size_t idx) const
{
    Node<DataType> *current = head;
        for (size_t i = 0; i < idx; i++)
        {
                current = current->next;
        }
    int res = current->data;
    return res;
}
template <typename DataType>
void LList<DataType>::erase_at(size_t idx)
{
    if (idx + 1 > size())
    {
        std::cout << "Error, index is bigger than size if the list " << std::endl;
        return;
    }

    if (idx + 1 == size())
    {
        pop_back();
        return;
    }

    if (idx == 0)
    {
        pop_front();
        return;
    }

    Node<DataType> *current = head;
    for (size_t k = 0; k < idx; k++)
    {
        current = current->next;
    }
    Node<DataType> *cur1 = head;
    for (size_t k = 0; k < idx - 1; k++)
    {
        cur1 = cur1->next;
    }
   // delete cur1->next;
    cur1->next = current->next;

}
template <typename DataType>
void LList<DataType>::insert_at(size_t idx, int val)
{
    if ((idx == 0)&&(idx == size() - 1))
    {
        erase_at(idx);
        if (idx == 0)
            push_front(val);
        else
            push_back(val);
    }

    if (idx > size() - 1)
        return;

    Node<DataType> *current = head;
        for (size_t k = 0; k < idx; k++)
        {
                current = current->next;
        }

    current->data = val;
}
template <typename DataType>
void LList<DataType>::reverse()
{
    if (size() == 1)
        return;
    Node<DataType> *prev = NULL;
    Node<DataType> *curr = head;
    Node<DataType> *next = head->next;
    while (next != NULL)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;
    head = curr;
}

#endif //LLIST_H
