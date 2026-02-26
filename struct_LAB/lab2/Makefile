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

test_base: build/test_base.out
	./build/test_base.out

build/test_base.out: $(object) test/BaseFileTEST.cpp
	g++ -g -o build/test_base.out $(object) test/BaseFileTEST.cpp

test_base32: build/test_base32.out
	./build/test_base32.out

build/test_base32.out: $(object) test/Base32FileTEST.cpp
	g++ -g -o build/test_base32.out $(object) test/Base32FileTEST.cpp

test_rle: build/test_rle.out
	./build/test_rle.out

build/test_rle.out: $(object) test/RleFileTEST.cpp
	g++ -g -o build/test_rle.out $(object) test/RleFileTEST.cpp

test_ifiles: build/test_ifiles.out
	./build/test_ifiles.out

build/test_ifiles.out: $(object) test/IFilesTEST.cpp
	g++ -g -o build/test_ifiles.out $(object) test/IFilesTEST.cpp

# Запуск всех тестов
test: test_base test_base32 test_rle test_ifiles

#Утечка
build/leaks.out: $(object) src/lab2.cpp
	g++ -g -fsanitize=address -o build/leaks.out $(object) src/lab2.cpp
leaks: build/leaks.out
	./build/leaks.out

clean:
	rm -f build/release.out build/debug.out $(object)