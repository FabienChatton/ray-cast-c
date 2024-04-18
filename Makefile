CC=gcc
CFLAGS=-g -Wall
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
LIBS=-lncurses -lm

BINDIR=bin
BIN=$(BINDIR)/main

ifeq ($(OS),Windows_NT) 
RM = del /Q /F
RM_FILES = $(BINDIR) $(OBJ)
else
RM_FILES = $(BINDIR)/* $(OBJ)/*
endif

all: $(BIN)

$(BIN): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir $@

$(OBJ):
	mkdir $@

clean:
	$(RM) $(RM_FILES)
