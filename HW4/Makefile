objects = main4d.o Path.o Country.o CrossOverMap.o City.o Population.o random.o common.o

all: genalg

genalg: $(objects)
	g++ -g -o genalg main4d.o Path.o Country.o CrossOverMap.o Population.o random.o City.o common.o

main4d.o: main4d.cpp defs.h randomc.h
	g++ -c -Wall main4d.cpp

Path.o: Path.cpp Path.h defs.h
	g++ -c -Wall Path.cpp

Country.o: Country.cpp Country.h defs.h
	g++ -c -Wall Country.cpp

CrossOverMap.o: CrossOverMap.cpp CrossOverMap.h defs.h
	g++ -c -Wall CrossOverMap.cpp

Population.o: Population.cpp Population.h defs.h
	g++ -c -Wall Population.cpp

random.o: random.cpp randomc.h
	g++ -c -Wall random.cpp

common.o: common.h common.cpp
	g++ -c -Wall common.cpp


City.o:	City.cpp City.h defs.h
	g++ -c -Wall City.cpp

clean: 
	-rm *.o core genalg


