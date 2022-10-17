#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vector.h"

vector_t* vector_int(int value);
void vector_int_delete(vector_t** vector,void (*delete)(void**));
void delete_int_pointer(void** pointer);
void print_int(void* value);
int compare_int(void* value_1,void* value_2);
void vector_delete_all_repeated_elements(vector_t* vector,int(*compare)(void*,void*),void(*free_element)(void**));

int main(void){
  //creo un vector de enteros
  vector_t* new = vector_int(30);
  
  //imprimo el vector
  vector_printf(new,print_int);
  
  //ordeno los elementos
  vector_merge_sort(new,compare_int);
  
  //vuelvo a imprimirlos
  printf("\n\n");
  vector_printf(new,print_int);
   
  //elimino los elementos repetidos y vualvo a imprimirlo 
  vector_delete_all_repeated_elements(new,compare_int,delete_int_pointer);
  printf("\n\n");
  vector_printf(new,print_int);

  //elimino el vector con sus elementos
  vector_int_delete(&new,delete_int_pointer);

  return 0;      
}

/***************Ejemplos de uso del tipo abstracto de dato*********************************/

//funcion para crear un vector de punteros a enteros
vector_t* vector_int(int value){
  vector_t* vector = vector_new(value);
  srand(time(NULL));
  int* auxiliar = NULL;
  while(!vector_isfull(vector)){
    auxiliar = (int*)malloc(sizeof(int));
    *auxiliar = rand()%30;
    vector_add(vector,auxiliar);  
  }
  return vector;      
}

//procedimiento para borrar un vector y sus elementos (forma genérica)
void vector_int_delete(vector_t** vector,void (*delete)(void**)){
  if(*vector != NULL){
    void* auxiliar = NULL;
    while(!vector_isempty(*vector)){
      auxiliar = vector_remove(*vector,0);
      delete(&auxiliar);
    }
    vector_free(vector);
  } 
}

void delete_int_pointer(void** pointer){
  if(pointer != NULL){
    free(*pointer);
    *pointer = NULL;
  }
}

void print_int(void* value){
  printf(" %i ",*(int*)value);        
}

int compare_int(void* value_1,void* value_2){
  int* v1 = value_1;
  int* v2 = value_2;
  return (*v1)-(*v2);  
}

void vector_delete_all_repeated_elements(vector_t* vector,int(*compare)(void*,void*),void(*free_element)(void**)){
  for(int i=0;i<vector_size(vector);i++){
    for(int j=i+1;j<vector_size(vector);j++){
      if(compare(vector_get(vector,i),vector_get(vector,j))==0){
        void* auxiliar = vector_remove(vector,j);
        free_element(&auxiliar);
        j--;  
      }      
    }  
  }     
}


