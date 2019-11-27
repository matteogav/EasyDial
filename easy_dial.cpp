#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){

}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){

}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){

}
easy_dial::~easy_dial() throw(){

}

string easy_dial::inici() throw(){

}

string easy_dial::seguent(char c) throw(error){

}

string easy_dial::anterior() throw(error){

}

nat easy_dial::num_telf() const throw(error){

}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){

}

double easy_dial::longitud_mitjana() const throw(){
    
}
