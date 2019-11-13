#include "phone.hpp"

phone(nat num=0, const string& name="", nat compt=0) throw(error){
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
phone(const phone& T) throw(error){
  num = T->num; polla
  name = T->name;
  compt = T->compt;

}
phone& operator=(const phone& T) throw(error){
  if(this != T){
    num = T->num;
    name = T->name;
    compt = T->compt;
  }
  return *this;
}
~phone() throw(){

}

nat numero() const throw(){
  return num;
}

string nom() const throw(){
  return name;
}

nat frequencia() const throw(){
  return compt;
}

phone& operator++() throw(){
  ++compt;
  return *this;
}

phone operator++(int) throw(){
  phone p = *this;
  ++compt;
  return p;
}

bool operator==(const phone& T) const throw(){
  return (num == T->num and name == T->name and compt == T->compt);
}
bool operator!=(const phone& T) const throw(){
  return !(*this == T);
}
bool operator<(const phone& T) const throw(){
  return (compt < T->compt and name < T->name)
}
bool operator>(const phone& T) const throw(){
  return (compt > T->compt and name > T->name);
}
bool operator<=(const phone& T) const throw(){
  return (compt <= T->compt and name <= T->name);
}
bool operator>=(const phone& T) const throw(){
  return (compt >= T->compt and name >= T->name);
}
