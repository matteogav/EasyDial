#include "call_registry.hpp"
#include <vector>

call_registry::node_hash::node_hash(const phone &p, node_hash* seg){
	_phone = p;
	_seg = seg;
}

nat call_registry::hash(nat x) const{
	long y = (x * x * 31415926)%_mida;

	return y;
	/*
	nat y = x, n;
	for(int i=1; y <= 0; ++i){
		n = y%10 * i;
		y = y/10;
	}
	return n;*/
}

nat call_registry::hash_c(string nom) const{
	nat n = 0;
	for (nat i = 0; i < nom.length(); ++i) n = n + nom[i]*i;
	n = n%_mida;
	return n;
}

void call_registry::rehash(){
	//cout<<"------------------------------REHASH--------------------------"<<endl;
	nat mida = _mida;
	_mida *= 2;
	node_hash** aux = _taula;
	node_hash** _taula_ = new node_hash*[_mida];
	for(nat i=0; i < _mida; ++i) _taula_[i] = NULL;

	for (nat i = 0; i < mida; ++i){				// per cada posicio i de la taula abans de rehash
		node_hash* x = aux[i];
		while (x != NULL){								//per cada node de la sequencia de la posicio i
			nat j = hash(x->_phone.numero());
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
	if (res != NULL){
		while (not trobat and res->_seg != NULL){
			if (res->_phone.numero() == num) trobat = true;
			else res = res->_seg;
		}
	}
	return res;
}

void call_registry::esborrar(node_hash* n) const{
	if (n!=NULL) {
    	esborrar(n->_seg);
    	delete n;
  	}
}

call_registry::call_registry() throw(error){

	_mida = 16;
	_n_elements = 0;
	_taula = new node_hash*[_mida];
	for(nat i=0; i < _mida ; ++i) _taula[i] = NULL;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){
	_mida = R._mida;
	_n_elements = R._n_elements;

	node_hash **taula_aux = new node_hash*[_mida];
	for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;

	for(nat i=0; i < _mida; ++i){
		node_hash* aux = R._taula[i];
		node_hash *ant = NULL;
		while(aux != NULL){
			if(ant == NULL) {
				taula_aux[i] = new node_hash(aux->_phone, taula_aux[i]);
				ant = taula_aux[i];
			}
			else {
				ant->_seg = new node_hash(aux->_phone, ant->_seg);
			}
			
			aux = aux->_seg;
		}
	}
	_taula = taula_aux;
}

call_registry& call_registry::operator=(const call_registry& R) throw(error){
	_mida = R._mida;
	_n_elements = R._n_elements;

	node_hash **taula_aux = new node_hash*[_mida];
	for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;

	if(this != &R){
		for(nat i=0; i < _mida; ++i){
			node_hash* aux = R._taula[i];
			node_hash *ant = NULL;
			while(aux != NULL){
				if(ant == NULL) {
					taula_aux[i] = new node_hash(aux->_phone, taula_aux[i]);
					ant = taula_aux[i];
				}
				else {
					ant->_seg = new node_hash(aux->_phone, ant->_seg);
				}
			
				aux = aux->_seg;
			}
		}
		_taula = taula_aux;
	}

	return *this;
}

call_registry::~call_registry() throw(){
	for (nat i = 0; i < _mida; ++i) esborrar(_taula[i]);
	delete[] _taula;
}

void call_registry::registra_trucada(nat num) throw(error){
	if (es_buit()){
		nat z = hash(num);
		phone nou_p(num, "", 1);
		_taula[z] = new node_hash(nou_p, _taula[z]);
		++_n_elements;
	}
	else {
		float f_carrega = float(_n_elements)/float(_mida);
		if(f_carrega > 0.75) rehash();

		nat k;
		node_hash* aux = consulta(num, k);

		if (aux != NULL){
			//si no le trobat de moment estic al ultim node de la llista, per tant, comprovo si, és igual o no.
			if (aux->_phone.numero() == num) ++aux->_phone;			//sumo en un la frequencia
			else { 													//creo un nou node amb freq 1 i sense num			
				phone nou_p(num, "", 1);
				_taula[k] = new node_hash(nou_p, _taula[k]);
				++_n_elements;
			}
		}
		else { 														//creo un nou node amb freq 1 i sense num
			phone nou_p(num, "", 1);
			_taula[k] = new node_hash(nou_p, _taula[k]);
			++_n_elements;
		}
	}
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
	if (es_buit()){
		nat z = hash(num);
		phone nou_p(num, name, 0);
		_taula[z] = new node_hash(nou_p, _taula[z]);
		++_n_elements;
	}
	else {
		float f_carrega = float(_n_elements)/float(_mida);
		if(f_carrega > 0.75) rehash();

		nat k;
		node_hash* aux = consulta(num, k);

		if (aux != NULL){
			//si no le trobat de moment estic al ultim node de la llista, per tant, comprovo si, és igual o no.
			if (aux->_phone.numero() == num){
				phone modificat(num, name, aux->_phone.frequencia());
				(aux->_phone) = modificat;
			}
			else { 													//creo un nou node amb freq 0
				phone nou_p(num, name, 0);
				_taula[k] = new node_hash(nou_p, _taula[k]);
				++_n_elements;
			}
		}
		else { 													//creo un nou node amb freq 0
			phone nou_p(num, name, 0);
			_taula[k] = new node_hash(nou_p, _taula[k]);
			++_n_elements;
		}
	}
}

void call_registry::elimina(nat num) throw(error){
	if (es_buit()) throw error(ErrNumeroInexistent);
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
	if(not trobat) throw error(ErrNumeroInexistent);
}

bool call_registry::conte(nat num) const throw(){	
	if (es_buit()) return false;
	bool res = false;

	nat k=0;
	node_hash* aux = consulta(num, k);

	if (aux != NULL){
		if (aux->_phone.numero() == num) res = true;
	}

	return res;
}

string call_registry::nom(nat num) const throw(error){
	if (es_buit()) throw error(ErrNumeroInexistent);
	nat k;
	node_hash* aux = consulta(num, k);
	string res;

	if (aux != NULL){
		if (aux->_phone.numero() == num) res = aux->_phone.nom();
		else throw error(ErrNumeroInexistent);
	}
	else throw error(ErrNumeroInexistent);

	return res;
}

nat call_registry::num_trucades(nat num) const throw(error){
	if (es_buit()) throw error(ErrNumeroInexistent);
	nat k;
	node_hash* aux = consulta(num, k);
	nat res;

	if (aux != NULL){
		if (aux->_phone.numero() == num) res = aux->_phone.frequencia();
		else throw error(ErrNumeroInexistent);
	}
	else throw error(ErrNumeroInexistent);

	return res;
}

bool call_registry::es_buit() const throw(){
	return _n_elements == 0;
}

nat call_registry::num_entrades() const throw(){
	return _n_elements;
}

void call_registry::dump(vector<phone>& V) const throw(error){
	//nomes aqui es llança throw error(ErrNomRepetit)
	//volca  elements a una nova taula de hash amb funcio hash dels noms
	if(not es_buit()){
		node_hash** taula_aux = new node_hash*[_mida];
		for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;

		for (nat i = 0; i < _mida; ++i){
			if (_taula[i] != NULL){
				node_hash* aux = _taula[i];
				while (aux != NULL){
					nat j = hash_c(aux->_phone.nom());
					taula_aux[j] = new node_hash(aux->_phone, taula_aux[j]);
					aux = aux->_seg;
				}
			}
		}

		//afegir nova taula de hash al vector i comprovar si hi ha noms iguals
		//fent lo de sinonims
		for (nat i = 0; i < _mida; ++i){
			if (taula_aux[i] != NULL and taula_aux[i]->_seg != NULL){
				node_hash* aux = taula_aux[i];

				while (aux != NULL){				//afegir a vector si no es igual en cap sinonim
					node_hash *x = aux->_seg;
					string usr = aux->_phone.nom();

					bool trobat = false;
					while (x != NULL and !trobat){				//comprova si els sinonims que queden si hi ha algun igual de nom
						if(usr != "") if (usr == x->_phone.nom()) trobat = true;
						x = x->_seg;
					}
					if (trobat) throw error(ErrNomRepetit);
					else {
						if(usr != "") V.push_back(aux->_phone);
					}
					aux = aux->_seg;
				}
			}
			else if (taula_aux[i] != NULL and taula_aux[i]->_seg == NULL){
				if ((taula_aux[i]->_phone).nom() != "") V.push_back(taula_aux[i]->_phone);
			}
		}
	}
}




/*		//imprimir taula
	for (unsigned i = 0; i<_mida;i++){
		cout<<i<<". ";
		node_hash *x = _taula[i];
		if (x != NULL){
			while (x != NULL){							//per cada node de la sequencia de la posicio i
				cout<<"["<<(x->_phone).numero()<<", "<<(x->_phone).nom()<<", "<<(x->_phone).frequencia()<<"] --> ";
				x = x->_seg;
			}
		}
		cout<<endl;
	}

*/
