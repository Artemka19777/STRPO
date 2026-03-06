object = build/MyString.o build/Matrix.o build/WorkerDb.o build/Notification.o

release: build/release.out 
	./build/release.out
build/release.out: $(object) src/lab3.cpp
	g++ -o build/release.out $(object) src/lab3.cpp

build/Matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -c -o build/Matrix.o src/matrix.cpp

build/MyString.o: src/MyString.cpp src/MyString.hpp
	g++ -c -o build/MyString.o src/MyString.cpp
build/WorkerDb.o: src/WorkerDb.cpp src/WorkerDb.hpp
	g++ -c -o build/WorkerDb.o src/WorkerDb.cpp

build/Notification.o: src/Notification.hpp src/Notification.cpp
	g++ -c -o build/Notification.o src/Notification.cpp

build/test_priority.out: build/Notification.o test/test_priority.cpp build/MyString.o
	g++ -g -o build/test_priority.out test/test_priority.cpp build/Notification.o build/MyString.o

test: build/test_priority.out 
	./build/test_priority.out

debug: build/debug.out
	gdb build/debug.out

build/debug.out: $(object) src/lab3.cpp
	g++ -g -o build/debug.out $(object) src/lab3.cpp

clean:
	rm -f build/release.out build/debug.out $(object)