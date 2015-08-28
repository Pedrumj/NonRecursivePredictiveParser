#include "Stdafx.h"
#include <Windows.h>


struct stack{
struct stack *previous;
int value;
};

void Push(struct stack *__ptrHeader, int value){
	struct stack *_ptrNew = (struct stack *)malloc(sizeof(struct stack));
	_ptrNew->value = value;
	_ptrNew->previous = __ptrHeader;
	__ptrHeader  =_ptrNew;

}

struct stack *Pop(struct stack *__ptrHeader, int value){
	struct stack *_ptrTemp = (struct stack *)malloc(sizeof(struct stack));
	_ptrTemp = __ptrHeader;
	free(_ptrTemp);
	_ptrTemp = NULL;
	__ptrHeader = __ptrHeader->previous;
	return __ptrHeader;
}