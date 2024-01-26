#**************************************************
# Makefile 
#
#
#**************************************************
# Set The Compiler 
CC :=g++ 
# Compiler flags
CFLAGS :=  -I./mujoco/include  -I./glfw/include -I./include -I./glm
# Linker flags
LDFLAGS := -L./mujoco/bin -lmujoco  -L./glfw/lib -lglfw3
# List of source files
SOURCES := src/test.cpp 
# Name of the executable
EXECUTABLE := bin/main 
#**************************************************



all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)


