export CC=g++
export CFLAGS=-W -Wall -O2 -pedantic -std=c++0x -pipe

SOURCES=src/Mail/Mail.o \
	src/Mail/Socket/Socket.o \
	src/Mail/Base64/Base64.o

cli : src/Cli/main_cli.o $(SOURCES)
	$(CC) $(CFLAGS) $^ -o mailme_$@

gui :
	@(cd src/Interface && $(MAKE))
	mv src/Interface/mailme_gui .

src/Mail/Mail.o :
	@(cd src/Mail/ && $(MAKE))

clean :
	@(cd src/Mail/ && $(MAKE) clean)
	@(cd src/Cli/ && $(MAKE) clean)
	@(cd src/Interface/ && $(MAKE) clean)
	rm -rf *.{o,gch} mailme_*
