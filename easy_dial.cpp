#include "easy_dial.hpp"


void easy_dial::insereix(const phone& P){
  string s = P.nom();
  s += ENDPREF;
  nat tlf = P.numero();
  string s_tlf = tostring(tlf);

  _arrel = rinsereix(_arrel, 0, s, s_tlf);
}

easy_dial::node_tst* easy_dial::rinsereix(node_tst* n, nat i, string s, string s_tlf){
  if(n==NULL){
    n = new node_tst;
    n->_esq = n->_dret = n->_central = NULL;
    n->_lletra = s;
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
    if (n->_lletra > s[i]) n->_esq = rinsereix(n->_esq, i, s, s_tlf);
    else if (n->_lletra < s[i]) n->_dret = rinsereix(n->_dret, i, s, s_tlf);
    else n->_central = rinsereix(n->_central, i+1, s_tlf); // (n->_lletra == s[i])
  }
  return n;

}

easy_dial::easy_dial(const call_registry& R) throw(error){

  vector<phone>& v;
  R.dump(v);
  for(nat i = 0; i<v.size(); ++i) insereix(v[i]);

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
