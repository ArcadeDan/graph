final:
	g++ -std=c++2a -g -Wall -c *.cpp
	g++ -std=c++2a -g -Wall -o program  *.o
	rm *.o
debug:
	g++ -std=c++2a  -g -Wall -c *.cpp
	g++ -std=c++2a  -g -Wall -o program  *.o
	rm *.o
