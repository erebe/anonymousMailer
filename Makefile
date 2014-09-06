export CXX=g++
export CXXFLAGS=-W -Wall -O2 -pedantic -std=c++0x -pipe

SOURCES=src/Mail/Mail.o \
	src/Mail/Socket/Socket.o \
	src/Mail/Base64/Base64.o

cli : src/Cli/main_cli.o $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o mailme_$@

gui :
	@(cd src/Interface && $(MAKE))
	mv src/Interface/mailme_gui .

clean :
	find -name '*.o' -exec rm {} \;
