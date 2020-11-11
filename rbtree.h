#ifndef RED_BLACK_rbtree
#define RED_BLACK_rbtree
#include <stack>

using namespace std;

enum colors {RED, BLACK};

/*
TAREA 2 ANALISIS DE ALGORITMOS Y ESTRUCTURAS DE DATOS
HECHO POR: SEBASTIAN MONTERO CASTRO
ALGORITMO SACADO DE "Introduction to Algorithms" por Thomas H. Cormen et al.
*/

// Nodos del arbol:
template <typename T>
class rbnode{
   public:
		// Esta clase es para ser usada por otras clases.
		// Por eficiencia se hacen los atributos publicos.
		T key;
		rbnode<T> *p, *left, *right;
		enum colors color;

		// Constructor por omision.
		rbnode(){
			this->color = RED;
		};
		
      	//Inicializacion de datos miembro.
		rbnode (const T& k, rbnode<T> *w = NULL, rbnode<T> *y = NULL, 
				 rbnode<T> *z = NULL, enum colors c = RED):
					key(k), p(w), left(y), right(z), color(c)
		{};
		
		~rbnode(){
		}
};

// Arbol:
template <typename T>
class rbtree{
	public:

		// Constructor (crea un arbol vacio)
		rbtree(){
			this->nil = new rbnode<T>();
			this->nil->color = BLACK;
			this->root = this->nil;

		};
			
		// Constructor copia (no es necesario para la tarea)
		rbtree(const rbtree<T>& obj){ 
		};
			
		// Destructor (borra el arbol)
		~rbtree(){
			borrarArbol(this->root);
		};
		
		// Efectua un recorrido en orden del subarbol cuya ra�z es apuntada
        // por x. En cada visita apila la llave de cada nodo y su color.
        // Es decir, cada vez que se llega a un nodo se ejecutan las 
        // instrucciones pila.push(x->key); y luego pila.push(colorDeX).
        // Para efectos de la tarea, si el color del nodo es rojo, 
        // ponga en la pila un 0, y si es negro, ponga un 1.
        // Si se hace correctamente, al finalizar el m�todo la pila deber�a 
        // contener las llaves de los nodos del sub�rbol (y su color) 
        // ordenadas de mayor a menor.	
		void inorderTreeWalk(rbnode<T>* x){
			if(x != this->nil){
				inorderTreeWalk(x->left);
				cout << x->key << " - " << ((x->color == RED) ? "Rojo" : "Negro") << endl;
				inorderTreeWalk(x->right);
			}
		};
            
		// Busca la llave recursivamente, si la encuentra devuelve un 
        // puntero al nodo que la contiene, sino devuelve NULL.
		rbnode<T>* treeSearch(const T& k){
			return treeSearchRec(this->root,k);
		};
			
		// Igual que en el anterior pero usa un procedimiento iterativo.
		rbnode<T>* iterativeTreeSearch(const T& k){
			rbnode<T> * nodoActual = this->root;
			while(nodoActual != nil && k != nodoActual->key){
				if(k < nodoActual->key){
					nodoActual = nodoActual->left;
				}
				else{
					nodoActual = nodoActual->right;
				}
			}
			return nodoActual;
		};
			
		// Devuelve el nodo con la llave menor.
        // Si el arbol esta vacio devuelve NULL.	
		rbnode<T>* treeMinimum(){
			rbnode<T> * nodo = this->root;
			while(nodo->left != nil){
				nodo = nodo->left;
			}
			return nodo;
		};
			
		// Devuelve el nodo con la llave mayor.
        // Si el arbol esta vacio devuelve NULL.
		rbnode<T>* treeMaximum(){
			rbnode<T> * nodo = this->root;
			while(nodo->right != nil){
				nodo = nodo->right;
			}
			return nodo;
		};
			
		// Devuelve el nodo cuya llave es la siguiente mas grande que 
        // la del nodo x. Si no existe tal nodo devuelve NULL.
		rbnode<T>* treeSuccessor(const rbnode<T>* x){
			rbnode<T> nodo = nil;
			if(x->right != nil){
				nodo = treeMinimumParameter(x);
			}
			else{
				nodo = x->p;
				while(nodo != nil && x == nodo->right){
					x = nodo;
					nodo = nodo->p;
				}
			}
			return nodo;
		};
			
		// Inserta el nodo z en la posicion que le corresponde en el arbol.
		void treeInsert(rbnode<T>* z){ //aux es y, actual es x.
			rbnode<T> * y = this->nil;
			rbnode<T> * x = this->root;
			while(x != this->nil){
				y = x;
				if(z->key < x->key){
					x = x->left;
				}
				else{
					x = x->right;
				}
			}
			z->p = y;
			if(y == this->nil){
				this->root = z;
			}
			else if(z->key < y->key){
				y->left = z;
			}
			else{
				y->right = z;
			}
			z->left = this->nil;
			z->right = this->nil;
			z->color = RED;
			insertFixup(z);
		};
			
		// Saca del arbol la llave contenida en el nodo apuntado por z.
		// Devuelve la direccion del nodo eliminado para que se pueda 
		// disponer de el.	
		rbnode<T>* treeDelete(rbnode<T>* z){
		};
			
		// Devuelve la raiz del arbol. (Para efectos de revision de la tarea).
		rbnode<T> * getRoot() const{
			return this->root;
		};
		
		// Devuelve T.nil. (Para efectos de revision de la tarea).
		rbnode<T> * getNil() const{
			return this->nil;
		};
			
	private:
	
		rbnode<T> *root;	// raiz del arbol
		rbnode<T> *nil;	    // nodo nil (hoja) del arbol
		void leftRotate(rbnode<T> * x){
			rbnode<T> * y = x->right;
			x->right = y->left;
			if(y->left != this->nil){
				y->left->p = x;
			}
			y->p = x->p;
			if(x->p == this->nil){
				this->root = y;
			}
			else if(x == x->p->left){
				x->p->left = y;
			}
			else{
				x->p->right = y;
			}
			y->left = x;
			x->p = y;
		}
		void rightRotate(rbnode<T> * x){
			rbnode<T> * y = x->left;
			x->left = y->right;
			if(y->right != this->nil){
				y->right->p = x;
			}
			y->p = x->p;
			if(x->p == this->nil){
				this->root = y;
			}
			else if(x == x->p->right){
				x->p->right = y;
			}
			else{
				x->p->left = y;
			}
			y->right = x;
			x->p = y;
		}
		void insertFixup(rbnode<T> * z){
			rbnode<T> * y;
			while(z->p->color == RED){
				if(z->p == z->p->p->left){
					y = z->p->p->right;
					if(y->color == RED){
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else{
						if(z == z->p->right){
							z = z->p;
							leftRotate(z);
						}
						z->p->color = BLACK;
						z->p->p->color = RED;
						rightRotate(z->p->p);
					}
				}
				else{
					y = z->p->p->left;
					if(y->color == RED){
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else{
						if(z == z->p->left){
							z = z->p;
							rightRotate(z);
						}
						z->p->color = BLACK;
						z->p->p->color = RED;
						leftRotate(z->p->p);
					}
				}
			}
			this->root->color = BLACK;
		}
		rbnode<T> * treeSearchRec(rbnode<T> * nodo, const T& k){
			rbnode<T> * nodoEncontrado = nil;
			if(nodo == nil || k == nodo->key){
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

		rbnode<T> * treeMinimumParameter(rbnode<T> * nodo){
			while(nodo->left != NULL){
				nodo = nodo->left;
			}
			return nodo;
		};
		void borrarArbol(rbnode<T> * nodo){
			if(nodo != this->nil && nodo != nullptr){
				borrarArbol(nodo->left);
				borrarArbol(nodo->right);
				delete nodo;
			}
		}
		
};

#endif	// RED_BLACK_rbtree
