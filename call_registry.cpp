#include "call_registry.hpp"
#include <vector>

call_registry::node_hash::node_hash(const phone &p, node_hash* seg) throw(error){
// Cost = O(1)
	_phone = p;
	_seg = seg;
}

nat call_registry::hash(nat x) const throw(){
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
	return n%_mida;
}

nat call_registry::hash_c(string nom) const throw(){
// Cost = O(nom.length())
	nat n = 0;
	for (nat i = 0; i < nom.length(); ++i) n = n + nom[i]*i;
	n = n%_mida;
	return n;
}

void call_registry::rehash() throw(){
// Cost = O(n) --> mida taula + cada node de la sequencia de la posicio i
	nat mida = _mida;
	_mida *= 2;
	node_hash** aux = _taula;
	node_hash** _taula_ = new node_hash*[_mida];
	try{
		for(nat i=0; i < _mida; ++i) _taula_[i] = NULL;
	}
	catch(error){
		for(nat i=0; i < _mida; ++i) esborrar(_taula_[i]);
    	delete[] _taula_;
    	throw;
    }

	// Redistribuir els elements de la taula vella(_mida) a la taula nova(_mida*2)
	for (nat i = 0; i < mida; ++i){			// per cada posicio i de la taula abans de rehash
		node_hash* x = aux[i];
		while (x != NULL){					//per cada node de la sequencia de la posicio i
			nat j = hash(x->_phone.numero());

			try{
				//creo nou node i el poso a davant
				_taula_[j] = new node_hash(x->_phone, _taula_[j]);
			}
			catch(error){
				delete _taula_[j];
				throw;
			}
			x = x->_seg;
		}
	}
	for (nat i = 0; i < mida; ++i) esborrar(_taula[i]);
	delete[] _taula;
	_taula = _taula_;
}

call_registry::node_hash* call_registry::consulta(nat num, nat num_hash) const throw(){
// Cost = O(hash + elements de la sequencia)
	node_hash* res = _taula[num_hash];
	bool trobat = false;

	// Recorrer la llista d'elements fins a trobar el que busquem, sinó el trobem el node serà NULL
	if (res != NULL){
		while (not trobat and res != NULL){
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
	_mida = 64;
	_n_elements = 0;
	// Crear tota la taula a NULL
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

	// Copiar totes les llistes de cada element de la taula
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
    delete[] taula_aux;
    throw;
  }

	// Copiar totes les llistes de cada element de la taula
	if(this != &R){
		for(nat i=0; i < _mida; ++i){
			node_hash* aux = R._taula[i];
			node_hash* ant = NULL;
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
		for (nat i = 0; i < _mida; ++i) esborrar(_taula[i]);
		delete[] _taula;
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
	float f_carrega = float(_n_elements)/float(_mida);
	if(f_carrega > 0.75) rehash();				//cost O(n*l)

	// Busquem posició de la taula i mirem si hi és
	nat k = hash(num);
	node_hash* aux = consulta(num, k);			//cost O(hash + elements sequencia)

	// Si hi és vol dir que aux != NULL, per tant, sumo en un la frequencia
	if (aux != NULL) ++aux->_phone;
	// Si aux == NULL vol dir que no hi és. Creo un nou node amb freq 1 i sense nom
	else {
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

void call_registry::assigna_nom(nat num, const string& name) throw(error){
// Cost = O(hash + elements sequencia) perque rehash es fa en molt poques ocacions
	float f_carrega = float(_n_elements)/float(_mida);
	if(f_carrega > 0.75) rehash();				//cost O(n*l)

	// Busquem posició de la taula i mirem si hi és
	nat k = hash(num);
	node_hash* aux = consulta(num, k);			//cost O(hash + elements sequencia)

	// Si aux != NULL vol dir que l'hem trobat i per tant, canviem el nom.
	if (aux != NULL){							//O(1)
		phone modificat(num, name, aux->_phone.frequencia());
		(aux->_phone) = modificat;
	}
	// Si aux == NULL vol dir que no l'hem robta i per tant, afegim un nou telefon amb freq = 0.
	else {
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

void call_registry::elimina(nat num) throw(error){
// Cost = O(hash + elements sequencia)
	// Si està buida no existirà cap telèfon.
	if (es_buit()) throw error(ErrNumeroInexistent);	//cost O(1)
	nat i = hash(num);									//cost O(hash + elements sequencia)
	node_hash* aux = _taula[i];
	node_hash* ant = NULL;
	bool trobat = false;

	// Mirem en llista de la posició de la taula i que dona hash(), si hi és
	while(aux != NULL and not trobat){					//cost O(elements sequencia)
		// Si hi és marquem trobat = true i en saltem aquest element i el borrem
		if(aux->_phone.numero() == num){
			trobat = true;
			// Si estem al principi el punter de la posició i de la taula apunta a seguent.
			if(ant == NULL) _taula[i] = aux->_seg;
			// Sinó un salt normal de anterior a seguent.
			else ant->_seg = aux->_seg;
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

	nat i = hash(num);
	node_hash* aux = consulta(num, i);		//cost O(hash + elements sequencia)

	// Si aux != NULL vol dir que l'hem trobat
	if (aux != NULL) res = true;
	// Sinó ja teniem que res = false

	return res;
}

string call_registry::nom(nat num) const throw(error){
// Cost = O(hash + elements sequencia)
	if (es_buit()) throw error(ErrNumeroInexistent);
	nat i = hash(num);
	node_hash* aux = consulta(num, i); 		//cost O(hash + elements sequencia)

	string res;

	// Si aux != NULL vol dir que l'hem trobat
	if (aux != NULL) res = aux->_phone.nom();
	// Sinó, llancem error
	else throw error(ErrNumeroInexistent);

	return res;
}

nat call_registry::num_trucades(nat num) const throw(error){
// Cost = O(hash + elements sequencia)
	if (es_buit()) throw error(ErrNumeroInexistent);
	nat i = hash(num);
	node_hash* aux = consulta(num, i);		//cost O(hash + elements sequencia)
	nat res;

	// Si aux != NULL vol dir que l'hem trobat
	if (aux != NULL) res = aux->_phone.frequencia();
	// Sinó treiem error
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
// Cost = O(_mida * (nº elements de la sequencia)²)
	//volca elements de la hash() normal, si no és buida, a una nova taula de hash amb funcio hash que ordena per noms
	if(not es_buit()){
		node_hash** taula_aux = new node_hash*[_mida];
		try{
			for(nat i=0; i < _mida ; ++i) taula_aux[i] = NULL;
		}
		catch(error){
    	delete[] taula_aux;
    	throw;
    }

		for (nat i = 0; i < _mida; ++i){			//cost O(_mida * mº elements de la sequencia)
			if (_taula[i] != NULL){
				node_hash* aux = _taula[i];
				while (aux != NULL){				//cost (nº elements de la sequencia)
					nat j = hash_c(aux->_phone.nom());
					try{
						taula_aux[j] = new node_hash(aux->_phone, taula_aux[j]);
					}
					catch (error){
						for(nat i=0; i < _mida; ++i) esborrar(taula_aux[i]);
						delete taula_aux[j];
						throw;
					}
					aux = aux->_seg;
				}
			}
		}
		//afegir la nova taula de hash ordenada per noms al vector i comprovar si hi ha noms iguals
		for (nat i = 0; i < _mida; ++i){							//cost O(_mida * (nº elements de la sequencia)²)
			if (taula_aux[i] != NULL and taula_aux[i]->_seg != NULL){
				node_hash* aux = taula_aux[i];

				//afegir a vector si no es igual en cap "sinonim"
				while (aux != NULL){								//cost O(nº elements de la sequencia)
					node_hash *x = aux->_seg;
					string usr = aux->_phone.nom();

					bool trobat = false;
					//comprova si els "sinonims" que queden si hi ha algun igual de nom
					while (x != NULL and !trobat){					//cost O(nº elements de la sequencia)
						if(usr != "" and usr == x->_phone.nom()) trobat = true;
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
		for (nat i = 0; i < _mida; ++i) esborrar(taula_aux[i]);
		delete[] taula_aux;
	}
}
