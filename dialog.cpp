#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
  nat i = 0;
  bool fi = false;
  nat num_tlf = 0;
  string nom;
  // Afegir el inici al vector perquè sempre passa per allà
  try{
    nom = easy.inici();
		answers.push_back(nom);
		num_tlf = easy.num_telf();
	}
	catch(error e){
    num_tlf = 0;
		fi = true;
    answers.push_back(e.mensaje());
  }	
	// Mirem cada lletra de input i si dóna error acaba el programa
  while(i < input.length() and not fi){
    try{
      // Si és igual a '\0' mirem seguent de '\0'
      if(input[i] == phone::ENDCHAR){
				nom = easy.seguent(phone::ENDPREF);
        num_tlf = easy.num_telf();
        ++i;
      }
      // Si és igual a '<' fem anterior()
      else if(input[i] == phone::DELETECHAR){
        nom = easy.anterior();
        num_tlf = easy.num_telf();
        ++i;
      }
      // Si és una cosa diferent a '\0' i '<' fem seguent de la lletra
      else{                                                               
        nom = easy.seguent(input[i]);
        num_tlf = easy.num_telf();
        ++i;
      }
      // afegim el nom que s'ha extret
      answers.push_back(nom);
    }
    catch(error e){
      fi = true;
      num_tlf = 0;
      answers.push_back(e.mensaje());
    }
  }
  numtelf = num_tlf;
}
