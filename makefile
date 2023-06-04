SRCDIR = ./src
BUILDDIR = ./build
EXE = airwatcher
SRC = $(shell find $(SRCDIR) -name *.cpp)
OBJ = ${SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o}
CC = g++
CFLAGS = -ansi -pedantic -Wall -std=c++11 -O3
DEBUGFLAGS = -DDEBUG -g
LDFLAGS = 
RM = rm
MAKE = make
MKDIR = mkdir
CLANGFORMAT = clang-format
CLANGTIDY = clang-tidy
CPPCHECK = cppcheck
DEPDIR = $(BUILDDIR)/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
CP = cp

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEPDIR)/%.d | $(DEPDIR)
	@$(MKDIR) -p $(dir $@)
	$(CC) $(DEPFLAGS) -o $@ -c $< $(CFLAGS)

DEBUG:
	$(MAKE) clean
	$(MAKE) CFLAGS='$(CFLAGS) $(DEBUGFLAGS)'

format:
	$(CLANGFORMAT) -i $(SRCDIR)/*.cpp $(SRCDIR)/*.h 

tidy:
	$(CLANGTIDY) $(SRC) -header-filter=.*

cppcheck:
	$(CPPCHECK) $(SRC) --enable=all

clean:
	$(RM) -f $(OBJ) $(EXE) core

$(DEPDIR): ; @$(MKDIR) -p $@

DEPFILES = $(SRC:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))
