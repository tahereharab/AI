all: player verifier
	cp player playerA
	cp player playerB
	
player: player.o heuristics.o Tree.o
	g++ -o player player.o heuristics.o Tree.o

player.o: player.cpp heuristics.h
	g++ -c -Wall player.cpp

heuristics.o: heuristics.cpp heuristics.h
	g++ -c -Wall heuristics.cpp

Tree.o: Tree.cpp Tree.h
	g++ -c -Wall Tree.cpp

verifier: verifier.cpp
	g++ -Wall -o verifier verifier.cpp

clean:
	-rm player verifier player[A-B] timedplayer[A-B] brd_[a-b] *.o resp_[a-b]
