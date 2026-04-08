# src/mysed/Makefile

CC = gcc
AR = ar
CFLAGS = -Wall -I../../include

REPO_ROOT ?= ../..
OBJDIR := $(REPO_ROOT)/obj/mysed

LIBNAME := mysed
LIB := lib$(LIBNAME).a
LIB_PATH := $(OBJDIR)/$(LIB)

SRCS := mysed.c
OBJS := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: $(LIB_PATH)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_PATH): $(OBJS)
	$(AR) rcs $@ $^

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
