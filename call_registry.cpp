#include "call_registry.hpp"
#include <vector>

nat call_registry::hash(nat x) const{
	long y = ((x * x * 31415926) >> 4)%_mida;

	return y;
}

void call_registry::rehash(){

}

nat call_registry::consulta(nat num) const{
	nat i = hash(num);
	nat prilliure = -1, cont = 0;

	while ((_taula[i]._phone).numero() != num and _taula[i]._est != lliure and cont < _mida){
		++cont;
		if (_taula[i]._est == esborrat and prilliure == -1) prilliure = i;
		i = (i+1)%_mida;
	}
	if (_taula[i]._est == lliure and (_taula[i]._phone).numero() != num){
		if (prilliure != -1) i = prilliure;
	}
	
	return i;
}

void call_registry::afegir(phone p){
	nat i = consulta(p.numero());

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() != p.numero()) rehash();
	if (_taula[i]._est != ocupat) ++_quants;

	_taula[i]._phone = p;
	_taula[i]._est = ocupat;
}

call_registry::call_registry() throw(error){
	_mida = 10;
	_taula = new node_hash [_mida];
	_quants = 0;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){

}
call_registry& call_registry::operator=(const call_registry& R) throw(error){

}
call_registry::~call_registry() throw(){

}

void call_registry::registra_trucada(nat num) throw(error){
	nat i = consulta(num);

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() == num) (_taula[i]._phone)++;
	else {
		phone nou(num, "", 1);
		if (_quants < _mida) afegir(nou);
		else rehash();
	}
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){	
	nat i = consulta(num);

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() == num){
		phone modificat(num, name, (_taula[i]._phone).frequencia());
		(_taula[i]._phone) = modificat;
	}
	else {
		phone nou(num, name, 0);
		if (_quants < _mida) afegir(nou);
		else rehash();
	}
}

void call_registry::elimina(nat num) throw(error){
	nat i = consulta(num);

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() == num) _taula[i]._est = esborrat;
	else throw(ErrNumeroInexistent);
}

bool call_registry::conte(nat num) const throw(){
	nat i = consulta(num);
	bool res;

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() == num) res = true;
	else res = false;

	return res;
}

string call_registry::nom(nat num) const throw(error){
	nat i = consulta(num);
	string res;

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() == num) res = (_taula[i]._phone).nom();
	else throw(ErrNumeroInexistent);

	return res;
}

nat call_registry::num_trucades(nat num) const throw(error){
	nat i = consulta(num), res;

	if (_taula[i]._est == ocupat and (_taula[i]._phone).numero() == num) res = (_taula[i]._phone).frequencia();
	else throw(ErrNumeroInexistent);

	return res;
}

bool call_registry::es_buit() const throw(){
	return _quants == 0;
}

nat call_registry::num_entrades() const throw(){
	return _quants;
}

void call_registry::dump(vector<phone>& V) const throw(error){
	//nomes aqui es llança throw(ErrNomRepetit)
}
