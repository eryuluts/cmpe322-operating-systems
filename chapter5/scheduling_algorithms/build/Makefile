#SRCDIR given by upper-make

driver.exe: cpu.obj scheduler.obj driver.obj
	link driver.obj scheduler.obj cpu.obj /OUT:driver.exe

cpu.obj : $(SRCDIR)/cpu.c $(SRCDIR)/cpu.h $(SRCDIR)/scheduler.h
	$(CC) /c $(SRCDIR)/cpu.c

scheduler.obj : $(SRCDIR)/scheduler.c $(SRCDIR)/scheduler.h\
$(SRCDIR)/cpu.h $(SRCDIR)/list.h 
	$(CC) /c $(SRCDIR)/scheduler.c

driver.obj : $(SRCDIR)/driver.c $(SRCDIR)/list.h 
	$(CC) /c /D$(ALG) $(SRCDIR)/driver.c 

driver_alg: cpu.obj scheduler.obj
	$(CC) /c /D$(ALG) $(SRCDIR)/driver.c 
	link driver.obj scheduler.obj cpu.obj /OUT:driver.exe
	
clean:
	rm cpu.obj scheduler.obj driver.obj driver.exe
