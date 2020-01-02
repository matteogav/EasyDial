#include "call_registry.hpp"
#include <vector>

call_registry::node_hash::node_hash(const phone &p, node_hash* seg) throw(error){
// Cost = O(1)
	_phone = p;
	_seg = seg;
}

nat call_registry::hash(const nat &x, nat M) throw(){
// Cost = O(#num_digits de x)
	nat y = x;
	nat n = 0;
	int i = 1;
	while (y > 9){
		n += y%10 * i;
		y = y/10;
		++i;
	}
	n += y * i;
	return n%M;
}

nat call_registry::hash_c(string nom, nat M) throw(){
// Cost = O(nom.length())
	nat n = 0;
	for (nat i = 0; i < nom.length(); ++i) n = n + nom[i]*i;
	n = n%M;
	return n;
}

void call_registry::rehash(nat &M, node_hash** &taula) throw(){
// Cost = O(n) --> mida taula + cada node de la sequencia de la posicio i
	nat mida = M;
	M *= 2;
	node_hash** aux = taula;
	node_hash** _taula_ = new node_hash*[M];
	try{
		for(nat i=0; i < M; ++i) _taula_[i] = NULL;
	}
	catch(error){
		for(nat i=0; i < M; ++i) esborrar(_taula_[i]);
    	delete[] _taula_;
    	throw;
    }

	for (nat i = 0; i < mida; ++i){						// per cada posicio i de la taula abans de rehash
		node_hash* x = aux[i];
		while (x != NULL){								//per cada node de la sequencia de la posicio i
			//calcula hash(num)
			nat y = x->_phone.numero();
			nat n = 0;
			int i = 1;
			while (y > 9){
				n += y%10 * i;
				y = y/10;
				++i;
			}
			n += y * i;
			nat j = n%M;
			try{
				_taula_[j] = new node_hash(x->_phone, _taula_[j]);				//creo nou node i el poso a davant
			}
			catch(error){
				delete _taula_[j];
				throw;
			}
			x = x->_seg;
		}
	}
	taula = _taula_;
	_taula_ = NULL;			// eliminar node _taula_
	delete[] _taula_;
}

call_registry::node_hash* call_registry::consulta(nat num, nat num_hash, node_hash** taula) throw(){
// Cost = O(hash + elements de la sequencia)
	node_hash* res = taula[num_hash];
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

void call_registry::esborrar(node_hash* n) throw(){
// Cost = O(n) --> n = elements de la sequencia
	if (n!=NULL) {
    	esborrar(n->_seg);
    	delete n;
  	}
}

call_registry::call_registry() throw(error){
// Cost = O(_mida)
	_mida = 16;
	_n_elements = 0;
	_taula = new node_hash*[_mida];
	try{
		for(nat i=0; i < _mida ; ++i) _taula[i] = NULL;
	}
	catch(error){
		for(nat i=0; i < _mida; ++i) esborrar(_taula[i]);
    	delete[] _taula;
    	throw;
    }
	
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){
// Cost = O(n*l) --> n = _mida i l = elements de la sequencia en posicio i
	_mida = R._mida;
	_n_elements = R._n_elements;

	node_hash **taula_aux = new node_hash*[_mida];
	try{
		for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;
	}
	catch(error){
		for(nat i=0; i < _mida; ++i) esborrar(taula_aux[i]);
    	delete[] taula_aux;
    	throw;
    }

	for(nat i=0; i < _mida; ++i){
		node_hash* aux = R._taula[i];
		node_hash *ant = NULL;
		while(aux != NULL){
			if(ant == NULL) {
				try{
					taula_aux[i] = new node_hash(aux->_phone, taula_aux[i]);
				}
				catch(error){
					delete taula_aux[i];
					throw;
				}
				ant = taula_aux[i];
			}
			else {
				try{
					ant->_seg = new node_hash(aux->_phone, ant->_seg);
				}
				catch(error){
					delete ant->_seg;
					throw;
				}
			}
			aux = aux->_seg;
		}
	}
	_taula = taula_aux;
}

call_registry& call_registry::operator=(const call_registry& R) throw(error){
// Cost = O(n*l) --> n = _mida i l = elements de la sequencia en posicio i
	_mida = R._mida;
	_n_elements = R._n_elements;

	node_hash **taula_aux = new node_hash*[_mida];
	try{
		for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;
	}
	catch(error){
		for(nat i=0; i < _mida; ++i) esborrar(taula_aux[i]);
    	delete[] taula_aux;
    	throw;
    }

	if(this != &R){
		for(nat i=0; i < _mida; ++i){
			node_hash* aux = R._taula[i];
			node_hash *ant = NULL;
			while(aux != NULL){
				if(ant == NULL) {
					try{
						taula_aux[i] = new node_hash(aux->_phone, taula_aux[i]);
					}
					catch(error){
						delete taula_aux[i];
						throw;
					}
					ant = taula_aux[i];
				}
				else {
					try{
						ant->_seg = new node_hash(aux->_phone, ant->_seg);
					}
					catch(error){
						delete ant->_seg;
						throw;
					}
				}
				aux = aux->_seg;
			}
		}
		_taula = taula_aux;
	}
	return *this;
}

call_registry::~call_registry() throw(){
// Cost = O(_mida*n) 
	for (nat i = 0; i < _mida; ++i) esborrar(_taula[i]);
	delete[] _taula;
}

void call_registry::registra_trucada(nat num) throw(error){
// Cost = O(hash + elements sequencia) perque rehash es fa en molt poques ocacions
	if (es_buit()){
		nat z = hash(num, _mida);					//cost O(num.size())
		phone nou_p(num, "", 1);
		try{
			_taula[z] = new node_hash(nou_p, _taula[z]);
		}
		catch(error){
			delete _taula[z];
			throw;
		}
		++_n_elements;
	}
	else {
		float f_carrega = float(_n_elements)/float(_mida);
		if(f_carrega > 0.75) rehash(_mida, _taula);				//cost O(n*l)

		nat k = hash(num, _mida);
		node_hash* aux = consulta(num, k, _taula);			//cost O(hash + elements sequencia)

		if (aux != NULL){							//O(1)
			//si no le trobat de moment estic al ultim node de la llista, per tant, comprovo si, és igual o no.
			if (aux->_phone.numero() == num) ++aux->_phone;			//sumo en un la frequencia
			else { 													//creo un nou node amb freq 1 i sense num
				phone nou_p(num, "", 1);
				try{
					_taula[k] = new node_hash(nou_p, _taula[k]);
				}
				catch(error){
					delete _taula[k];
					throw;
				}
				++_n_elements;
			}
		}
		else { 														//creo un nou node amb freq 1 i sense num
			phone nou_p(num, "", 1);
			try{
				_taula[k] = new node_hash(nou_p, _taula[k]);
			}
			catch(error){
				delete _taula[k];
				throw;
			}
			++_n_elements;
		}
	}
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
// Cost = O(hash + elements sequencia) perque rehash es fa en molt poques ocacions
	if (es_buit()){
		nat z = hash(num, _mida);					//cost O(num.size())
		phone nou_p(num, name, 0);
		try{
			_taula[z] = new node_hash(nou_p, _taula[z]);
		}
		catch(error){
			delete _taula[z];
			throw;
		}
		++_n_elements;
	}
	else {
		float f_carrega = float(_n_elements)/float(_mida);
		if(f_carrega > 0.75) rehash(_mida, _taula);				//cost O(n*l)

		nat k = hash(num, _mida);
		node_hash* aux = consulta(num, k, _taula);			//cost O(hash + elements sequencia)

		if (aux != NULL){							//O(1)
			//si no le trobat de moment estic al ultim node de la llista, per tant, comprovo si, és igual o no.
			if (aux->_phone.numero() == num){
				phone modificat(num, name, aux->_phone.frequencia());
				(aux->_phone) = modificat;
			}
			else { 													//creo un nou node amb freq 0
				phone nou_p(num, name, 0);
				try{
					_taula[k] = new node_hash(nou_p, _taula[k]);
				}
				catch(error){
					delete _taula[k];
					throw;
				}
				++_n_elements;
			}
		}
		else { 													//creo un nou node amb freq 0
			phone nou_p(num, name, 0);
			try{
				_taula[k] = new node_hash(nou_p, _taula[k]);
			}
			catch(error){
				delete _taula[k];
				throw;
			}
			++_n_elements;
		}
	}
}

void call_registry::elimina(nat num) throw(error){
// Cost = O(hash + elements sequencia)
	if (es_buit()) throw error(ErrNumeroInexistent);	//cost O(1)
	nat i = hash(num, _mida);									//cost O(hash + elements sequencia)
	node_hash* aux = _taula[i];
	node_hash* ant = NULL;
	bool trobat = false;

	while(aux != NULL and not trobat){					//cost O(elements sequencia)
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
// Cost = O(hash + elements sequencia)
	if (es_buit()) return false;
	bool res = false;

	nat i = hash(num, _mida);
	node_hash* aux = consulta(num, i, _taula);		//cost O(hash + elements sequencia)

	if (aux != NULL){
		if (aux->_phone.numero() == num) res = true;
	}

	return res;
}

string call_registry::nom(nat num) const throw(error){
// Cost = O(hash + elements sequencia)
	if (es_buit()) throw error(ErrNumeroInexistent);
	nat i = hash(num, _mida);
	node_hash* aux = consulta(num, i, _taula); 		//cost O(hash + elements sequencia)

	string res;

	if (aux != NULL){
		if (aux->_phone.numero() == num) res = aux->_phone.nom();
		else throw error(ErrNumeroInexistent);
	}
	else throw error(ErrNumeroInexistent);

	return res;
}

nat call_registry::num_trucades(nat num) const throw(error){
// Cost = O(hash + elements sequencia)
	if (es_buit()) throw error(ErrNumeroInexistent);
	nat i = hash(num, _mida);
	node_hash* aux = consulta(num, i, _taula);		//cost O(hash + elements sequencia)
	nat res;

	if (aux != NULL){
		if (aux->_phone.numero() == num) res = aux->_phone.frequencia();
		else throw error(ErrNumeroInexistent);
	}
	else throw error(ErrNumeroInexistent);

	return res;
}

bool call_registry::es_buit() const throw(){
// Cost = O(1)
	return _n_elements == 0;
}

nat call_registry::num_entrades() const throw(){
// Cost = O(1)
	return _n_elements;
}

void call_registry::dump(vector<phone>& V) const throw(error){
// Cost = O()
	//nomes aqui es llança throw error(ErrNomRepetit)
	//volca  elements a una nova taula de hash amb funcio hash dels noms
	if(not es_buit()){
		node_hash** taula_aux = new node_hash*[_mida];
		try{
			for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;
		}
		catch(error){
			for(nat i=0; i < _mida; ++i) esborrar(taula_aux[i]);
    		delete[] taula_aux;
    		throw;
    	}

		for (nat i = 0; i < _mida; ++i){			//cost O(_mida * mº elements de la sequencia)
			if (_taula[i] != NULL){
				node_hash* aux = _taula[i];
				while (aux != NULL){				//cost (nº elements de la sequencia)
					nat j = hash_c(aux->_phone.nom(), _mida);
					try{
						taula_aux[j] = new node_hash(aux->_phone, taula_aux[j]);
					}
					catch (error){
						delete taula_aux[j];
						throw;
					}
					aux = aux->_seg;
				}
			}
		}
		//afegir nova taula de hash al vector i comprovar si hi ha noms iguals
		//fent lo de sinonims
		for (nat i = 0; i < _mida; ++i){							//cost O(_mida * (nº elements de la sequencia)²)
			if (taula_aux[i] != NULL and taula_aux[i]->_seg != NULL){
				node_hash* aux = taula_aux[i];

				//afegir a vector si no es igual en cap sinonim
				while (aux != NULL){								//cost O(nº elements de la sequencia)
					node_hash *x = aux->_seg;
					string usr = aux->_phone.nom();

					bool trobat = false;
					//comprova si els sinonims que queden si hi ha algun igual de nom
					while (x != NULL and !trobat){					//cost O(nº elements de la sequencia)
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
