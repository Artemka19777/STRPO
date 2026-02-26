object= build/MyString.o build/BaseFile.o build/RleFile2.o build/Base32File2.o 

release: release.out
	./build/release.out
release.out: $(object) src/lab2.cpp
	g++ -o build/release.out $(object) src/lab2.cpp

debug: build/debug.out
	gdb build/debug.out

build/debug.out: $(object) src/lab2.cpp
	g++ -g -o build/debug.out $(object) src/lab2.cpp

build/MyString.o: src/MyString.cpp src/MyString.hpp
	g++ -g -c -o build/MyString.o src/MyString.cpp 
build/BaseFile.o: src/BaseFile.cpp src/BaseFile.hpp
	g++ -g -c -o build/BaseFile.o src/BaseFile.cpp 
build/Base32File2.o: src/Base32File2.cpp src/Base32File2.hpp
	g++ -g -c -o build/Base32File2.o src/Base32File2.cpp 

build/RleFile2.o: src/RleFile2.cpp src/RleFile2.hpp
	g++ -g -c -o build/RleFile2.o src/RleFile2.cpp 

#Тест
test: build/test.out
	./build/test.out

build/test.out: $(object) src/test.cpp
	g++ -g -o build/test.out $(object) src/test.cpp
#Утечка
build/leaks.out: $(object) src/lab2.cpp
	g++ -g -fsanitize=address -o build/leaks.out $(object) src/lab2.cpp
leaks: build/leaks.out
	./build/leaks.out

clean:
	rm -f build/release.out build/debug.out $(object)