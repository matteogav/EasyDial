#include "easy_dial.hpp"
#include <sstream>

void easy_dial::insereix(const phone& P){
  string s = P.nom();
  s += phone::ENDPREF;
  nat tlf = P.numero();

  string s_tlf = util::tostring(tlf);

  _arrel = rinsereix(_arrel, 0, s, s_tlf);
  _n_elem++;
}

easy_dial::node_tst* easy_dial::rinsereix(node_tst* n, nat i, string s, string s_tlf) throw{
  if(n==NULL){
    n = new node_tst;
    n->_esq = n->_dret = n->_central = NULL;
    n->_lletra = s[i];
    try {
      if (i < s.length()-1) n->_central = rinsereix(n->_central, i+1, s, s_tlf);
      else{      //NOTA: el que diu als apunts [ i == s.length()-1; s[i] == Simbol() ]
        node_tst* ph = new node_tst;
        ph->_esq = ph->_dret = ph->_central = NULL;
        ph->_lletra = s_tlf;
      }
    }
    catch (error) {
      delete n;
      throw;
    }
  }
  else{
    if (n->_lletra[0] > s[i]) n->_esq = rinsereix(n->_esq, i, s, s_tlf);
    else if (n->_lletra[0] < s[i]) n->_dret = rinsereix(n->_dret, i, s, s_tlf);
    else n->_central = rinsereix(n->_central, i+1, s, s_tlf); // (n->_lletra == s[i])
  }
  return n;

}

void easy_dial::emplena_v(node_tst* n, vector<string>& result, const string& pref, nat& i, string &aux) throw{
  /*  */
  if (n != NULL){
    if (i < pref.size()) {
      if (pref[i] < n->_lletra[0]) emplena_v(n->_esq, result, pref, i, aux);
      else if (pref[i] == n->_lletra[0]) emplena_v(n->_central, result, pref, i+1, aux);
      else if (pref[i] > n->_lletra[0]) emplena_v(n->_dret, result, pref, i, aux);
    }
    else if (i >= pref.size()){
      if (n->_lletra != "\0"){
        if (n->_esq != NULL) emplena_v(n->_esq, result, pref, i, aux);
        if (n->_central != NULL)
        {
          aux += n->_lletra[0];
          emplena_v(n->_central, result, pref, i, aux);
        }
        if (n->_dret != NULL) emplena_v(n->_dret, result, pref, i, aux);
      }
      else if (n->_lletra == "\0") {
        result.push_back(aux);
        aux = pref;
      }
    }
  }
}

easy_dial::easy_dial(const call_registry& R) throw(error){

  vector<phone> v;
  R.dump(v);

  for(nat i = 0; i<v.size(); ++i) insereix(v[i]);
  _n_elem = R.num_entrades();

}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){

}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){

}
easy_dial::~easy_dial() throw(){

}

string easy_dial::inici() throw(){
  _prefix = "";

  if (_n_elem == 0) return "";       //si no hi ha elements retorna string buit.
  else {
    
  }
}

string easy_dial::seguent(char c) throw(error){
  /* si introdueix dos cops seguit string buit, tira erro pref indef i */
  _prefix += c;
}

string easy_dial::anterior() throw(error){

}

nat easy_dial::num_telf() const throw(error){

}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
  /* Retorna en el vector result tots els noms dels contactes de 
  telèfon que comencen amb el prefix pref, en ordre lexicogràfic creixent. */

  /*per fer això buscar per arbre el final del prefix, i des d'alla crear string de pref+[i]amb final de "\0"
  on i es cada cop que es mou al centre.*/

  nat i = 0;
  string aux=pref;
  emplena_v(_arrel, result, pref, i, string);

}

double easy_dial::longitud_mitjana() const throw(){

}
