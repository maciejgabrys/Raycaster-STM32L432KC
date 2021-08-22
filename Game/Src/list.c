#include <stdlib.h>
#include "list.h"
#include "main.h"

list_t* ListNew(void)
{
	list_t* ret = (list_t*)malloc(sizeof(list_t));
	if (ret != NULL)
	{
		ret->front = NULL;
		ret->back = NULL;
		ret->length = 0;
	}
	return ret;
}

int16_t ListPushFront(list_t* list, void* obj)
{
	uint8_t ret = -1;
	if (list != NULL)
	{
		node_t* new = (node_t*)malloc(sizeof(node_t));
		if (new == NULL)
		{
			ret = -1;
		}
		else
		{
			new->next = list->front;
			new->prev = NULL;
			new->obj = obj;
			if (list->front != NULL)
			{
				list->front->prev = new;
			}
			else
			{
				list->back = new;
			}
			list->front = new;
			ret = ++list->length;
		}
	}
	return ret;
}

int16_t ListPushBack(list_t* list, void* obj)
{
	uint8_t ret = -1;
	if (list != NULL)
	{
		node_t* new = (node_t*)malloc(sizeof(node_t));
		if (new == NULL)
		{
			ret = -1;
		}
		else
		{
			new->prev = list->back;
			new->next = NULL;
			new->obj = obj;
			if (list->back != NULL)
			{
				list->back->next = new;
			}
			else
			{
				list->front = new;
			}
			list->back = new;
			ret = ++list->length;
		}
	}
	return ret;
}

int16_t ListRemove(list_t* list, void* obj)
{
	uint8_t ret = -1;
	if (list != NULL)
	{
		node_t* node = list->front;
		while (node != NULL)
		{
			if (node->obj == obj)
			{
				if (list->front == node && list->back == node)
				{
					list->front = NULL;
					list->back = NULL;
				}
				else if (list->front == node)
				{
					list->front = node->next;
					list->front->prev = NULL;
				}
				else if (list->back == node)
				{
					list->back = node->prev;
					list->back->next = NULL;
				}
				else
				{
					node->next->prev = node->prev;
					node->prev->next = node->next;
				}
				free(node);
				ret = --list->length;
				break;
			}
			node = node->next;
		}
	}
	return ret;
}

int16_t ListForEach(list_t* list, void(*func)(void* obj))
{
	int16_t ret = -1;
	if (list != NULL)
	{
		ret = 0;
		node_t* node = list->front;
		while (node != NULL)
		{
			func(node->obj);
			node = node->next;
		}
	}
	return ret;
}

int16_t ListForEachReverse(list_t* list, void(*func)(void* obj))
{
	int16_t ret = -1;
	if (list != NULL)
	{
		ret = 0;
		node_t* node = list->back;
		while (node != NULL)
		{
			func(node->obj);
			node = node->prev;
		}
	}
	return ret;
}

int16_t ListFreeAndDelete(list_t* list)
{
	int16_t ret = -1;
	if (list != NULL)
	{
		ret = 0;
		node_t* node = list->front;
		while (node != NULL)
		{
			free(node->obj);
			free(node);
			node = node->next;
		}
		free(list);
	}
	return ret;
}

int16_t ListDelete(list_t* list)
{
	int16_t ret = -1;
	if (list != NULL)
	{
		ret = 0;
		node_t* node = list->front;
		while (node != NULL)
		{
			free(node);
			node = node->next;
		}
		free(list);
	}
	return ret;
}
