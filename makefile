enigma: main.o Statically_Connected_Components.o Rotor.o IO.o Enigma.o Cable.o Errors.o
	g++ -Wall -g main.o Statically_Connected_Components.o Rotor.o IO.o Enigma.o Cable.o Errors.o -o enigma

main.o: main.cpp Enigma.hpp Errors.hpp
	g++ -Wall -g -c main.cpp

Enigma.o: Enigma.cpp Enigma.hpp
	g++ -Wall -g -c Enigma.cpp

IO.o: IO.cpp IO.hpp Constants.hpp
	g++ -Wall -g -c IO.cpp

Statically_Connected_Components.o: Statically_Connected_Components.cpp Statically_Connected_Components.hpp
	g++ -Wall -g -c Statically_Connected_Components.cpp

Cable.o: Cable.cpp Cable.hpp
	g++ -Wall -g -c Cable.cpp
	
Rotor.o: Rotor.cpp Rotor.hpp
	g++ -Wall -g -c Rotor.cpp

Errors.o: Errors.cpp Errors.hpp
	g++ -Wall -g -c Errors.cpp

clean:
	rm -f *.o enigma
