#include "easy_dial.hpp"

easy_dial(const call_registry& R) throw(error){

}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial(const easy_dial& D) throw(error){

}
easy_dial& operator=(const easy_dial& D) throw(error){

}
~easy_dial() throw(){

}

string inici() throw(){

}

string seguent(char c) throw(error){

}

string anterior() throw(error){

}

nat num_telf() const throw(error){

}

void comencen(const string& pref, vector<string>& result) const throw(error){

}

double longitud_mitjana() const throw();
