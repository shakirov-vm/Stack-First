#include <stdio.h>
#include <malloc.h>

const int POISON = -666;

void FillPoison(struct stack_t* stack);
stack_t StackConstruct(int capacity);
void StackDestruct(struct stack_t* stack);
void StackPush(struct stack_t* stack, int push);
void StackDump(struct stack_t* stack);
int StackPop(struct stack_t* stack, int position);

struct stack_t
{
	int* buf;
	int size;
	int capacity;
};

int main()
{
	printf("Hello world!\n");

	printf("Enter:\n");

	int N = 0;

	scanf("%d", &N);

	struct stack_t stack = StackConstruct(N);

	FillPoison(&stack);

	StackDump(&stack);

	StackPush(&stack, 10);

	int a = StackPop(&stack, 0);
	int b = StackPop(&stack, 1);

	printf("\n\n%d %d", a, b);

	StackDestruct(&stack);

	StackDump(&stack);
}

stack_t StackConstruct(int capacity)
{
	struct stack_t stack;
	if (capacity > 0)
	{
		stack.buf = (int*) calloc(capacity, sizeof(int));
		//FillPoison(&stack);  //        Не работает в этом месте                      ??
		//     Вроде & на месте
	}
	else printf("Need positive number\n");

	stack.size = 0;
	stack.capacity = capacity;

	return stack;
}
void StackDestruct(struct stack_t* stack)
{
	FillPoison(stack); //                                ??

	stack->buf = (int*) 00000001;

	stack->size = -1;
	stack->capacity = -1;
}
void FillPoison(struct stack_t* stack)
{
	for (int i = 0; i < stack->capacity; i++)
	{
		*(stack->buf + i) = POISON;
	}
}
void StackPush(struct stack_t* stack, int push)
{
	if (stack->size < stack->capacity)
	{
		for (int i = 0; i < stack->capacity; i++)
		{
			if (*(stack->buf + i) == POISON)
			{
				*(stack->buf) = push;
				stack->size++;
				break;
			}
		}
	}
	else printf("Stack is FULL\n");
}
void StackDump(struct stack_t* stack)
{
	printf("\nstack - [%p]\n", stack);
	printf("size - %d, capacity - %d, buf - [%p]\n", stack->size, stack->capacity, stack->buf);
	for (int i = 0; i < stack->capacity; i++)
	{
		printf("<%d> - >%d<\n", i, *(stack->buf + i));
	}
	printf("\n");
}
int StackPop(struct stack_t* stack, int position)
{
	return *(stack->buf + position);
}
