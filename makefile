IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) `pkg-config --cflags glib-2.0`

SDIR=src
ODIR=obj
LDIR=lib

#Libs are included without the lib prefix because -l does that for you
LIBS=-lm `pkg-config --libs glib-2.0`

#H files go here
_DEPS = node.h graph.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#Target object files go here (There basically the c files)
_OBJ = main.o node.o graph.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

#The end program results name
main : $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

