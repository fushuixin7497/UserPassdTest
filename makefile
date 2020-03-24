build:./UPT

./UPT:UserPassdTest.cpp
	g++ -g -Wall $^ -I ./ -lcrypt -Wl,-rpath,. -o $@

delete:
	rm -rf *.cpp *.h
clean:
	rm -fr ./UPT