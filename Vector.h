#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct{
 void** v;
 int size;
 int max_size;
}vector_t;

vector_t* vector_new(int init_size);

void vector_free(vector_t** v);

int vector_size(vector_t* v);

int vector_maxsize(vector_t* v);

int vector_isfull(vector_t* v);

int vector_isempty(vector_t* v);

void* vector_get(vector_t* v,int index);

void* vector_set(vector_t* v,int index,void* value);

int vector_add(vector_t* v,void* value);

int vector_add_first(vector_t* v, void* value);

int vector_insert(vector_t* v,int index,void* value);

int vector_insert_sorted(vector_t* v,void* value,int(*compare)(void*,void*));

void* vector_remove(vector_t* v,int index);

void vector_printf(vector_t* v,void (*printf_)(void*));

void vector_shuffle(vector_t* v);

/********************ALGORITMOS DE ORDENAMIENTO***************************************/

void vector_select_sort(vector_t* v,int (*compare)(void*,void*));   

void vector_insert_sort(vector_t* v,int (*compare)(void*,void*));

void vector_bubble_sort(vector_t* v,int (*compare)(void*,void*));

void vector_bubble_sort_improved(vector_t* v,int (*compare)(void*,void*));

void vector_quick_sort(vector_t* v,int (*compare)(void*,void*));

//este procedimiento es auxiliar a vector_quick_sort
void _quick_sort(void** start,void** end,int(*compare)(void*,void*));
//

void vector_merge_sort(vector_t* v,int (*compare)(void*,void*));

//estos procediminetos son auxiliares a vector_merge_sort 
void merge_sort(vector_t* v,int bottom,int top,int(*compare)(void*,void*));

void _merge(vector_t* v,int bottom,int middle,int top,int(*compare)(void*,void*));
//

void vector_shell_sort(vector_t* v,int (*compare)(void*,void*));

/*******************ALGORITMOS DE BUSQUEDA********************************************/

int vector_sequential_search(vector_t* v,void* value,int (*compare)(void*,void*));

int vector_binary_search(vector_t* v,void* value,int (*compare)(void*,void*));

#include "Vector.c"
#endif //VECTOR_H_INCLUDED