CC = g++ -c
CO= g++ -o
opcions= -std=c++98 -g -O0 -ansi -Wall

#compilar: g++ -c -Wall arxiu.cpp
#montar: g++ -o nom_executable.e arxiu1.o arxiu2.o -lesin

TARGETS  = phone call_registry easy_dial dialog	monta
all: $(TARGETS)

phone:
	$(CC) $(opcions) phone.cpp

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

clean:
	rm executable phone.o call_registry.o easy_dial.o dialog.o