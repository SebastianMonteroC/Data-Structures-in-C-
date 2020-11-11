#ifndef LINKED_LIST_llist
#define LINKED_LIST_llist
#include <iostream>
using namespace std;
/*
TAREA 2 ANALISIS DE ALGORITMOS Y ESTRUCTURAS DE DATOS
HECHO POR: SEBASTIAN MONTERO CASTRO
ALGORITMO SACADO DE "Introduction to Algorithms" por Thomas H. Cormen et al.
*/

// Nodos de la lista:
template <typename T>
class llnode{
   public:
		// Esta clase es para ser usada por otras clases.
		// Por eficiencia los atributos se dejan publicos.
		T key;
		llnode<T> *prev, *next;
		//enum colors color;

		// Constructor por omision.
		llnode(){
		};
		
      	// Inicializacion de los datos miembro.
		llnode (const T& k, llnode<T> *w = NULL, llnode<T> *y = NULL):key(k), prev(w), next(y) {
		};
		
		~llnode(){

		}
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist{
	public:
		llist(){
			nil = new llnode<T>;
			nil->next = nil;
			nil->prev = nil;
		};
			// Constructor (crea una lista vacia)

		llist(const llist<T>& obj){ 
		};
			// Constructor copia

		~llist(){
			llnode<T> * x = nil->next;
			while(x != nil){
				//cout << "Se esta borrando el elemento " << x->key << endl;
				x = x->next;
				listDelete(x->prev);
			}
			//printLista();
		};
			// Destructor (borra la lista)
					
		llnode<T>* listSearch(const T& k){
			llnode<T>* x = nil->next;
			while(x != nil && x->key != k){
				x = x->next;
			}
			return x;
		};
			// Busca la llave iterativamente. Si la encuentra, devuelve un 
            // apuntador al nodo que la contiene; sino devuelve NULL.
			
		void listInsert(llnode<T>* x){
			x->next = nil->next;
			nil->next->prev = x;
			nil->next = x;
			x->prev = nil;
			//printLista();
		};
			// Inserta el nodo x en la lista.
	
		llnode<T>* listDelete(llnode<T>* x){
			x->prev->next = x->next;
			x->next->prev = x->prev;
			return x;
		};
			// Saca de la lista la llave contenida en el nodo apuntado por x.
			// Devuelve la direccion del nodo eliminado para que se pueda 
			// disponer de el.
				
		llnode<T> * getNil() const{
			return this->nil;
		};
		// Devuelve el nodo centinela. (Para efectos de revision de la tarea).
		
		private:
			llnode<T> *nil;	    // nodo centinela
			void printLista(){
				llnode<T> *x = nil->next;
				while(x != nil){
					std::cout << x->key << " -> ";
					x = x->next;
				}
				std::cout << "FIN" << std::endl;
			}

};

#endif	// LINKED_LIST_llist
