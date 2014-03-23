Mail.o : Socket/Socket.o Base64/Base64.o Mail.hpp Mail.cpp
	$(CC) $(CFLAGS) Mail.hpp Mail.cpp -c

Socket/Socket.o : 
	@(cd Socket && $(MAKE))

Base64/Base64.o :
	@(cd Base64 && $(MAKE))

clean :
	@(cd Socket && $(MAKE) clean)
	@(cd Base64 && $(MAKE) clean)
	rm -rf *.{o,gch}




