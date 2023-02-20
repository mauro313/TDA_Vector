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
  
  // creation of an int vector.
  vector_t* new = vector_int(15);
 
  //print the vector
  vector_printf(new,print_int);
  
  //sort the vector.
  vector_merge_sort(new,compare_int);
  
  //print again the vector.
  printf("\n\n");
  vector_printf(new,print_int);
   
  //delete the repeated elements and print again.
  vector_delete_all_repeated_elements(new,compare_int,delete_int_pointer);
  printf("\n\n");
  vector_printf(new,print_int);
   
  // using vector_traverse.
  int amountOfEven = 0;
  vector_traverse(new,vector_amountOfEven,&amountOfEven);
  printf("The amount of even numbers is %d ",amountOfEven);

  //delete the vector and free memory.
  vector_int_delete(&new,delete_int_pointer);
  return 0;      
}

/***************EXAMPLE OF USE OF THE TDA*********************************/

/**
 * @brief create a int vector.
 * 
 * @param value 
 * @return vector_t* 
 */
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

/**
 * @brief erase all the elements in a vector and the vector.
 * 
 * @param vector 
 * @param delete 
 */
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

/**
 * @brief auxiliar procedure to free memeory of a int pointer.
 * 
 * @param pointer 
 */
void delete_int_pointer(void** pointer){
  if(pointer != NULL){
    free(*pointer);
    *pointer = NULL;
  }
}

/**
 * @brief auxiliar procedure to print a int pointer.
 * 
 * @param value 
 */
void print_int(void* value){
  printf(" %i ",*(int*)value);        
}

/**
 * @brief auxiliar compare procedure.
 * 
 * @param value_1 
 * @param value_2 
 * @return int 
 */
int compare_int(void* value_1,void* value_2){
  int* v1 = value_1;
  int* v2 = value_2;
  return (*v1)-(*v2);  
}

/**
 * @brief delete al repeated elements in a vector.
 * 
 * @param vector 
 * @param compare 
 * @param free_element 
 */
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


/**
 * @brief fusion two sort vectors in a new one without repeated elements.
 * 
 * @param vector1 
 * @param vector2 
 * @param compare 
 * @return vector_t* 
 */
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


/**
 * @brief function used in vector_traverse.Return true if the element is even and false otherwise.
 * 
 * @param element 
 * @param context 
 * @return true 
 * @return false 
 */
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