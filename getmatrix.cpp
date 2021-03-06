#include <iostream>
#include <fstream>
#include <cstdlib>
#include <malloc.h>
#include <string>
#include "smatrix.h"

//reading sparse matrix from file
//each row & column is a circular doubly linked list
//each list head is an element of an array (row/col)

void addNode(int val, int i, int j, node **&row, node **&col)
{
	node *el = new node;
	el->val = val;
	el->row = i;
	el->col = j;
	el->right = row[i];
	el->down = col[j];
	node *temp = row[i];
	while (temp->right != row[i])
	{
		temp = temp->right;
	}
	temp->right = el;
	el->left = temp;
	temp = col[j];
	while (temp->down != col[j])
	{
		temp = temp->down;
	}
	temp->down = el;
	el->up = temp;
}

void getMatrix(node **&row, node **&col, int size, int base_elem, std::string filename)
{
	std::ifstream data(filename);
	if (!data.is_open())
	{
		throw std::runtime_error("file " + filename + " not found");
	}

	int value;
	for (int i = 0; i < size; i++) // row
	{
		for (int j = 0; j < size; j++) //column
		{
			data >> value;
			if (value != base_elem)
			{
				addNode(value, i, j, row, col);
			}
		}
	}

	data.close();
}

node * makeHead()
{
	node *head = new node;
	head->down = head;
	head->up = head;
	head->left = head;
	head->right = head;
	head->row = -1;
	head->col = -1;
	head->val = 0;
	return head;
};
