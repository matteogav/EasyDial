#include "easy_dial.hpp"
#include <sstream>

void easy_dial::insereix(const phone& P){
  string s = P.nom();
  s += phone::ENDPREF;
  nat tlf = P.numero();
  nat frequen = P.frequencia();

  nat i=0;
  _arrel = rinsereix(_arrel, i, s, tlf, frequen);
}

easy_dial::node_tst* easy_dial::rinsereix(node_tst* n, nat &i, string s, nat tlf, nat frequen) throw(error){
  if(n==NULL){
    node_tst* ph = new node_tst;
    ph->_esq = ph->_dret = ph->_central = NULL;
    ph->_lletra = s[i];
    try {
      if (i < s.length()-1) n->_central = rinsereix(n->_central, i+1, s, tlf, frequen);
      else{      //NOTA: el que diu als apunts [ i == s.length()-1; s[i] == Simbol() ]  com que es ultim node li afegim tlf i freq que te
        ph->_tlf = tlf;
        ph->_freq = frequen;
      }
    }
    catch (error) {
      delete ph;
      throw;
    }
  }
  else{
    if (n->_lletra > s[i]) n->_esq = rinsereix(n->_esq, i, s, tlf, frequen);
    else if (n->_lletra < s[i]) n->_dret = rinsereix(n->_dret, i, s, tlf, frequen);
    else n->_central = rinsereix(n->_central, i+1, s, tlf, frequen);              // (n->_lletra == s[i])
  }
  return n;

}

void easy_dial::emplena_v(node_tst* n, vector<string>& result, const string& pref, nat& i, string &aux) const throw{
  /*  */
  if (n != NULL){
    if (i < pref.size()) {  // busco el prefix primer
      if (pref[i] < n->_lletra) emplena_v(n->_esq, result, pref, i, aux);
      else if (pref[i] == n->_lletra) emplena_v(n->_central, result, pref, i+1, aux);
      else if (pref[i] > n->_lletra) emplena_v(n->_dret, result, pref, i, aux);
    }
    else if (i >= pref.size()){   //recorro arbe fins a trobar \0 quan la trobo afegeixo aux al vector result
      if (n->_lletra != phone::ENDPREF){           //lletra != \0
        if (n->_esq != NULL) emplena_v(n->_esq, result, pref, i, aux);
        if (n->_central != NULL)
        {
          aux += n->_lletra;
          emplena_v(n->_central, result, pref, i, aux);
        }
        if (n->_dret != NULL) emplena_v(n->_dret, result, pref, i, aux);
      }
      else if (n->_lletra == phone::ENDPREF) {
        result.push_back(aux);
      }
      if (aux != pref) {
        aux.erase(aux.size() - 1);
      }
    }
  }
}

easy_dial::easy_dial(const call_registry& R) throw(error){

  vector<phone> v;
  R.dump(v);

  //ordenar vector per frequencia mes alta a mes baixa, he triat mergesort


  for(nat i = 0; i<v.size(); ++i) insereix(v[i]);
  _n_elem = R.num_entrades();
  _prefix="";   //el prefix en curs queda indefinit
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){

}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){

}
easy_dial::~easy_dial() throw(){

}

string easy_dial::inici() throw(){
  /* Cost constant?*/
  _prefix = "";
  string res = "";

  if (_n_elem != 0){
    node_tst* n=_arrel;
    while (n->_lletra != phone::ENDPREF){       //cost el numero de lletres que te la persona mes frequent de l'agenda
      res += n->_lletra;
      n=n->_central;
    }
  }

  return res;
}

string easy_dial::seguent(char c) throw(error){
  /* Cost constant?*/
  /* si introdueix dos cops seguit string buit, tira erro pref indef i */
  if (anterior().empty()) throw error(ErrPrefixIndef);
  string res="";
  _prefix += c;
  return res;
}

string easy_dial::anterior() throw(error){
  /* Cost constant?*/
  if (_prefix.empty()) throw error(ErrNoHiHaAnterior);
  if (anterior().empty()) throw error(ErrPrefixIndef);
  _prefix.erase(_prefix.size() - 1);      //treure una lletra del prefix
}

nat easy_dial::num_telf() const throw(error){
  /* Cost constant?*/

}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
  /* El que he fet és guardar una string amb el prefix, primer busco el prefix i un cop la i es
  igual a la mida del prefix busco per esq, central i dret totes les paruales que hi ha*/

  nat i = 0;
  string aux=pref;
  emplena_v(_arrel, result, pref, i, aux);
}

double easy_dial::longitud_mitjana() const throw(){

}
