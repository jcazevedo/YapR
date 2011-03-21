SRCDIR = src
INCLUDEDIR = include
OBJDIR = build
YAPLIBDIR = /home/jcazevedo/work/yap-6

CCFLAGS = -Wall `R CMD config --cppflags` -I$(INCLUDEDIR) -I/usr/local -c -shared -fPIC -g -fno-stack-protector
LDFLAGS = `R CMD config --ldflags` -shared $(YAPLIBDIR)/libYap.a
CC = gcc
SRC = $(subst $(SRCDIR)/,, $(wildcard $(SRCDIR)/*.c))
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: YapR

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) $^ -o $@

YapR: $(OBJ)
	ld $(LDFLAGS) -o YapR.so $^ 

clean:
	rm -f $(OBJ) $(SRCDIR)/*~ YapR YapR.exe YapR.so
