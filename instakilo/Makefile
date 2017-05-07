#!/bin/bash
CC=gcc
RM=rm -f

SRC_PATH=src/
INC_PATH=include/

INCS=$(foreach d, $(INC_PATH), -I$d)

CFLAGS=-std=c99 -Wall $(MODE) $(INCS)
LDFLAGS=-lm

FILE_PREFIX=.c
OBJ=.o

SOURCES=main.c $(SRC_PATH)test_instakilo.c $(SRC_PATH)stack_machine.c $(SRC_PATH)libimg.c $(SRC_PATH)libppm.c $(SRC_PATH)instakilo.c $(SRC_PATH)image_stack.c
OBJECTS=$(SOURCES:$(FILE_PREFIX)=$(OBJ))

EXECUTABLE=instakilo

MODE=$(DEBUG)

RELEASE=-O2 -DNDEBUG
DEBUG=-O0 -ggdb

all: $(SOURCES) $(EXECUTABLE)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

$(EXECUTABLE): $(OBJECTS)

%$(OBJ): %FILE_PREFIX
	$(CC) $(CFLAGS) $< $@ $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
