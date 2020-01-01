#include "phone.hpp"

//buscar en name si hi ha un dels caracters "prohibits"
phone::phone(nat num, const string& name, nat compt) throw(error){
// Cost = O(name.size()) ---> O(1)
  bool trobat = false;
  nat i = 0;
  while (i < name.size() and !trobat){
    if (name[i] == DELETECHAR or name[i] == ENDCHAR or name[i] == ENDPREF) throw error(ErrNomIncorrecte);
    i++;
  }
  telf = num;
  contacte = name;
  freq = compt;
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
phone::phone(const phone& T) throw(error){
// Cost = O(1)
  telf = T.telf;
  contacte = T.contacte;
  freq = T.freq;
}
phone& phone::operator=(const phone& T) throw(error){
// Cost = O(1)
  telf = T.telf;
  contacte = T.contacte;
  freq = T.freq;
  return *this;
}
phone::~phone() throw(){}

nat phone::numero() const throw(){
// Cost = O(1)
  return telf;
}

string phone::nom() const throw(){
// Cost = O(1)
  return contacte;
}

nat phone::frequencia() const throw(){
// Cost = O(1)
  return freq;
}

phone& phone::operator++() throw(){
// Cost = O(1)
  ++freq;
  return *this;
}

phone phone::operator++(int) throw(){
// Cost = O(1)
  phone p = *this;
  ++freq;
  return p;
}

bool phone::operator==(const phone& T) const throw(){
// Cost = O(1)
  return (contacte == T.contacte and freq == T.freq);
}

bool phone::operator!=(const phone& T) const throw(){
// Cost = O(1)
  return !(*this == T);
}

bool phone::operator<(const phone& T) const throw(){
// Cost = O(1)
  bool res;
  if (freq < T.freq) res = true;
  else if (freq == T.freq){
    if (contacte < T.contacte) res = true;
    else res = false;
  }
  else res = false;

  return res;
}

bool phone::operator>(const phone& T) const throw(){
// Cost = O(1)
  bool res;
  if (freq > T.freq) res = true;
  else if (freq == T.freq){
    if (contacte > T.contacte) res = true;
    else res = false;
  }
  else res = false;

  return res;
}

bool phone::operator<=(const phone& T) const throw(){
// Cost = O(1)
  bool res;
  if (*this < T) res = true;
  else if (*this == T) res = true;
  else res = false;

  return res;
}

bool phone::operator>=(const phone& T) const throw(){
// Cost = O(1)
  bool res;
  if (*this > T) res = true;
  else if (*this == T) res = true;
  else res = false;

  return res;
}
