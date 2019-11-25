#include "call_registry.hpp"
#include <vector>

nat call_registry::hash(nat x) const{

	long y = ((x * x * 31415926) >> 4)%_mida;
	return y;

}

void call_registry::rehash(){

}

void call_registry::afegir(phone p){

  if(factor_carrega(_mida, _n_elements+1) > 0.75) rehash();

  int i = hash(p.numero());
  node_hash* aux = _taula[i];
  bool trobat = false;
  while(aux != NULL and not trobat){
    if(aux->_phone.numero() == num) trobat = true;
    else aux = aux->_seg;
  }

  if(not trobat){
    _taula[i] = new node_hash(p, _taula[i]);
    ++_mida;
  }
}

call_registry::call_registry() throw(error){

	_mida = 10;
  _n_elements = 0;
	_taula = new node_hash*[_mida];
  for(int i=0; i<_mida ; ++i) _taula[i] = NULL;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){

  _mida = R->_mida;
  _n_elements = _n_elements;
  /*for(int i=0; i < R->_mida; ++i){
    _taula[i] = R->_taula[i];
  }*/
}
call_registry& call_registry::operator=(const call_registry& R) throw(error){
  if(this != R){
    _mida = R._mida;
    _n_elements = _n_elements;
    for(int i=0; i < R._mida; ++i){
      _taula[i] = R._taula[i];
    }
  }
  return *this;
}
call_registry::~call_registry() throw(){

}

void call_registry::registra_trucada(nat num) throw(error){
	nat i = hash(num);
  node_hash* aux = _taula[i];

	if (aux->_phone.numero() == num) ++(aux->_phone);
	else if (aux == NULL){
		phone nou(num, "", 1);
		afegir(nou);
	}
  else{
    aux = aux->_seg;
  }
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
	nat i = hash(num);
  node_hash* aux = _taula[i];

	if (aux->_phone.numero() == num){
		phone modificat(num, name, (_taula[i]._phone).frequencia());
		(_taula[i]._phone) = modificat;
	}
	else {
		phone nou(num, name, 0);
		afegir(nou);
	}
}

void call_registry::elimina(nat num) throw(error){
	nat i = hash(num);
	node_hash* aux = _taula[i];
	node_hash* ant = NULL;
	bool trobat = false;

	while(aux != NULL and not trobat){
		if(aux->_phone.numero() == num){
			trobat = true;
			if(ant == NULL){
				aux->_seg = ant;
				--_n_elements;
				delete[] aux;
			}
			else{
				ant->_seg = aux->_seg;
				--_n_elements;
				delete[] aux;
			}
		}
		else{
			ant = aux;
			aux = aux->_seg;
		}
	}
	if(not trobat) throw(ErrNumeroInexistent);
}

bool call_registry::conte(nat num) const throw(){

	nat i = hash(num);
  node_hash* aux = _taula[i];
	bool res = false;

  while(aux != NULL and not res){
    if (aux->_phone.numero() == num) res = true;
    else aux = aux->_seg;
  }
	return res;
}

string call_registry::nom(nat num) const throw(error){
	nat i = hash(num);
  node_hash* aux = _taula[i];
  bool b = false;
	string res;

  while(aux != NULL and not b){
    if (aux->_phone.numero() == num){
      res = aux->_phone.nom();
      b = true;
    }
    else aux = aux->_seg;
  }

  if(not b) throw(ErrNumeroInexistent);
	return res;
}

nat call_registry::num_trucades(nat num) const throw(error){
	nat i = hash(num);
  nat res;

  while(aux != NULL and not b){
    if (aux->_phone.numero() == num){
      res = aux->_phone.frequencia();
      b = true;
    }
    else aux = aux->_seg;
  }

	if(not b) throw(ErrNumeroInexistent);
	return res;
}

bool call_registry::es_buit() const throw(){
	return _n_elements == 0;
}

nat call_registry::num_entrades() const throw(){
	return _n_elements;
}

void call_registry::dump(vector<phone>& V) const throw(error){
	//nomes aqui es llança throw(ErrNomRepetit)
}
