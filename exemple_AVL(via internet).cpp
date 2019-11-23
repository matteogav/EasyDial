#include <stdio.h>

typedef struct AVL{
	int dato, FB; // FB es la altura del subarbol izquierdo menos la altura del subarbol derecho
	AVL *izq, *der;
	bool borrado;
} AVL;

void rotarLL(AVL* &A){ //precond: el árbol necesita una rotacion LL
	AVL* aux = A->izq->der;
	A->izq->der = A;
	A->izq->FB = 0; 
	AVL* aux2 = A->izq;
	A->izq = aux;
	A->FB = 0;
	A = aux2;
}

void rotarRR(AVL* &A){ //precond: el árbol necesita una rotacion RR
	AVL* aux = A->der->izq;
	A->der->izq = A;
	A->der->FB = 0; 
	AVL* aux2 = A->der;
	A->der = aux;
	A->FB = 0;
	A = aux2;
}


void rotarLRalter(AVL* &A){ //precond: el árbol necesita una rotacion LR
	rotarRR(A->izq);
	rotarLL(A);
}

void rotarRLalter(AVL* &A){ //precond: el árbol necesita una rotacion RL
	rotarLL(A->der);
	rotarRR(A);
}

AVL* Crear(){
	return NULL;
}

void Insert(int n, bool &aumento, AVL* &A){
	if (A == NULL){
		A = new AVL;
		A->dato = n;
		A->FB = 0;
		A->izq = NULL;
		A->der = NULL;
		aumento = true;
		A->borrado = false;
	}else{
		if (n < A->dato){			
			Insert(n, aumento, A->izq);			
			if (aumento){
				switch (A->FB){
					case -1:{
						A->FB = 0;
						aumento = false;
						break;
					}
					case 0:{
					    A->FB = 1;
						aumento = true;
						break;
					}
					case 1:{
						if (A->izq->FB == 1){ // Si es 1 necesita una rotacion LL si es -1 necesita una rotacion LR
							rotarLL(A);
						}else{
							rotarLRalter(A);
						}
						aumento = false;
						break;
					}
				}
			}
		}else{
			Insert(n, aumento, A->der);			
			if (aumento){
				switch (A->FB){
					case -1:{
						if (A->der->FB == 1){ // Si es 1 necesita una rotacion RL si es -1 necesita una rotacion RR
							rotarRLalter(A);
						}else{
							rotarRR(A);
						}
						aumento = false;						
						break;
					}
					case 0:{
						A->FB = -1;
						aumento = true;
						break;
					}
					case 1:{
						A->FB = 0;
						aumento = false;
						break;
					}
				}
			}
		}
	}
}

void Insertar(AVL* &A, int n){
	bool aumento;
	Insert(n, aumento, A);
}

bool EsVacio(AVL* A){
	return A == NULL;
}

bool Pertenece(AVL* A, int n){
	if (A == NULL){
		return false;
	}else{
		if (A->dato == n){
			if (A->borrado){
				return false;
			}else{
				return true;
			}
		}else if (n < A->dato){		
			return Pertenece(A->izq, n);
		}else{
			return Pertenece(A->der, n);
		}		
	}
}

void Borrar(AVL* &A, int n){
	if (A->dato == n){
		A->borrado = true;
	}else if (n < A->dato){		
		Borrar(A->izq, n);
	}else{
		Borrar(A->der, n);
	}
}
