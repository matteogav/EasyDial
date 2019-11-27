#include "call_registry.hpp"
#include <vector>

call_registry::node_hash::node_hash(const phone &p, node_hash* seg){
	_phone = p;
	_seg = seg;
}

nat call_registry::hash(nat x) const{

	long y = ((x * x * 31415926) >> 4)%_mida;
	return y;

}

nat call_registry::hash_c(string nom) const{

}

void call_registry::rehash(){
	_mida *= 2;
	node_hash **aux = _taula;
	node_hash **_taula_ = new node_hash*[_mida];

	for (unsigned i = 0; i < (_mida/2); i++){			// per cada posicio i de la taula
		node_hash *x = aux[i];
		while (x != NULL){								//per cada node de la sequencia de la posicio i
			nat j = hash((x->_phone).numero());

			_taula_[j] = new node_hash(x->_phone, _taula_[j]);				//creo nou node i el poso a davant
			x = x->_seg;
		}
	}
	_taula = _taula_;
}

call_registry::node_hash* call_registry::consulta(nat num, nat &i) const{
	
	i = hash(num);
	node_hash *res = _taula[i];
	bool trobat = false;

	//ho miro fins al últim abans d'acabar, per guardar anterior, si hi es retorna un element del mig
	//si no hi es en el bucle poder esta en el ultim i es mira en la seguent funcio
	while (!trobat and res->_seg != NULL){
		if ((res->_phone).numero() == num) trobat = true;
		else res = res->_seg;
	}

	return res;
}

call_registry::call_registry() throw(error){

	_mida = 16;
	_n_elements = 0;
	_taula = new node_hash*[_mida];
	for(nat i=0; i<_mida ; ++i) _taula[i] = NULL;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){

  _mida = R._mida;
  _n_elements = R._n_elements;
  for(nat i=0; i < R._mida; ++i){
    _taula[i] = R._taula[i];
  }
}
call_registry& call_registry::operator=(const call_registry& R) throw(error){
  if(this != &R){
    _mida = R._mida;
    _n_elements = _n_elements;
    for(nat i=0; i < R._mida; ++i){
      _taula[i] = R._taula[i];
    }
  }
  return *this;
}
call_registry::~call_registry() throw(){

}

void call_registry::registra_trucada(nat num) throw(error){
	float f_carrega = _n_elements/_mida;
	if(f_carrega > 0.75) rehash();

	nat k;
	node_hash* aux = consulta(num, k);

	//si no le trobat de moment estic al ultim node de la llista comprovo si, és igual o no.
	if ((aux->_phone).numero() == num) (aux->_phone)++;		//sumo en un la frequencia
	else { 													//creo un nou node amb freq 1 i sense num
		phone nou_p(num, "", 1);
		_taula[k] = new node_hash(nou_p, _taula[k]);
		_n_elements++;
	}
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
	float f_carrega = _n_elements/_mida;
	if(f_carrega > 0.75) rehash();

	nat k;
	node_hash* aux = consulta(num, k);

	//si no le trobat de moment estic al ultim node de la llista, per tant, comprovo si, és igual o no.
	if ((aux->_phone).numero() == num){
		phone modificat(num, name, (aux->_phone).frequencia());
		(aux->_phone) = modificat;
	}
	else { 													//creo un nou node amb freq 0
		phone nou_p(num, name, 0);
		_taula[k] = new node_hash(nou_p, _taula[k]);
		_n_elements++;
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
				_taula[i] = aux->_seg;
			}
			else{
				ant->_seg = aux->_seg;
			}
			--_n_elements;
			delete(aux);
		}
		else{
			ant = aux;
			aux = aux->_seg;
		}
	}
	if(not trobat) throw(ErrNumeroInexistent);
}

bool call_registry::conte(nat num) const throw(){
	nat k;
	node_hash* aux = consulta(num, k);
	bool res;

	if ((aux->_phone).numero() == num) res = true;
	else res = false;

	return res;
}

string call_registry::nom(nat num) const throw(error){
	nat k;
	node_hash* aux = consulta(num, k);
	string res;

	if ((aux->_phone).numero() == num) res = (aux->_phone).nom();
	else throw(ErrNumeroInexistent);

	return res;
}

nat call_registry::num_trucades(nat num) const throw(error){
	nat k;
	node_hash* aux = consulta(num, k);
	nat res;

	if ((aux->_phone).numero() == num) res = (aux->_phone).frequencia();
	else throw(ErrNumeroInexistent);

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
	
	//volca  elements a una nova taula de hash amb funcio hash dels noms
	node_hash **_t_aux = new node_hash*[_mida];
	for (unsigned i = 0; i < _mida; i++){
		if (_taula[i] != NULL){
			node_hash *aux = _taula[i];
			while (aux != NULL){
				nat j = hash_c((aux->_phone).nom());
				_t_aux[j] = new node_hash(aux->_phone, _t_aux[j]);
				aux = aux->_seg;
			}
		}
	}
	//afegir nova taula de hash al vector i comprovar si hi ha noms iguals
	//fent lo de sinonims
	bool iguals = false;
	nat i = 0;
	while (i < _mida){
		if (_t_aux[i] != NULL and _t_aux[i]->_seg != NULL){
			node_hash *aux = _t_aux[i];
			while (aux != NULL){
				node_hash *x = _t_aux[i];
				string usr = (aux->_phone).nom();
				while (x != NULL){
					if(usr == (x->_phone).nom()) iguals = true;
					x = x->_seg;
				}
				if (!iguals) V.push_back(aux->_phone);
				else throw(ErrNomRepetit);
				aux = aux->_seg;
			}
		}
		else if (_t_aux[i] != NULL and _t_aux[i]->_seg == NULL){
			V.push_back(_t_aux[i]->_phone);
		}
		i++;
	}

	
	
	
	
	//volca els elements al vector (desordenats i sense filtre de repetits)
	for (unsigned i = 0; i < _mida; i++){
		if (_taula[i] != NULL){
			node_hash *aux = _taula[i];
			while (aux != NULL){
				V.push_back(aux->_phone);
				aux = aux->_seg;
			}
		}
	}


}