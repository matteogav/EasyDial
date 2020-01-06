#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
  nat i = 0;
  bool fi = false;
  nat num_tlf = 0;
  string nom;
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
	
  while(i < input.length() and not fi){
    try{
      if(input[i] == phone::ENDCHAR){
				nom = easy.seguent(phone::ENDPREF);
        num_tlf = easy.num_telf();
        ++i;
      }
      else if(input[i] == phone::DELETECHAR){
        nom = easy.anterior();
        num_tlf = easy.num_telf();
        ++i;
      }
      else{                                                               
        nom = easy.seguent(input[i]);
        num_tlf = easy.num_telf();
        ++i;
      }
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
