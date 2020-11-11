#ifndef BINARY_SEARCH_Tree
#define BINARY_SEARCH_Tree
#include <iostream>

using namespace std;
/*
TAREA 2 ANALISIS DE ALGORITMOS Y ESTRUCTURAS DE DATOS
HECHO POR: SEBASTIAN MONTERO CASTRO
ALGORITMO SACADO DE "Introduction to Algorithms" por Thomas H. Cormen et al.
*/
// Nodos del arbol:
template <typename T>
class node{
   public:
		// Esta clase es usada por otras clases.
		// Para mayor eficiencia, los atributos se hacen publicos.
		T key;
		node<T> *p, *left, *right;

		// Constructor por omision
		node(){
			this->key, this->p, this->left, this->right = NULL;
		};
		
        // Inicializacion de datos miembro
		node(const T& k, node<T> *w = NULL, node<T> *y = NULL, node<T> *z = NULL):key(k), p(w), left(y), right(z){};
		
		~node(){
		}
};

// Arbol:
template <typename T>
class tree{
	public:
		tree(){
			root = NULL;
		};
			// Constructor. Crea un arbol vacio

		tree(const tree<T>& obj){
			copiarArbol(this->root,obj.getRoot());
		};
			// Constructor copia

		~tree(){
			destructorArbolRec(this->root);
		};
			// Destructor (borra el arbol)
			
		void inorderTreeWalk(node<T>* x){
			if(x){
				inorderTreeWalk(x->left);
				cout << x->key<< endl;
				inorderTreeWalk(x->right);
			}
		};

            // Efectua un recorrido en orden del sub�rbol cuya raiz es apuntada
            // por x, imprimiendo en cada visita la llave de cada nodo.
		
		node<T>* treeSearch(const T& k){
			return treeSearchRec(this->root,k);
		};
			// Busca la llave recursivamente; si la encuentra, devuelve un 
            // apuntador al nodo que la contiene, sino devuelve NULL
			
		node<T>* iterativeTreeSearch(const T& k){
			node<T> * nodoActual = this->root;
			while(nodoActual != NULL && k != nodoActual->key){
				if(k < nodoActual->key){
					nodoActual = nodoActual->left;
				}
				else{
					nodoActual = nodoActual->right;
				}
			}
			return nodoActual;
		};
			// Lo mismo que en el anterior pero usando un procedimiento 
			// iterativo
			
		node<T>* treeMinimum(){
			node<T> * nodo = this->root;
			while(nodo->left != NULL){
				nodo = nodo->left;
			}
			return nodo;
		};
			// Devuelve el nodo que tiene la llave menor.
            // Si el arbol est� vacio devuelve NULL.

		node<T>* treeMaximum(){
			node<T> * nodo = this->root;
			while(nodo->right != NULL){
				nodo = nodo->right;
			}
			return nodo;
		};
			// Devuelve el nodo que tiene la llave mayor.
            // Si el arbol esta vacio devuelve NULL.

		node<T>* treeSuccessor(const node<T>* x){
			node<T> nodo = NULL;
			if(x->right != NULL){
				nodo = treeMinimumParameter(x);
			}
			else{
				nodo = x->p;
				while(nodo != NULL && x == nodo->right){
					x = nodo;
					nodo = nodo->p;
				}
			}
			return nodo;
		};
			// Devuelve el nodo cuya llave es la que le sigue a la
            // del nodo x. Si no existe tal nodo devuelve NULL.

		void treeInsert(node<T>* z){
			node<T> * y = NULL;
			node<T> * x = this->root;
			while(x != NULL){
				y = x;
				if(z->key < x->key){
					x = x->left;
				}
				else{
					x = x->right;
				}
			}
			z->p = y;
			if(y == NULL){
				this->root = z;
			}
			else if(z->key < y->key){
				y->left = z;
			}
			else{
				y->right = z;
			}
		};
		// Inserta el nodo z en la posicion que le corresponde en el arbol.
			
		node<T>* treeDelete(node<T>* z){
			if(z->left == NULL){
				transplant(z,z->right);
			}
			else if(z->right == NULL){
				transplant(z,z->left);
			}
			else{
				node<T> * nodo = treeMinimumParameter(z->right);
				if(nodo->p != z){
					transplant(nodo,nodo->right);
					nodo->right = z->right;
					nodo->right->p = nodo;
				}
				transplant(z,nodo);
				nodo->left = z->left;
				nodo->left->p = nodo;
			}
		};
			// Saca del arbol la llave contenida en el nodo apuntado por z.
			// Devuelve la direccion del nodo eliminado para que se pueda 
			// disponer de ella.
	
		node<T> * getRoot() const{
			return this->root;
		};
		// Devuelve la raiz del arbol. (Para efectos de revisi�n de la tarea).
	
	private:
		node<T> *root;	// root of the Tree
		node<T> * treeSearchRec(node<T> * nodo, const T& k){
			node<T> * nodoEncontrado = NULL;
			if(nodo == NULL || k == nodo->key){
				nodoEncontrado = nodo;
			}
			else if(k < nodo->key){
				nodoEncontrado = treeSearchRec(nodo->left,k);
			}
			else{
				nodoEncontrado = treeSearchRec(nodo->right,k);
			}
			return nodoEncontrado;
		}
		node<T> * treeMinimumParameter(node<T> * nodo){
			while(nodo->left != NULL){
				nodo = nodo->left;
			}
			return nodo;
		};
		node<T> * treeMaximumParameter(node<T> * nodo){
			while(nodo->right != NULL){
				nodo = nodo->right;
			}
			return nodo;
		};
		void transplant(node<T> * u, node<T> * v){
			if(u->p == NULL){
				this->root = v;
			}
			else if(u == u->p->left){
				u->p->left = v;
			}
			else{
				u->p->right = v;
			}
			if(v != NULL){
				v->p = u->p;
			}
		}
		void destructorArbolRec(node<T> * nodo){
			if(nodo != NULL){
				destructorArbolRec(nodo->right);
				destructorArbolRec(nodo->left);
				delete nodo;
			}
		}
		void copiarArbol(node<T> * &nodoDestino, node<T> * nodoACopiar){
			if(nodoACopiar == NULL){
				nodoDestino = NULL;
			}
			else{
				node<T> nodoDestino = new node<T>;
				nodoDestino->key = nodoACopiar->key;
				copiarArbol(nodoDestino->left,nodoACopiar->left);
				copiarArbol(nodoDestino->right,nodoACopiar->right);
				copiarArbol(nodoDestino->p,nodoACopiar->p);
			}
		}
};
#endif	// BINARY_SEARCH_Tree
