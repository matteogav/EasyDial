#include "easy_dial.hpp"
#include <sstream>

void easy_dial::insereix(const phone& P, bool &arrel, node_tst* &a, nat &freq, nat &numerad) throw(){
// Cost = O()
  string s = P.nom();
  s += phone::ENDPREF;
  nat i = 0;
  string ant = "";
  string nom = P.nom();
  nat tlf = P.numero();
  freq = P.frequencia();
  nat puls_num = 0;
  a = rinsereix(a, i, s, nom, tlf, arrel, ant, a, freq, puls_num, a);
  numerad += puls_num;
}

easy_dial::node_tst* easy_dial::rinsereix(node_tst* n, nat &i, string s, string &nom, const nat &telef, bool &arrel, string ant_ant, node_tst* res,const nat &freq, nat &puls_num, node_tst* aarreell) throw(error){
// Cost = O()
  if(n==NULL){
    node_tst* m = new node_tst;
    try {
    	m->_esq = m->_dret = m->_central = NULL;
    	m->_lletra = s[i];
      if(arrel){
        m->maxFr = ant_ant;
        m->antFr = nom;
        nom="";
        m->_tlf = telef;
        m->_pare = NULL;
        m->nivell = 0;
        arrel = false;
        i++;
        m->_central = rinsereix(m->_central, i, s, nom, telef, arrel, ant_ant, m, freq, puls_num, aarreell);
      }
      else{
        if (i < s.length()) {
          m->maxFr = nom;
          m->antFr = ant_ant;
          m->_tlf = telef;
          ant_ant = m->maxFr;
					m->_pare = res;
          m->nivell = i+1;
          if (m->maxFr != "") puls_num = freq * m->nivell;
          nom = "";
          i++;
          m ->_central = rinsereix(m->_central, i, s, nom, telef, arrel, ant_ant, m, freq, puls_num, aarreell);
        }
      }
    }
    catch(error){
      delete m;
      throw;
    }
    return m;
  }
  else{
    if (n->_lletra > s[i]) {
      n->_esq = rinsereix(n->_esq, i, s, nom, telef, arrel, n->antFr, n, freq, puls_num, aarreell);
    }
    else if (n->_lletra < s[i]){
      n->_dret = rinsereix(n->_dret, i, s, nom, telef, arrel, n->antFr, n, freq, puls_num, aarreell);
    }
    else {
      if(n->maxFr == ""){
        if (n == aarreell) n->nivell = 1;
        n->maxFr = nom;
        n->_tlf = telef;
        nom = "";
        if (n->antFr != ""){
          puls_num = freq * n->nivell;
        }
      }
      ant_ant = n->maxFr;
      i++;
      n->_central = rinsereix(n->_central, i, s, nom, telef, arrel, ant_ant, n, freq, puls_num, aarreell);
    }
    return n;
  }
}

void easy_dial::emplena_v(node_tst* n, vector<string>& result, const string& pref, nat& i, string &aux) throw(){
// Cost = O()
  if (n != NULL){
    if (i < pref.size()) {  // busco el prefix primer
      if (pref[i] < n->_lletra) emplena_v(n->_esq, result, pref, i, aux);
      else if (pref[i] == n->_lletra) {
        i++;
        emplena_v(n->_central, result, pref, i, aux);
      }
      else if (pref[i] > n->_lletra) emplena_v(n->_dret, result, pref, i, aux);
    }
    else if (i >= pref.size()){   //recorro arbe fins a trobar \0 quan la trobo afegeixo aux al vector result
      if (n->_lletra != phone::ENDPREF){
        if (n->_esq != NULL) emplena_v(n->_esq, result, pref, i, aux);
        if (n->_central != NULL){
          aux += n->_lletra;
          emplena_v(n->_central, result, pref, i, aux);
          if (aux != pref) {
            aux.erase(aux.size() - 1);
          }
        }
        if (n->_dret != NULL) emplena_v(n->_dret, result, pref, i, aux);
      }
      else if (n->_lletra == phone::ENDPREF) {
        result.push_back(aux);
        if (n->_dret != NULL) emplena_v(n->_dret, result, pref, i, aux);
      }
    }
  }
}

void easy_dial::esborra_tst(node_tst* n) throw(){
// Cost = O(#n_nodes_tst) ???
  if(n != NULL){
    esborra_tst(n->_central);
    esborra_tst(n->_dret);
    esborra_tst(n->_esq);
    delete n;
  }
}

easy_dial::node_tst* easy_dial::copia_tst(node_tst* n) throw(error){
// Cost = O(#n_nodes_tst) ???
	node_tst* aux;
  if(n != NULL){
    aux = new node_tst;
		try{
		  aux->_lletra = n->_lletra;
		  aux->_tlf = n->_tlf;
		  aux->maxFr = n->maxFr;
		  aux->antFr = n->antFr;
		  aux->_esq = copia_tst(n->_esq);
		  aux->_central = copia_tst(n->_central);
		  aux->_dret = copia_tst(n->_dret);
    }
		catch(error){
			delete aux;
			throw;
		}
  }
  return aux;
}

void easy_dial::partir(vector<phone> &v, vector<phone> &v2, int m) throw(){
// Cost = O(1) ??
  int i = v.size();
  while (i > m){
    v2.insert(v2.begin(), v.back());
    v.pop_back();
    --i;
  }
}

void easy_dial::fusionar(vector<phone> &v, vector<phone> &v2) throw(){
// Cost = O()
  if (v.size() == 0) v = v2;
  if (v.size() > 0 and v2.size() > 0){
    vector<phone>::iterator it_v = v.begin();
    vector<phone>::iterator it_v2 = v2.begin();
    vector<phone> res;
    bool v_acabat = false, v2_acabat = false;

    while (not v_acabat and not v2_acabat){
      if (*it_v2 < *it_v){
        res.push_back(*it_v);
        ++it_v;
      }
      else if (*it_v2 >= *it_v){
        res.push_back(*it_v2);
        ++it_v2;
      }

      if (it_v == v.end()) v_acabat = true;
      if (it_v2 == v2.end()) v2_acabat = true;
    }
    if (v_acabat){
      while (it_v2 != v2.end()){
        res.push_back(*it_v2);
        ++it_v2;
      }
    }
    else if (v2_acabat){
      while (it_v != v.end()){
        res.push_back(*it_v);
        ++it_v;
      }
    }
    v = res;
  }
}

void easy_dial::ordena(vector<phone> &v, int n) throw(){
// Cost = O()
  vector<phone> v2;
  if(n>1){
    nat m = n / 2;
    partir(v,v2,m);
    ordena(v,m);
    ordena(v2,n-m);
    fusionar(v,v2);
  }
}

easy_dial::easy_dial(const call_registry& R) throw(error){
// Cost = O()
  vector<phone> v;
  R.dump(v);
  bool arr = true;
  _arrel = NULL;
  total_freq = 0.0;
  num_puls = 0.0;
  numerador = 0;

  nat freq = 0, numerad = 0;

  if(v.size() > 0){
    //ordenar vector per frequencia mes alta a mes baixa, hem triat mergesort
    ordena(v,v.size());
    _nom_arrel = v[0].nom();
    _tlf_arrel = v[0].numero();
    for(unsigned int i = 0; i<v.size(); ++i) {
      insereix(v[i], arr, _arrel, freq, numerad);
      numerador = numerad;
      total_freq += freq;
    }
  }
  _pref_n = NULL;
  _pref_indef = true;   //el prefix en curs queda indefinit
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){
// Cost = O(#n_nodes_tst)
  _prefix = D._prefix;
  _pref_n = D._pref_n;
  _pref_indef = D._pref_indef;
  total_freq = D.total_freq;
  num_puls = D.num_puls;
  numerador = D.numerador;
  _arrel = copia_tst(D._arrel);
}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
// Cost = O(#n_nodes_tst) ???
  if(this != &D){
    easy_dial e(D);
    node_tst* aux = _arrel;
    _arrel = e._arrel;
    e._arrel = aux;
  }
  return *this;
}
easy_dial::~easy_dial() throw(){
// Cost = O(#n_nodes_tst)
  esborra_tst(_arrel);
}

string easy_dial::inici() throw(){
// Cost = O(1)
  _prefix = "";
  string res = "";
  _pref_indef = false;
  null_pref_n = false;
  es_buit = false;
  if (_arrel != NULL){
    _pref_n = _arrel;
    res = _arrel->antFr;
  }
  else es_buit = true;
  return res;
}

string easy_dial::seguent(char c) throw(error){
// Cost = O(1) ---> Cas pitjor (#n_lletres_abecedari)
// si introdueix dos cops seguit string buit, tira error pref indef i
  if (_pref_indef) throw error(ErrPrefixIndef);
  else if (null_pref_n or es_buit) {
    _pref_indef = true;
    throw error(ErrPrefixIndef);
  }
  _prefix += c;
  string res="";

  if (_pref_n != NULL){
    bool trobat = false;
    node_tst* aux = _pref_n;
    if (_prefix.length() > 1) aux = aux->_central;
    if (aux->_lletra != phone::ENDPREF){
        while (aux != NULL and not trobat){
        if (aux->_lletra == c) trobat = true;
        else if (aux->_lletra > c) aux = aux->_esq;
				else aux = aux->_dret;
      }
    }
    else {
      if (aux->_dret != NULL) {
        aux = aux->_dret;
        if (aux->_lletra == c) trobat = true;
      }
    }
    if (trobat){
      _pref_n = aux;
      res = _pref_n->maxFr;
      if (res == "") es_buit = true;
    }
    else {
      null_pref_n = true;
      res = "";
    }
  }

  return res;
}

string easy_dial::anterior() throw(error){
// Cost = O(1) ---> Cas pitjor (#n_lletres_abecedari)  ???
  if (_pref_indef == true) throw error(ErrPrefixIndef);
  else if (_prefix.empty()) {
    _pref_indef = true;
    throw error(ErrNoHiHaAnterior);
  }
  string res = "";
  if (_arrel != NULL) {
    if (_prefix.size() == 1) _prefix = "";
    else if (_prefix.size() > 1) _prefix.erase(_prefix.size() - 1);      //treure una lletra del prefix

    if (_prefix != ""){
      if (not null_pref_n){
        string ultima = _prefix.substr(_prefix.length()-1, 1);
        while (_pref_n->_lletra != ultima[0]) _pref_n = _pref_n->_pare;
        res = _pref_n->maxFr;
      }
      else {
        null_pref_n = false;
        res = _pref_n->maxFr;      //si el pref_n en seguent havia anat a null
      }
    }
    else {                  //si prefix queda a 0 arrel
      _pref_n = _arrel;
      null_pref_n = false;
      res = _pref_n->antFr;
    }
    es_buit = false;
  }


  return res;
}

nat easy_dial::num_telf() const throw(error){
// Cost = O(1)
  if (_pref_indef == true) throw error(ErrPrefixIndef);
  else if (_arrel == NULL) throw error(ErrNoExisteixTelefon);
  else {
    if (null_pref_n or es_buit) throw error(ErrNoExisteixTelefon);
    else {
      if (_prefix == "") return _tlf_arrel;
      else return _pref_n->_tlf;
    }
  }
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
// Cost = O()
/* El que hem fet és guardar un string amb el prefix, primer busquem el prefix i un cop la i es
   igual a la mida del prefix busquem per esq, central i dret totes les paruales que hi han*/

  nat i = 0;
  string aux = pref;
  emplena_v(_arrel, result, pref, i, aux);
}

double easy_dial::longitud_mitjana() const throw(){
// Cost = O(1)
  double res = 0;
  if (total_freq != 0) res = double(numerador) / double(total_freq);
  return res;
}
