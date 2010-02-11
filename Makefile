SRCDIR = src
INCLUDEDIR = include
OBJDIR = build

CCFLAGS = -Wall `R CMD config --cppflags` -I$(INCLUDEDIR) -I/usr/local -c -shared -fPIC -g
LDFLAGS = `R CMD config --ldflags` -shared /usr/local/bin/yap.dll
CC = gcc
SRC = $(subst $(SRCDIR)/,, $(wildcard $(SRCDIR)/*.c))
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: YapR

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) $^ -o $@

YapR: $(OBJ)
	$(CC) $(LDFLAGS) -o YapR.dll $^ 

clean:
	rm -f $(OBJ) $(SRCDIR)/*~ YapR YapR.exe YapR.dll
