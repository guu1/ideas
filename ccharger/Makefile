# Versioning:
CUR := 0
REV := 0
AGE := 0


# Compiler:
CC := gcc
# Flags for the compiler
# You dont know C flag extra
EXTRA_FLAGS	:= -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align \
            		-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            		-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            		-Wconversion -Wstrict-prototypes
#EXTRA_FLAGS	+= -pedantic
DEBUG_FLAG	:= -g
CFLAGS 		:= $(DEBUG_FLAG) -std=gnu99
#CFLAGS		+= $(EXTRA_FLAGS)


# TODO: isto tem que sem instalado corretamente 
# Root directories:
ROOT := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Directories:
SRCDIR     := $(ROOT)/src
INCDIR     := $(ROOT)/include
BUILDDIR   := $(ROOT)/obj
TARGETDIR  := $(ROOT)/bin
LIBDESTDIR := $(PREFIX)/lib
INCDESTDIR := $(PREFIX)/include

#################################
#	 C PRE-PROCESSOR	#
#################################
# What flags should be passed to the C pre-processor
# In other words, where should we look for files to include
# This doenst include compiler specific directories
CPPFLAGS	:= -I. \
		-I$(INCLUDE_DIR)

## CLIENT INCLUDES FOR SEARCH
INCLUDE_DIR		:= $(MAKE_DIR)include/


#################################
#	     LINKER		#
#################################
# Where to look for libraries to link
# TODO: vamos usar libusb tem que se fazer o link aqui

LDFLAGS			:= -L. \
			-L$(LIBS_DIR)
