object= build/MyString.o build/BaseFile.o

release: release.out
	./build/release.out
release.out: $(object) src/lab2.cpp
	g++ -o build/release.out $(object) src/lab2.cpp

build/MyString.o: src/MyString.cpp src/MyString.hpp
	g++ -g -c -o build/MyString.o src/MyString.cpp  
build/MyString.o: src/MyString.cpp src/MyString.hpp
	g++ -g -c -o build/MyString.o src/MyString.cpp 
build/BaseFile.o: src/BaseFile.cpp src/BaseFile.hpp
	g++ -g -c -o build/BaseFile.o src/BaseFile.cpp 