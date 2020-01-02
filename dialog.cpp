#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
  nat i = 0;
  bool fi = false;
  nat num_tlf = 0;       // o num_tlf = easy.num_telf();

  easy.inici();
  while(i < input.length()-1 and not fi){
    if(input[i] == phone::ENDCHAR){    //??
      num_tlf = easy.num_telf();
      fi = true;
      i++;
    }
    else if(input[i] == phone::DELETECHAR){
      easy.anterior();
      num_tlf = easy.num_telf();
      i++;
    }
    else{                               //Ni la variable 'i' ni 'num_tlf' es poden factoritzar i treure fora,
      num_tlf = easy.num_telf();        //segueixen un ordre de la manera que se li dona el valor segons l'opcio
      i++;                              //encara que aixo un 'prototip' del que crec que podria ser la solucio
      easy.seguent(input[i]);
    }
  }
}
