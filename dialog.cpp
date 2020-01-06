#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
  nat i = 0;
  bool fi = false;
  nat num_tlf = 0;       // o num_tlf = easy.num_telf();
  string nom;
  easy.inici();
	cout << "PUTO NOM:" << easy.seguent(input[i]) << endl;
	
  while(i < input.length() and not fi){
    cout << "LLETRA: " << input[i] <<endl;
    try{
      if(input[i] == phone::ENDCHAR){
				cout << "aqui" <<endl;
        num_tlf = easy.num_telf();
        fi = true;
        i++;
      }
      else if(input[i] == phone::DELETECHAR){
        cout << "aqui2" <<endl;
        nom = easy.anterior();
        num_tlf = easy.num_telf();
        i++;
      }
      else{              
				cout << "aqui3" <<endl;                
        num_tlf = easy.num_telf();       
        i++;                              
        nom = easy.seguent(input[i]);
				cout << "nom:"<<nom<<endl;
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
