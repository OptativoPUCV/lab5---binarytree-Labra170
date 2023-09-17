#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) // Función 1. Crear el árbol.
{
  TreeMap * map = (TreeMap *) malloc(sizeof(TreeMap)); // Se asigna memoria al mapa.

  if (map == NULL) // Si no se pudo asignar memoria
  { // Entonces
    exit(EXIT_FAILURE); // El programa finaliza en fallo.
  }

  map->root = NULL; // La raíz, se establece/inicializa en NULL.
  map->current = NULL; // El puntero actual, se establece/inicializa en NULL.
  map->lower_than = lower_than; // Se copia la función.
  
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) // Función 3
{
  
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) // Función 2. Buscar en el árbol.
{
  TreeNode * current = tree->root; // El current se mueve a la raíz del arbol.
  int rComparacion = tree->lower_than(key, current->pair->key); 
  // Como la función regresa un entero por ser de comparación, se usa para ver a que lado ir.

  while (current != NULL) // Mientras haya elementos para "analizar"
    { // Entonces
      if (rComparacion == 0) // Si es el valor buscado
      {
        tree->current = current; // Se actualiza el puntero
        return current->pair; // Se retorna el par.
      }
      else if (rComparacion < 0) // Si es menor
      {
        current = current->left; // Se sigue por la izquierda.
      }
      else // Si no
      {
        current = current->right; // Se sigue por la derecha.
      }
    }

  tree->current = NULL; // Si no se encuentra la clave, se establece en NULL.
  return NULL; // Como no se encontró, se retorna NULL.
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
