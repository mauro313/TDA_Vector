#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Vector.h"

/**
 * @brief create a new vector with the select max size.
 * 
 * @param maxsize 
 * @return vector_t* 
 */
vector_t* vector_new(int maxsize){
  vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
  if(vector == NULL){
    printf("\nmemory cannot be reserved(1)\n");
    exit(EXIT_FAILURE);
   }
  vector->v =(void**)malloc(maxsize*sizeof(void*));
  if(vector->v == NULL){
    free(vector);
    vector = NULL;
    printf("\nmemory cannot be reserved(2)\n");
    exit(EXIT_FAILURE);
  }
  vector->size = 0;
  vector->max_size = maxsize;
  return vector;
}

/**
 * @brief free the memory of a vector.
 * 
 * @param v 
 */
void vector_free(vector_t** v){
  if(v != NULL && (*v) != NULL){
    free((*v)->v);
    (*v)->v = NULL;
    free(*v);
    *v = NULL;
  }
}

/**
 * @brief return the current size of a vector.
 * 
 * @param v 
 * @return int 
 */
int vector_size(vector_t* v){
  if(v == NULL){
    printf("\nvector pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  return v->size;
}

/**
 * @brief return the max size of a vector.
 * 
 * @param v 
 * @return int 
 */
int vector_maxsize(vector_t* v){
  if(v == NULL){
    printf("\nvector pointer is NULL(2)\n");
    exit(EXIT_FAILURE);
  }
  return v->max_size;
}

/**
 * @brief return true if the vector is full and false if is not.
 * 
 * @param v 
 * @return true 
 * @return false 
 */
bool vector_isfull(vector_t* v){
  if(v == NULL){
    printf("\nvector pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  return (v->size == v->max_size);
}

/**
 * @brief return true if the vector is empty and false if is not.
 * 
 * @param v 
 * @return true 
 * @return false 
 */
bool vector_isempty(vector_t* v){
  if(v == NULL){
    printf("\nvector pointer is NULL(4)\n");
    exit(EXIT_FAILURE);
  }
  return (v->size == 0);
}

/**
 * @brief return the element in the selected position.
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_get(vector_t* v,int index){
  if(v == NULL){
    printf("\nvector pointer is NULL(5)\n");
    exit(EXIT_FAILURE);
  }
  if(index<0 || index>=v->size){
    printf("\ninvalid index(1)\n");
    exit(EXIT_FAILURE);
  }
  return v->v[index];
}

/**
 * @brief exchange the element in the select position.Return the exchanged element.
 * 
 * @param v 
 * @param index 
 * @param value 
 * @return void* 
 */
void* vector_set(vector_t* v,int index,void* value){
  if(v == NULL){
    printf("\nvector pointer is NULL(6)\n");
    exit(EXIT_FAILURE);
  }
  if(index<0 || index>=v->size){
    printf("\ninvalid index(2)\n");
    exit(EXIT_FAILURE);
  }
  void* returned = v->v[index];
  v->v[index] = value;
  return returned;
}

/**
 * @brief add an element at the end of a vector. Return true if the element was added and false
 * otherwise (the vector is full).
 * 
 * @param v 
 * @param value 
 * @return bool 
 */
bool vector_add(vector_t* v,void* value){
  if(v == NULL){
    printf("\nvector pointer is NULL(7)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(!vector_isfull(v)){
    v->v[v->size] = value;
    v->size++;
    returned = true;
  }
  return returned;
}

/**
 * @brief add an element at the begin of a vector.Return true if the element was added and 
 * false otherwise.
 * 
 * @param v 
 * @param value 
 * @return bool 
 */
bool vector_add_first(vector_t* v, void* value){
  if(v == NULL){
    printf("\nvector pointer is NULL(8)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(!vector_isfull(v)){
    v->size++;
    for(int i=v->size-1;i=1;i--){
      v->v[i] = v->v[i-1];
    }
    v->v[0] = value;
    returned = true;
  }
  return returned;
}

/**
 * @brief insert an element at the selected position. Return true if the element was added and false
 * otherwise.
 * 
 * @param v 
 * @param index 
 * @param value 
 * @return bool 
 */
bool vector_insert(vector_t* v,int index,void* value){
  if(v == NULL){
    printf("\nvector pointer is NULL(9)\n");
    exit(EXIT_FAILURE);
  }
  if(index<0 || index>v->size || index == v->max_size){
    printf("\ninvalid index(3)\n");
    exit(EXIT_FAILURE);
  }
  int returned = 0;
  if(!vector_isfull(v)){
    v->size++;
    for(int i=v->size-1;i>index;i--){
      v->v[i] = v->v[i-1];
    }
    v->v[index] = value;
    returned = true;
  }
  return returned;
}

/**
 * @brief add an element in sorted form. Return true if the element was added and false otherwise
 * (vector full).
 * 
 * @param v 
 * @param value 
 * @param compare 
 * @return bool 
 */
bool vector_insert_sorted(vector_t* v,void* value,int(*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL(10)");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(!vector_isfull(v)){
    int index = 0;
    while(index<v->size && compare(value,v->v[index])>=0){
      index++;
    }
    if(index == 0 && vector_isempty(v)){
      v->v[index] = value;
    }
    else{
      v->size++;
      for(int i=v->size-1;i>index;i--){
        v->v[i]=v->v[i-1];
      }
      v->v[index]=value;
    }
    returned = true;
  }
  return returned;
}

/**
 * @brief remove the element in the selected position.
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_remove(vector_t* v,int index){
  if(v == NULL){
    printf("\nvector pointer is NULL(11)\n");
    exit(EXIT_FAILURE);
  }
  if(index<0 || index>=v->size){
    printf("\ninvalid index(4)\n");
    exit(EXIT_FAILURE);
  }
  void* returned = v->v[index];
  v->size--;
  for(int i=index;i<v->size;i++){
    v->v[i] = v->v[i+1];
  }
  return returned;
}

/**
 * @brief print the vector.
 * 
 * @param v 
 * @param printf_ 
 */
void vector_printf(vector_t* v,void (*printf_)(void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(12)\n");
    return;
  }
  for(int i=0;i<v->size;i++){
    printf_(v->v[i]);
  }
}

/**
 * @brief shuffle the elements of a vector.
 * 
 * @param v 
 */
void vector_shuffle(vector_t* v){
  if(v == NULL){
    printf("\nvector pointer is NULL(13)\n");
    return;
  }
  if(!vector_isempty(v)){
    srand(time(NULL));
    for(int i=0;i<v->size;i++){
      int index = rand ()%v->size;
      void* auxiliar = v->v[index];
      v->v[index] = v->v[i];
      v->v[i]= auxiliar;
    }
  }
}

/********************SORT ALGORITHMS***************************************/

/**
 * @brief version of the select sort.
 * 
 * @param v 
 * @param compare 
 */
void vector_select_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(14)\n");
    return;
  }
  int size = v->size;
  for(;size>0;size--){
    for(int i=0;i<size;i++){
      if(compare(v->v[size-1],v->v[i])<0){
        void* auxiliar = v->v[size-1];
        v->v[size-1] = v->v[i];
        v->v[i] = auxiliar;
      }
    }
  }
}

/**
 * @brief version of the insert sort
 * 
 * @param v 
 * @param compare 
 */
void vector_insert_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(15)\n");
    return;
  }
  for(int i=1;i<v->size;i++){
    if(compare(v->v[i],v->v[i-1])<0){
      int j = i-1;
      void* auxiliar = v->v[j+1];
      while(j>=0 && compare(auxiliar,v->v[j])<0){
        v->v[j]=v->v[j+1];
        j--;
      }
      v->v[j+1]=auxiliar;
    }
  }
}

/**
 * @brief version of the bubble sort.
 * 
 * @param v 
 * @param compare 
 */
void vector_bubble_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(16)\n");
    return;
  }
  int size = v->size;
  for(;size>0;size--){
    for(int i=1;i<size;i++){
      if(compare(v->v[i],v->v[i-1])<0){
        void* auxiliar  = v->v[i];
        v->v[i]=v->v[i-1];
        v->v[i-1]=auxiliar;
      }
    }
  }
}

/**
 * @brief improved version of the select sort.
 * 
 * @param v 
 * @param compare 
 */
void vector_bubble_sort_improved(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(17)\n");
    return;
  }
  int size = v->size;
  int check = 1;
  while(check==1 && size>0){
    check = 0;
    for(int i=1;i<size;i++){
      if(compare(v->v[i-1],v->v[i])>0){
        void* auxiliar  = v->v[i];
        v->v[i]=v->v[i-1];
        v->v[i-1]=auxiliar;
        check = 1;
      }
    }
    size--;
  }
}

/**
 * @brief version of the quick sort.
 * 
 * @param v 
 * @param compare 
 */
void vector_quick_sort(vector_t* v,int(*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(18)\n");
    return;
  }
  _quick_sort(&v->v[0],&v->v[v->size-1],compare);
}

void _quick_sort(void** start,void** end,int(*compare)(void*,void*)){
  if(start<end){
    void** left = start;
    void** right = end;
    void* aux = *left;
    while(left<right){
      while((left<right) && (compare(aux,*right)<0)){
        right--;
      }
      if(left<right){
        *left = *right;
        left++;
      }
      while((left<right) && (compare(aux,*left)>0)){
        left++;
      }
      if(left<right){
        *right=*left;
        right--;
      }
    }
    *left = aux;
    _quick_sort(start,left-1,compare);
    _quick_sort(left+1,end,compare);
  }
}

/**
 * @brief version of the merge sort.
 * 
 * @param v 
 * @param compare 
 */
void vector_merge_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(19)\n");
    return;
  }
  merge_sort(v,0,v->size-1,compare);
}

void merge_sort(vector_t* v,int bottom,int top,int(*compare)(void*,void*)){
  if(bottom < top){
    int middle = round((bottom+top)/2);
    merge_sort(v,bottom,middle,compare);
    merge_sort(v,middle+1,top,compare);
    _merge(v,bottom,middle,top,compare);
  }
}

void _merge(vector_t* v,int bottom,int middle,int top,int(*compare)(void*,void*)){
  int size_1 = middle-bottom+1;
  int size_2 = top-middle;
  void* array_left[size_1];
  void* array_right[size_2];
  for(int i=0;i<size_1;i++){
    array_left[i]=v->v[bottom+i];
  }
  for(int j=0;j<size_2;j++){
    array_right[j]=v->v[middle+1+j];
  }
  int i=0;
  int j=0;
  int k=bottom;
  while(i<size_1 && j<size_2){
    if(compare(array_left[i],array_right[j])<=0){
      v->v[k]=array_left[i];
      i++;
    }
    else{
      v->v[k]=array_right[j];
      j++;
    }
    k++;
  }
  while (i < size_1) {
    v->v[k]=array_left[i];
    i++;
    k++;
  }
  while (j < size_2) {
    v->v[k]=array_right[j];
    j++;
    k++;
  }
}

/**
 * @brief version of the shell sort.
 * 
 * @param v 
 * @param compare 
 */
void vector_shell_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(20)\n");
    return;
  }
  for(int interval = v->size/2;interval > 0;interval /= 2){
    for (int i = interval; i < v->size; i += 1) {
      void* auxiliar = v->v[i];
      int j;
      for (j = i; j >= interval && compare(v->v[j-interval],auxiliar) > 0; j -= interval) {
        v->v[j]=v->v[j-interval];
      }
      v->v[j]=auxiliar;
    }
  }
}

/*******************SEARCH ALGORITHMS********************************************/

/**
 * @brief version of the sequential search.Return the position of the element if it exist and 
 * the max size otherwise.
 * 
 * @param v 
 * @param value 
 * @param compare 
 * @return int 
 */
int vector_sequential_search(vector_t* v,void* value,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(21)\n");
    exit(EXIT_FAILURE);
  }
  int returned = 0;
  while(returned<v->size && compare(v->v[returned],value)){
    returned++;
  }
  return returned;
}

/**
 * @brief version of the binary search. The vector must be sorted.
 * Return the position of the element if it exist and 
 * the max size otherwise.
 * 
 * @param v 
 * @param value 
 * @param compare 
 * @return int 
 */
int vector_binary_search(vector_t* v,void* value,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("\nvector pointer is NULL(22)\n");
    exit(EXIT_FAILURE);
  }
  int lower = 0;
  int higher = v->size-1;
  int returned = (lower+higher)/2;
  while(lower < higher && compare(v->v[returned],value)){
    if(compare(v->v[returned],value)<0){
      lower = returned + 1;
    }
    else{
      higher = returned - 1;
    }
    returned = (lower+higher)/2;
  }
  return (!compare(v->v[returned],value))? returned:v->size;
}


/**
 * @brief traverse the vector using a context variable.
 * 
 * @param v 
 * @param vector_do 
 * @param context 
 */
void vector_traverse(vector_t* v,bool vector_do(void* element,void* context),void* context){
  if(v == NULL){
    printf("\nvector pointer is NULL(23)\n");
    return;
  }
  int counter = 0;
  while(counter < v->size  && vector_do(v->v[counter],context)){
    counter++;
  }
}
