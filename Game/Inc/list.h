#ifndef __LIST_H_
#define __LIST_H_

#include <stdint.h>

typedef struct node node_t;
struct node
{
	void* obj;
	node_t* prev;
	node_t* next;
};
typedef struct
{
	node_t* front;
	node_t* back;
	uint8_t length;
} list_t;

list_t* ListNew(void);
int16_t ListPushFront(list_t* list, void* obj);
int16_t ListPushBack(list_t* list, void* obj);
int16_t ListRemove(list_t* list, void* obj);
int16_t ListForEach(list_t* list, void(*func)(void* obj));
int16_t ListForEachReverse(list_t* list, void(*func)(void* obj));
int16_t ListFreeAndDelete(list_t* list);
int16_t ListDelete(list_t* list);

#endif /* __LIST_H_ */
