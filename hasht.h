#ifndef HASH_CLASS
#define HASH_CLASS
#include <vector>
#include "llist.h"

using namespace std;
/*
TAREA 2 ANALISIS DE ALGORITMOS Y ESTRUCTURAS DE DATOS
HECHO POR: SEBASTIAN MONTERO CASTRO
ALGORITMO SACADO DE "Introduction to Algorithms" por Thomas H. Cormen et al.
*/
template <typename T>

class hasht{
	public:
		// Constructor que especifica el numero de cubetas (entradas) 
		// en la tabla
		hasht(int nEntradas){
			tabla.resize(nEntradas);
			for(int i=0;i<nEntradas;i++){
				tabla[i] = new llist<T>;
			}
			numEntradas = nEntradas;
		};
			
		// Destructor (borra la tabla)
		~hasht(){
			for(int i=0;i<numEntradas;i++){
				delete tabla[i];
			}
			tabla.clear();
		};
			
		// Retorna un puntero a la llave o NULL si no se encuentra
		T* search(const T& item){
			int key = item % numEntradas;
			T * buscado = &tabla[key]->listSearch(item)->key;
			return buscado;
		};
			
		// Inserta el elemento en la tabla
		void insert(const T& item){
			int key = item % numEntradas;
			tabla[key]->listInsert(new llnode<T>(item));
		};
			

	private:
		// Nœmero de entradas en la tabla
		int numEntradas;
		// La tabla es un vector de listas de STL
		vector<llist<T>*>tabla;
};
#endif
