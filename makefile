#---------------------------------
# INITIALISATION DES VARIABLES
#---------------------------------

# Indiquer le compilateur
CXX= gcc

# Les fichiers sources de l'application
SRCDIR=src
SRC=$(wildcard $(SRCDIR)/*.c)

OBJDIR=bin
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INCLUDES_DIR=include

EXEC= trainsimulator

# Les chemins ou se trouvent les fichiers a inclure
INCLUDE= -I$(INCLUDES_DIR)

# Options de compilation.
CXXFLAGS=  $(INCLUDE)

# Les librairies avec lesquelle on va effectueller l'edition de liens
LIBS=-lpthread


#-----------
# LES CIBLES
#-----------
all : $(EXEC)

$(EXEC) :  $(OBJ)
	$(CXX) -o $(OBJDIR)/$@ $^ $(CXXFLAGS) $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES_DIR)/*.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY : clean
clean:
	rm -rf $(OBJDIR)/*

run : clean all
	./bin/$(EXEC)
