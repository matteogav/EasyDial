#include "phone.hpp"

//buscar en name si hi ha un dels caracters "prohibits"
phone::phone(nat num, const string& name, nat compt) throw(error){
  size_t busca = name.find(DELETECHAR);
  if (busca != string::npos) throw(ErrNomIncorrecte);

  busca = name.find(ENDCHAR); 
  if (busca != string::npos) throw(ErrNomIncorrecte);

  busca = name.find(ENDPREF); 
  if (busca != string::npos) throw(ErrNomIncorrecte);
  telf=num;
  contacte=name;
  freq=compt;
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
phone::phone(const phone& T) throw(error){
  telf = T.telf;
  contacte = T.contacte;
  freq = T.freq;
}
phone& phone::operator=(const phone& T) throw(error){
  telf = T.telf;
  contacte = T.contacte;
  freq = T.freq;
  return *this;
}
phone::~phone() throw(){}

nat phone::numero() const throw(){
  return telf;
}

string phone::nom() const throw(){
  return contacte;
}

nat phone::frequencia() const throw(){
  return freq;
}

phone& phone::operator++() throw(){
  ++freq;
  return *this;
}

phone phone::operator++(int) throw(){
  phone p = *this;
  ++freq;
  return p;
}

bool phone::operator==(const phone& T) const throw(){
  return (telf == T.telf and contacte == T.contacte and freq == T.freq);
}
bool phone::operator!=(const phone& T) const throw(){
  return !(*this == T);
}
bool phone::operator<(const phone& T) const throw(){
  bool res;
  if (freq < T.freq) res=true;
  else if (freq == T.freq){
    if (contacte < T.contacte) res=true;
    else res=false;
  }
  else res=false;

  return res;
  //return (freq < T.freq and contacte < T.contacte);
}
bool phone::operator>(const phone& T) const throw(){
  bool res;
  if (freq > T.freq) res=true;
  else if (freq == T.freq){
    if (contacte > T.contacte) res=true;
    else res=false;
  }
  else res=false;

  return res;
  //return (freq > T.freq and contacte > T.contacte);
}
bool phone::operator<=(const phone& T) const throw(){
  return (freq <= T.freq and contacte <= T.contacte);
}
bool phone::operator>=(const phone& T) const throw(){
  return (freq >= T.freq and contacte >= T.contacte);
}
