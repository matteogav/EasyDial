#include <iostream>
#include <istream>
#include "phone.hpp"

using namespace std;

int main (){
	nat t;
	nat f;
	string c;

	cout<<"Entra un contacte: ";
	cin>>c;
	cout<<"\nQuin telefon te? ";
	cin>>t;
	cout<<"\nNumero de trucades: ";
	cin>>f;

	phone T1(t, c, f);
	phone T2(666666666, "Thomas Turbao", 5);
	phone T3(677777777, "Dolores De Piernas", 10);
	phone T4(688888888, "Macias Pajas", 2);

	cout<<"contacte T1->> "<<T1.nom()<<"|| telefon --> "<<T1.numero()<<"|| trucades --> "<<T1.frequencia()<<endl;
	cout<<"contacte T2->> "<<T2.nom()<<"|| telefon --> "<<T2.numero()<<"|| trucades --> "<<T2.frequencia()<<endl;
	cout<<"contacte T3->> "<<T3.nom()<<"|| telefon --> "<<T3.numero()<<"|| trucades --> "<<T3.frequencia()<<endl;
	cout<<"contacte T4->> "<<T4.nom()<<"|| telefon --> "<<T4.numero()<<"|| trucades --> "<<T4.frequencia()<<endl;
	
	cout<<endl<<"T3++"<<endl;
	T3++;
	cout<<"contacte T3->> "<<T3.nom()<<"|| telefon --> "<<T3.numero()<<"|| trucades --> "<<T3.frequencia()<<endl;
	cout<<endl<<"++T3"<<endl;
	++T3;
	cout<<"contacte T3->> "<<T3.nom()<<"|| telefon --> "<<T3.numero()<<"|| trucades --> "<<T3.frequencia()<<endl;

	cout<<"T1 == T1: "<<(T1==T1);
	cout<<" || T1 == T2: "<<(T1==T2)<<endl;
	cout<<"T1 != T1: "<<(T1!=T1);
	cout<<" || T1 != T2: "<<(T1!=T2)<<endl;
	cout<<"T1 < T2: "<<(T1<T2);
	cout<<" || T1 < T4: "<<(T1<T4);
	cout<<" || T1 < T3: "<<(T1<T3);
	cout<<" || T1 > T2: "<<(T1>T2);
	cout<<" || T1 > T4: "<<(T1>T4)<<endl;
	cout<<"T1 <= T2: "<<(T1<=T2);
	cout<<" || T1 <= T4: "<<(T1<=T4);
	cout<<" || T1 <= T1: "<<(T1<=T1)<<endl;
	cout<<"T1 >= T2: "<<(T1>=T2);
	cout<<" || T1 >= T4: "<<(T1>=T4);
	cout<<" || T1 >= T1: "<<(T1>=T1)<<endl;
}