#include "easy_dial.hpp"
#include <sstream>

void easy_dial::insereix(const phone& P, bool &arrel){
  string s = P.nom();
  s += phone::ENDPREF;
  nat i = 0;
  string ant = "";
  string nom = P.nom();
  nat tlf = P.numero();
  _arrel = rinsereix(_arrel, i, s, nom, tlf, arrel, ant);
  //cout << "ARREL_AF:" << _arrel->antFr<<endl;
}

easy_dial::node_tst* easy_dial::rinsereix(node_tst* n, nat &i, string s, string &nom, const nat &telef, bool &arrel, string ant_ant) throw(error){
  if(n==NULL){
    node_tst* n = new node_tst;
    n->_esq = n->_dret = n->_central = NULL;
    n->_lletra = s[i];
    try {
      if(arrel){
        n->maxFr = ant_ant;
        n->antFr = nom;
        n->_tlf = telef;
        arrel = false;
        i++;
        n->_central = rinsereix(n->_central, i, s, ant_ant, telef, arrel, ant_ant);
        /*cout<<"r_inser_arrel_nom:"<<nom<<endl;
				cout<<"r_inser_arrel_mF:"<<n->maxFr<< "."<<endl;
				cout<<"r_inser_arrel_aF:"<<n->antFr<< "."<<endl;*/
      }
      else{
        if (i < s.length()) {
          n->maxFr = nom;
          n->antFr = ant_ant;
          n->_tlf = telef;
          ant_ant = n->maxFr;
          //n->_freq = frequen;      //CAL???
          nom = "";
          i++;
          n->_central = rinsereix(n->_central, i, s, nom, telef, arrel, ant_ant);
          /*cout<<"r_inser_nom:"<<nom<<endl;
					cout<<"r_inser_mF:"<<n->maxFr<< "."<<endl;
					cout<<"r_inser_aF:"<<n->antFr<< "."<<endl;*/
        }
      }
    }
    catch (error) {
      delete n;
      throw;
    }
    return n;
  }
  else{
    if (n->_lletra > s[i]) n->_esq = rinsereix(n->_esq, i, s, nom, telef, arrel, n->antFr);
    else if (n->_lletra < s[i]) n->_dret = rinsereix(n->_dret, i, s, nom, telef, arrel, n->antFr);		
    else {
      if(n->maxFr == ""){
        n->maxFr = nom;
        n->_tlf = telef;
        nom = "";
      }
      ant_ant = n->maxFr;
      i++;
      n->_central = rinsereix(n->_central, i, s, nom, telef, arrel, ant_ant);     // (n->_lletra == s[i])
    }
    return n;
  }
}

void easy_dial::emplena_v(node_tst* n, vector<string>& result, const string& pref, nat& i, string &aux) const throw(){
  /*  */
  if (n != NULL){
    if (i < pref.size()) {  // busco el prefix primer
      if (pref[i] < n->_lletra) emplena_v(n->_esq, result, pref, i, aux);
      else if (pref[i] == n->_lletra) {
        i++;
        emplena_v(n->_central, result, pref, i, aux); //No compilaba amb i+1,
      }
      else if (pref[i] > n->_lletra) emplena_v(n->_dret, result, pref, i, aux);       //no se si funciona amb ++i.
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

void easy_dial::esborra_tst(node_tst* n) throw(){
  if(n != NULL){
    esborra_tst(n->_central);
    esborra_tst(n->_dret);
    esborra_tst(n->_esq);
    delete n;
  }
}

easy_dial::node_tst* easy_dial::copia_tst(node_tst* n) throw(error){
  if(n != NULL){
    node_tst* aux = new node_tst;
    aux->_lletra = n->_lletra;
    aux->_tlf = n->_tlf;
    aux->maxFr = n->maxFr;
    aux->antFr = n->antFr;
    aux->_esq = copia_tst(n->_esq);
    aux->_central = copia_tst(n->_central);
    aux->_dret = copia_tst(n->_dret);
  }
  return n;
}

easy_dial::easy_dial(const call_registry& R) throw(error){
  vector<phone> v;
  R.dump(v);
  bool arr = true;
  _arrel = NULL;
  //ordenar vector per frequencia mes alta a mes baixa, he triat mergesort
   if(v.size() > 0){
     _nom_arrel = v[0].nom();
		/*for(unsigned int i = 0; i<v.size(); ++i){
			 cout <<"vector["<<i<< "]: "<<(v[i].nom())<<endl;
     }*/
     for(unsigned int i = 0; i<v.size(); ++i){
       //cout <<"vector: "<<(v[i].nom())<<endl;
			 insereix(v[i], arr);
     }
     /*cout << "_nom_arrel:" << _nom_arrel<<endl;
     cout << "__arrel:" << _arrel->_lletra<<endl;
     cout << "_arrel_aaaF:" << _arrel->antFr<<endl;
		*/
   }
  _pref_n = NULL;
  _pref_n_ant = NULL;
  _pref_indef = true;   //el prefix en curs queda indefinit
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){
  _prefix = D._prefix;
  _pref_n = D._pref_n;
  _pref_n_ant = D._pref_n_ant;
  _pref_indef = D._pref_indef;
  _arrel = copia_tst(D._arrel);
}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
  if(this != &D){
    easy_dial e(D);
    node_tst* aux = _arrel;
    _arrel = e._arrel;
    e._arrel = aux;
  }
  return *this;
}
easy_dial::~easy_dial() throw(){
  esborra_tst(_arrel);
}

string easy_dial::inici() throw(){
  /* Cost constant?*/
  _prefix = "";
  _pref_indef = false;
  string res = "";
  if (_arrel != NULL){
    _pref_n = _arrel;
    res = _arrel->antFr;
  }
  return res;
}

string easy_dial::seguent(char c) throw(error){
  /* Cost constant?*/
  /* si introdueix dos cops seguit string buit, tira error pref indef i */

  if (_pref_indef == true) throw error(ErrPrefixIndef);
  else if (_pref_n == NULL) {
    _pref_indef = true;
    throw error(ErrPrefixIndef);
  }
  _prefix += c;
  string res="";
  /*_pref_n_ant = _pref_n;
  _pref_n = _pref_n->_central;


  if (_pref_n != NULL){
    bool trobat = false;

    while (_pref_n != NULL and not trobat){
      if (_pref_n->_lletra == c) trobat = true;
      else if (_pref_n->_lletra < c) _pref_n = _pref_n->_esq;
      else if (_pref_n->_lletra > c) _pref_n = _pref_n->_dret;
    }
    if (trobat) res = _prefix + _pref_n->_nom;
  }*/

  return res;
}

string easy_dial::anterior() throw(error){
  /* Cost constant?*/
  if (_pref_indef == true) throw error(ErrPrefixIndef);
  else if (_prefix.empty()) {
    _pref_indef = true;
    throw error(ErrNoHiHaAnterior);
  }

  _prefix.erase(_prefix.size() - 1);      //treure una lletra del prefix
}

nat easy_dial::num_telf() const throw(error){
  /* Cost constant?*/
  /* Possible solucio */
  if (_pref_indef == true) throw error(ErrPrefixIndef);
  else if (_arrel == NULL) throw error(ErrNoExisteixTelefon);
  else {
    node_tst* aux = _pref_n;
    while (aux->_lletra != phone::ENDPREF){
      aux = aux->_central;
    }
    return aux->_tlf;
  }
}

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
  /* El que he fet és guardar un string amb el prefix, primer busco el prefix i un cop la i es
  igual a la mida del prefix busco per esq, central i dret totes les paruales que hi ha*/

  nat i = 0;
  string aux = pref;
  emplena_v(_arrel, result, pref, i, aux);
}

double easy_dial::longitud_mitjana() const throw(){

}
