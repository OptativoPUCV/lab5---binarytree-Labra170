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


void insertTreeMap(TreeMap * tree, void* key, void * value) // Función 3. Para insertar en el árbol
{
  if (searchTreeMap(tree, key) != NULL)
  {
    return;
  }
  
  TreeNode * newNode = createTreeNode(key, value);
  if (newNode == NULL)
  {
    exit(EXIT_FAILURE);
  }

  if (tree->root == NULL)
  {
    tree->root = newNode;
    tree->current = newNode;
    return;
  }

  TreeNode * current = tree->root;
  TreeNode * parent = NULL;
  
  while (current != NULL)
    {
      int rComparacion = tree->lower_than(key, current->pair->key);

      if (rComparacion > 0)
      {
        parent = current;
        current = current->left;
      }
      else
      {
        parent = current;
        current = current->right;
      }
    }

  newNode->parent = parent;

  if (tree->lower_than(key, parent->pair->key) > 0)
  {
    parent->left = newNode;
  }
  else
  {
    parent->right = newNode;
  }
  
  tree->current = newNode;
}

TreeNode * minimum(TreeNode * x) // Función 4. Para buscar el valor mínimo del árbol.
{
  if (x == NULL)
  {
    return NULL;
  }
  while (x->left != NULL)
    {
      x = x->left;
    }
  return x;
}

void removeNode(TreeMap * tree, TreeNode* node) // Función 5. Borrar un nodo del árbol.
{
  if (node == NULL)
  {
    return;
  }

  TreeNode * parent = node->parent;

  if (node->left == NULL && node->right == NULL) // Sin hijos.
  {
    if (parent == NULL) // Si no tiene padre, es decir, es la raíz, se elimina directamente.
    {
      free(node);
      tree->root = NULL;
    }
    else
    {
      if (parent->left == node)
      {
        parent->left = NULL;
      }
      else
      {
        parent->right = NULL;
      }
      free(node);
    }
  }

  else if (node->left != NULL && node->right != NULL)
  {
    TreeNode * minimumNode = minimum(node->right);

    node->pair->key = minimumNode->pair->key;
    node->pair->value = minimumNode->pair->value;

    removeNode(tree, minimumNode);
  }
  else
  {
    TreeNode * hijo = (node->left != NULL) ? node->left : node->right;

    if (parent == NULL)
    {
      tree->root = hijo;
      hijo->parent = NULL;
    }
    else
    {
      if (parent->left == node)
      {
        parent->left = hijo;
      }
      else
      {
        parent->right = hijo;
      }
      hijo->parent = parent;
    }
    free(node);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) // Función 2. Buscar en el árbol.
{
  TreeNode *current = tree->root;

    while (current != NULL) {
        int cmp = tree->lower_than(key, current->pair->key);

        if (cmp == 0) {
            // Se encontró la clave, actualiza 'current' y retorna el Pair asociado
            tree->current = current;
            return current->pair;
        } else if (cmp < 0) {
            // Si la clave buscada es menor, busca en el subárbol izquierdo
            current = current->left;
        } else {
            // Si la clave buscada es mayor, busca en el subárbol derecho
            current = current->right;
        }
    }

    // La clave no se encontró en el árbol
    tree->current = NULL;
    return NULL;
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
