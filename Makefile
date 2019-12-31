CC = g++ -c
CO= g++ -o
opcions= -std=c++98 -g -O0 -ansi -Wall

#compilar: g++ -c -Wall arxiu.cpp
#montar: g++ -o nom_executable.e arxiu1.o arxiu2.o -lesin

TARGETS  = phone prova_phone call_registry easy_dial dialog	monta comprova_phone comprova_call_registry comprova_easy_dial rmout cleano clean
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
	$(CC) $(opcions) phone.cpp
	$(CC) $(opcions) call_registry.cpp
	$(CC) $(opcions) easy_dial.cpp
	$(CC) $(opcions) dialog.cpp
	$(CC) $(opcions) driver_easydial.cpp
	$(CO) driver.e driver_easydial.o phone.o call_registry.o easy_dial.o dialog.o -lesin

comprova_phone:
	echo "time ./driver.e < jp_public/jp_public_phone.in >& jp_public/jp_phone.out && diff jp_public/jp_phone.out jp_public/jp_phone.res"

comprova_call_registry:
	echo "time ./driver.e < jp_public/jp_public_call_registry.in >& jp_public/jp_call_registry.out && diff jp_public/jp_call_registry.out jp_public/jp_call_registry.res"

comprova_easy_dial:
	echo "time ./driver.e < jp_public/jp_public_easy_dial.in >& jp_public/jp_easy_dial.out && diff jp_public/jp_easy_dial.out jp_public/jp_easy_dial.res"

comprova:
	echo "time ./driver.e < jp_public.in >& jp.out && diff jp.out jp_public.res"

rmout:
	rm jp_public/*.out

rmo:
	rm *.o

clean:
	rm *.e *.o *.out