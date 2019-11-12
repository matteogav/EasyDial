#include "call_registry.hpp"
#include <vector>

call_registry() throw(error){

}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry(const call_registry& R) throw(error){

}
call_registry& operator=(const call_registry& R) throw(error){

}
~call_registry() throw(){

}

void registra_trucada(nat num) throw(error){

}

void assigna_nom(nat num, const string& name) throw(error){

}

void elimina(nat num) throw(error){

}

bool conte(nat num) const throw(){

}

string nom(nat num) const throw(error){

}

nat num_trucades(nat num) const throw(error){

}

bool es_buit() const throw(){

}

nat num_entrades() const throw(){

}

void dump(vector<phone>& V) const throw(error){

}
