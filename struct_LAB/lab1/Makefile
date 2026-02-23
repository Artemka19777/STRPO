object= build/rect.o build/MyString.o build/barrel.o build/textwrapper.o build/matrix.o


release: release.out
	./build/release.out

release.out: $(object) src/lab1.cpp
	g++ -o build/release.out $(object) src/lab1.cpp

build/debug.out: $(object) src/lab1.cpp
	g++ -g -o build/debug.out $(object) src/lab1.cpp

debug: build/debug.out
	gdb build/debug.out

build/rect.o: src/rect.cpp src/rect.hpp
	g++ -g -c -o build/rect.o src/rect.cpp 

build/textwrapper.o: src/textwrapper.cpp src/textwrapper.hpp
	g++ -g -c -o build/textwrapper.o src/textwrapper.cpp  

build/MyString.o: src/MyString.cpp src/MyString.hpp
	g++ -g -c -o build/MyString.o src/MyString.cpp  

build/barrel.o: src/barrel.cpp src/barrel.hpp
	g++ -g -c -o build/barrel.o src/barrel.cpp 

build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp 

#Версия сборки для проверки утечки памяти

build/leaks.out: $(object) src/lab1.cpp
	g++ -g -fsanitize=address -o build/leaks.out $(object) src/lab1.cpp
leaks: build/leaks.out
	./build/leaks.out<tests/input.txt
#Тесты

build/test_rect_basic_methods.out: build/rect.o tests/test_rect_basic_methods.cpp
	g++ -g -o build/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp build/rect.o

build/test_rect_properties.out: build/rect.o tests/test_rect_properties.cpp
	g++ -g -o build/test_rect_properties.out tests/test_rect_properties.cpp build/rect.o

build/test_rect_operations.out: build/rect.o tests/test_rect_operations.cpp
	g++ -g -o build/test_rect_operations.out tests/test_rect_operations.cpp build/rect.o

build/test_bounding_rect.out: build/rect.o tests/test_bounding_rect.cpp
	g++ -g -o build/test_bounding_rect.out tests/test_bounding_rect.cpp build/rect.o

test:build/test_rect_basic_methods.out build/test_rect_properties.out \
	build/test_rect_operations.out build/test_bounding_rect.out
	./build/test_rect_basic_methods.out
	./build/test_rect_properties.out
	./build/test_rect_operations.out
	./build/test_bounding_rect.out

clean:
	rm -f build/release.out build/debug.out $(object)