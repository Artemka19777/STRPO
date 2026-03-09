object = build/Circle.o 
release: release.out
	./build/release.out

release.out: $(object) src/lab4.cpp
	g++ -o build/release.out $(object) src/lab4.cpp

build/Circle.o: src/Circle.cpp src/Circle.hpp
	g++ -g -c -o build/Circle.o src/Circle.cpp 

build/leaks.out: $(object) src/lab4.cpp
	g++ -g -fsanitize=address -o build/leaks.out $(object) src/lab4.cpp
leaks: build/leaks.out
	./build/leaks.out