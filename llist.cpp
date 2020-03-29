#include <llist.h>
#include <iostream>

void LList::push_back(int val)
{
	Node *nd = new Node;
	
	nd->data = val;
	nd->next = NULL;

	if (head == NULL)
	{
		head = nd;
	}
	else
	{
		Node *current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = nd;
	}
}	

size_t LList::size() const
{
	size_t res = 1;
	Node *current = head;
	while (current->next != NULL)
	{
		current = current->next;
		res++;
	}
	return res;
}

void LList::push_front(int val)
{
	Node *nd = new Node;
		
	nd->data = val;
	nd->next = head;
	head = nd;
}

void LList::pop_back()
{
	Node *current = head;
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

void LList::pop_front()
{
	size_t res = size();
        if (res == 1)
        {
		delete head;
                return;
        }

	Node *current = head;
	current = current->next;
	head = current;	
}

int& LList::operator[](size_t idx)
{
	Node *current = head;
	for (size_t i = 0; i < idx; i++)
	{
		current = current->next;
	}
	int &res = current->data;
	return res;
}

int LList::operator[](size_t idx) const
{
	Node *current = head;
        for (size_t i = 0; i < idx; i++)
        {
                current = current->next;
        }
	int res = current->data;
	return res;
}

void LList::erase_at(size_t idx)
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
		std::cout << "rere" << std::endl;
		pop_front();
		return;
	}
	
	Node *current = head;
	for (size_t k = 0; k < idx; k++)
	{
		current = current->next;
	}
	Node *cur1 = head;
	for (size_t k = 0; k < idx - 1; k++)
	{
		cur1 = cur1->next;
	}
	delete cur1->next;
	cur1->next = current->next;

}

void LList::insert_at(size_t idx, int val)
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

	Node *current = head;
        for (size_t k = 0; k < idx; k++)
        {
                current = current->next;
        }
	
	current->data = val;
}

void LList::reverse()
{
	if (size() == 1)
		return;
	Node *prev = NULL;
	Node *curr = head;
	Node *next = head->next;
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
	


// HERE WILL BE YOUR CODE


