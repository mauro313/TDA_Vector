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
vector_t* merge_of_sort_vectors(vector_t* vector1,vector_t* vector2,int (*compare)(void*,void*));
bool vector_amountOfEven(void* element,void* context);

int main(void){
  srand(time(NULL));
  //creo un vector de enteros
  vector_t* new = vector_int(15);
 
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
   
  //empleo de vector traverse
  int amountOfEven = 0;
  vector_traverse(new,vector_amountOfEven,&amountOfEven);
  printf("The amount of even numbers is %d ",amountOfEven);

  //elimino el vector con sus elementos
  vector_int_delete(&new,delete_int_pointer);
  return 0;      
}

/***************Ejemplos de uso del tipo abstracto de dato*********************************/

//funcion para crear un vector de punteros a enteros
vector_t* vector_int(int value){
  vector_t* vector = vector_new(value);
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

// procedimientos auxiliares
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
///////////////////////////////////////////



// eliminar elementos repetidos de un vector
void vector_delete_all_repeated_elements(vector_t* vector,int(*compare)(void*,void*),void(*free_element)(void**)){
  if(vector == NULL){
    printf("vector is NULL");
    return;  
  }
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

//Escribir una función que permita mezclar dos vectores ordenados sin incluir elementos repetidos.
//Tener en cuenta que la función debe servir sin importar qué datos guarden los vectores, pero
//ambos vectores deben contener los mismos tipos de datos.

vector_t* merge_of_sort_vectors(vector_t* vector1,vector_t* vector2,int (*compare)(void*,void*)){
  vector_t* new_vector = vector_new(vector_size(vector1)+vector_size(vector2));
  int counter1 = 0;
  int counter2 = 0;
  while(counter1<vector_size(vector1) && counter2<vector_size(vector2)){
    if(compare(vector_get(vector1,counter1),vector_get(vector2,counter2))<0){
      if(vector_isempty(new_vector)){
        vector_add(new_vector,vector_get(vector1,counter1));
      }
      if(!vector_isempty(new_vector) && compare(vector_get(new_vector,vector_size(new_vector)-1),vector_get(vector1,counter1))!=0){
        vector_add(new_vector,vector_get(vector1,counter1));
      }
      counter1++;
    }
    else{
      if(vector_isempty(new_vector)){
        vector_add(new_vector,vector_get(vector2,counter2));  
      }  
      if(!vector_isempty(new_vector) && compare(vector_get(new_vector,vector_size(new_vector)-1),vector_get(vector2,counter2))!=0){
        vector_add(new_vector,vector_get(vector2,counter2));
      }
      counter2++;
    }
  }
  while(counter1<vector_size(vector1)){
    if(compare(vector_get(new_vector,vector_size(new_vector)-1),vector_get(vector1,counter1))!=0){
      vector_add(new_vector,vector_get(vector1,counter1));
    }
    counter1++; 
  }
  while(counter2<vector_size(vector2)){
    if(compare(vector_get(new_vector,vector_size(new_vector)-1),vector_get(vector2,counter2))!=0){
      vector_add(new_vector,vector_get(vector2,counter2));
    }
    counter2++;
  }
  return new_vector; 
}


//funcion de ejemplo para uso de vector traverse
bool vector_amountOfEven(void* element,void* context){
  bool returned = false;
  if(element != NULL){
    if((*(int*)element)%2==0){
      (*(int*)context)++;
    }
    returned = true;
  }  
  return returned;
}