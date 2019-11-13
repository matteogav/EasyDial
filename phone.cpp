#include "phone.hpp"

phone::phone(nat num, const string& name, nat compt) throw(error){
  size_t busca = name.find(DELETECHAR); 
  if (busca != string::npos) throw(ErrNomIncorrecte);

  busca = name.find(ENDCHAR); 
  if (busca != string::npos) throw(ErrNomIncorrecte);

  busca = name.find(ENDPREF); 
  if (busca != string::npos) throw(ErrNomIncorrecte);
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
phone::phone(const phone& T) throw(error){
  num = T.num;
  name = T.name;
  compt = T.compt;

}
phone& phone::operator=(const phone& T) throw(error){
  num = T.num;
  name = T.name;
  compt = T.compt;
  return *this;
}
phone::~phone() throw(){

}

nat phone::numero() const throw(){
  return num;
}

string phone::nom() const throw(){
  return name;
}

nat phone::frequencia() const throw(){
  return compt;
}

phone& phone::operator++() throw(){
  ++compt;
  return *this;
}

phone phone::operator++(int) throw(){
  phone p = *this;
  ++compt;
  return p;
}

bool phone::operator==(const phone& T) const throw(){
  return (num == T.num and name == T.name and compt == T.compt);
}
bool phone::operator!=(const phone& T) const throw(){
  return !(*this == T);
}
bool phone::operator<(const phone& T) const throw(){
  return (compt < T.compt and name < T.name);
}
bool phone::operator>(const phone& T) const throw(){
  return (compt > T.compt and name > T.name);
}
bool phone::operator<=(const phone& T) const throw(){
  return (compt <= T.compt and name <= T.name);
}
bool phone::operator>=(const phone& T) const throw(){
  return (compt >= T.compt and name >= T.name);
}
