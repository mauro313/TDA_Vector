#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Vector.h"

// Crea el vector vacío a parir de la reserva en memoria. Tamaño = 0, Tamaño máximo = ini_size.
vector_t* vector_new(int maxsize){
  vector_t* vector = (vector_t*) malloc(sizeof(vector_t));
  if(vector == NULL){
    printf("memory cannot be reserved");
    exit(-1);
   }
  vector->v =(void**)malloc(maxsize*sizeof(void*));
  if(vector->v == NULL){
    free(vector);
    vector = NULL;
    printf("memory cannot be reserved(1)");
    exit(-2);
  }
  vector->size = 0;
  vector->max_size = maxsize;  
  return vector;
}

// Libera la memoria del vector
void vector_free(vector_t** v){
  if(v != NULL && (*v) != NULL){
    free((*v)->v);
    (*v)->v = NULL;
    free(*v);
    *v = NULL;
  }
}

//Retorna el tamaño actual del vector
int vector_size(vector_t* v){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-3);  
  }
  return v->size;
}

//Retorna el tamaño máximo que puede tener el vector
int vector_maxsize(vector_t* v){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-4);  
  }
  return v->max_size;  
}

// Devuelve false si no está lleno y true si está lleno.
bool vector_isfull(vector_t* v){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-5);  
  }
  bool returned = false;
  if(v->size == v->max_size){
    returned = true;
  }
  return returned;
}

// Devuelve false si no está vacío y true si está vacío.
bool vector_isempty(vector_t* v){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-6);  
  }
  bool returned = false;
  if(v->size == 0){
    returned = true;
  }
  return returned;
}

// Retorna el valor de una posición del vector.
void* vector_get(vector_t* v,int index){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-7);
  }
  if(index<0 || index>=v->size){
    printf("invalid index");
    exit(-8);  
  }
  return v->v[index];
}

// Permite reemplazar el valor de una posición del vector(devuelve el valor reemplazado).
//En caso contrario retorna NULL
void* vector_set(vector_t* v,int index,void* value){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-9);  
  }
  if(index<0 || index>=v->size){
    printf("invalid index");
    exit(-10);  
  }
  void* returned = v->v[index];
  v->v[index] = value;
  return returned;
}

// Permite agregar un elemento al final.Retorna 1 si el valor se insertó y 0 en caso contrario
int vector_add(vector_t* v,void* value){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-11);  
  }
  int returned = 0; 
  if(!vector_isfull(v)){
    v->v[v->size] = value;
    v->size++;
    returned = 1;
  }
  return returned;
}

//Permite agregar un elemento al inicio.Retorna 1 si el valor se insertó y 0 en caso contrario
int vector_add_first(vector_t* v, void* value){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-12);  
  }
  int returned = 0;
  if(!vector_isfull(v)){
    v->size++;
    for(int i=v->size-1;i=1;i--){
      v->v[i] = v->v[i-1];    
    }
    v->v[0] = value;
    returned = 1;      
  }
  return returned;
}

// Permite agregar un elemento en una posición determinada.Retorna 1 si lo agrego y 0 en caso contrario(vector lleno).
int vector_insert(vector_t* v,int index,void* value){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-13);  
  }
  if(index<0 || index>v->size){
    printf("invalid index");
    exit(-14);  
  }
  int returned = 0;
  if(!vector_isfull(v)){
    v->size++;
    for(int i=v->size-1;i>index;i--){
      v->v[i] = v->v[i-1];    
    }
    v->v[index] = value;
    returned = 1;
  }
  return returned;
}

//Permite insertar elementos de manera ordenada. Retorna 1 si se agrego el valor y 0 en caso contrario(vector lleno).
int vector_insert_sorted(vector_t* v,void* value,int(*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-15);  
  }
  int returned = 0;
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
    returned = 1;
  }
  return returned;  
}

// Permite eliminar un elemento del vector. Retorna dicho elemento. 
void* vector_remove(vector_t* v,int index){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-16);  
  }
  if(index<0 || index>=v->size){
    printf("invalid index");
    exit(-17);  
  }
  void* returned = v->v[index];
  v->size--;
  for(int i=index;i<v->size;i++){
    v->v[i] = v->v[i+1];
  }
  return returned;
}


//Imprime el contenido de un vector
void vector_printf(vector_t* v,void (*printf_)(void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-18);  
  }
  for(int i=0;i<v->size;i++){
    printf_(v->v[i]);
  }
}

//Desordena los elementos de un vector
void vector_shuffle(vector_t* v){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-19);  
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

/********************ALGORITMOS DE ORDENAMIENTO***************************************/

//Ordenamiento por seleccion
//La base del algoritomo radica en elegir el elemento más pequeño del arreglo e
// intercambiarlo por el primero, luego se repite el proceso desde el seguno elemento
void vector_select_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-20);  
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

//Ordenamiento por insercion
//Se recorre el arreglo desde el comienzo y cuando se encuentra un elemento menor que el actual
// se lo quita del arreglo y se retrocede hasta insertarlo en el lugar correcto.
void vector_insert_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-21);  
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

//Ordenamiento por burbujeo
//Se recorre el arreglo desde el comienzo, se comparan dos celdas contiguas, si no estan
//ordenadas en forma continua, las intercambia.
//Se repite el proceso n-1 veces, hasta que n = 1. 
void vector_bubble_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-22);  
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

//Ordenamiento por burbujeo mejorado(Se evitan recorridos innecesarios.Se reduce complejidad)
void vector_bubble_sort_improved(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-23);  
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

// Algoritmo de ordenamiento quick sort (inestable).Emplea la recursividad. Tiene el enfoque de dividir y conquistar.
void vector_quick_sort(vector_t* v,int(*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-24);  
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

//algoritmo de ordenamiento merge sort (estable).Emplea la recursividad. Tiene el enfoque de dividir y conquistar
void vector_merge_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-25);  
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

//Algoritmo de ordenamiento shell sort (forma mejorada del algoritmo insertion sort)
void vector_shell_sort(vector_t* v,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-26);  
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

/*******************ALGORITMOS DE BUSQUEDA********************************************/

int vector_sequential_search(vector_t* v,void* value,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-27);  
  }  
  int returned = 0;
  while(returned<v->size && compare(v->v[returned],value)){
    returned++;  
  }
  return returned;
}

// el vector debe encontrarse ordenado para emplear este algoritmo
int vector_binary_search(vector_t* v,void* value,int (*compare)(void*,void*)){
  if(v == NULL){
    printf("vector pointer is NULL");
    exit(-28);  
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


// Procedimiento para recorrer un vector y realiar un procedimiento al mismo tiempo empleando una variable de contexto.
void vector_traverse(vector_t* v,bool vector_do(void* element,void* context),void* context){
  if(v == NULL){
    printf("vector is NUll");
    exit(-29);  
  }
  int counter = 0;
  while(counter < v->size  && vector_do(v->v[counter],context)){
    counter++;  
  }
}
