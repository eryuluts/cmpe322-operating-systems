#SRCDIR given by upper-make

driver.exe: cpu.obj scheduler.obj driver.obj
	link driver.obj scheduler.obj cpu.obj /OUT:driver.exe

cpu.obj : $(SRCDIR)/cpu.c $(SRCDIR)/cpu.h $(SRCDIR)/scheduler.h
	cl /c $(SRCDIR)/cpu.c

scheduler.obj : $(SRCDIR)/scheduler.c $(SRCDIR)/scheduler.h $(SRCDIR)/cpu.h\
$(SRCDIR)/list.h 
	cl /c $(SRCDIR)/scheduler.c

driver.obj : $(SRCDIR)/driver.c $(SRCDIR)/list.h 
	cl /D$(ALG) /c $(SRCDIR)/driver.c

clean:
	rm cpu.obj scheduler.obj driver.obj driver.exe
