# Compiler I am using
CC = clang
APP_NAME = main
BUILD_DIR = ./bin
# This is a wildcard statement. Basically will
# grab and compile anyfile ending in .c.
# The compiler will optimize any unused files in
# the linking phase.
C_FILES = ./src/*.c

# Here are multiline. This is a c optimization flag
C_FLAGS = -o2
# These is a warnings flag
C_FLAGS += -Wall

# These are header files that I want to include.
# This is where you could add library code the -I
# denotes to the compiler, until we say otherwise, compile
# these files as well, and have the object files available during linking.
# The -framework are things specific to mac. I need those in order
# to create windows(Cocoa) use opengl and get user input.
APP_INCLUDE = -I./lib/ -framework Cocoa -framework Opengl -framework IOKit

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
APP_LINK = -Llib/mac -lraylib

# There are more things that are available via clang or gcc, but this is
# a goos start. Now comes out "scripts"

game:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/$(APP_NAME) $(C_FILES) $(APP_INCLUDE) $(APP_LINK)
