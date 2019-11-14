CC = g++ -c
CO= g++ -o
opcions= -std=c++98 -g -O0 -ansi -Wall

#compilar: g++ -c -Wall arxiu.cpp
#montar: g++ -o nom_executable.e arxiu1.o arxiu2.o -lesin

TARGETS  = phone call_registry easy_dial dialog	monta clean cleano prova_phone
all: $(TARGETS)

phone:
	$(CC) $(opcions) phone.cpp

prova_phone:
	$(CC) $(opcions) phone.cpp
	$(CC) $(opcions) phone_prova.cpp
	$(CO) phone_prova phone_prova.o phone.o -lesin

call_registry:
	$(CC) $(opcions) call_registry.cpp

easy_dial:
	$(CC) $(opcions) easy_dial.cpp

dialog:
	$(CC) $(opcions) dialog.cpp

monta:
	$(CO) executable phone.o call_registry.o easy_dial.o dialog.o -lesin

#comprova:
#	echo "time ./driver < jp1.in >& jp1.out && diff jp1.out jp1.res"

#rmout:
#	rm jp_public/*.out

cleano:
	rm *.o

clean:
	rm executable phone.o call_registry.o easy_dial.o dialog.o