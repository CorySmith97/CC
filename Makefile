UNAME := $(shell uname)


ifeq ($(UNAME), Linux)
	CC = clang
endif
ifeq ($(UNAME), Darwin)
	CC = clang
endif
ifeq ($(OS), Windows)
	CC = clang
endif
APP_NAME = main
BUILD_DIR = ./bin
# This is a wildcard statement. Basically will
# grab and compile anyfile ending in .c.
# The compiler will optimize any unused files in
# the linking phase.
C_FILES = ./src/*.c

# Here are multiline. This is a c optimization flag
C_FLAGS = -std=c23 -g -o0
# These is a warnings flag
C_FLAGS += -Wall

# These are header files that I want to include.
# This is where you could add library code the -I
# denotes to the compiler, until we say otherwise, compile
# these files as well, and have the object files available during linking.
# The -framework are things specific to mac. I need those in order
# to create windows(Cocoa) use opengl and get user input.
APP_INCLUDE =

# Link is for precompiled libraries. These typically come in the following
# formats:
# 	*.so
# 	*.dynlib
# 	*.dll
# 	*.a
# I think there is another one for window static libraries. But that should
# be the common ones. The format for this one is Where is the directory for
# the file located. And the -l is link from the -L directory, and then you
# tac on the name at the end.
APP_LINK =
ifeq ($(UNAME), Darwin)
	APP_LINK += -Llib/mac -lraylib
	APP_INCLUDE += -I./lib/ -framework Cocoa -framework Opengl -framework IOKit
endif
ifeq ($(OS), Windows)
	APP_LINK += -Llib/windows -lraylib -lopengl32 -lgdi32 -lwinmm
	APP_INCLUDE += -I./lib/
endif

# There are more things that are available via clang or gcc, but this is
# a goos start. Now comes out "scripts"

build:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/$(APP_NAME) $(C_FILES) $(APP_INCLUDE) $(APP_LINK)

run:
	$(BUILD_DIR)/$(APP_NAME)

.PHONY: clean

clean:
	rm -f ./bin/*.o
