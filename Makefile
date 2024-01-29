#**********************************************************************
# Makefile 
#
# Author : wissem chiha 
# Date   : Januray 2024
# Notes  : built with GNU Make 4.3 
#**********************************************************************
# Set the source directory 
SRCDIR := src
# Set the object directory
OBJDIR := obj
# Set the bin directory
BINDIR := bin
#**********************************************************************
# Set The Compiler 
CC :=g++ 
# Compiler flags
CFLAGS :=  -I./mujoco/include  -I./glfw/include -I./include -I./glm
# Linker flags
LDFLAGS := -L./mujoco/bin -lmujoco  -L./glfw/lib -lglfw3
# List all the source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

# List all object files 
OBJECTS := $(patsubst  $(SRCDIR)/%.cpp, obj/%.o, $(SOURCES))
# List of all the executable
EXECUTABLES := $(patsubst  $(SRCDIR)/%.cpp, $(BINDIR)/%, $(SOURCES))  
#**********************************************************************
# set default target 
all : log  $(EXECUTABLES)	
	
$(BINDIR)/%: $(OBJDIR)/%.o
	$(CC) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR):
	@echo "create object files folder"
	@mkdir $(OBJDIR)
# delete obj folder and all .o files 
clean:
	rm -rf $(EXECUTABLES)
log :
	@echo "building package mjUr5e..."
	
#**********************************************************************

