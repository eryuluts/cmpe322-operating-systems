#SRCDIR given by upper-make

producer-consumer.exe: buffer.obj producer-consumer.obj
	link buffer.obj producer-consumer.obj /OUT:producer-consumer.exe

buffer.obj : $(SRCDIR)/buffer.c $(SRCDIR)/buffer.h
	$(CC) /c $(SRCDIR)/buffer.c

producer-consumer.obj : $(SRCDIR)/producer-consumer.c $(SRCDIR)/buffer.h
	$(CC) /c $(SRCDIR)/producer-consumer.c
	
clean:
	rm buffer.obj producer-consumer.obj producer-consumer.exe
