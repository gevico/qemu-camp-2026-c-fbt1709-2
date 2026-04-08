# src/mytrans/Makefile

CC = gcc
AR = ar
CFLAGS = -Wall -I../../include -std=c11 -D_POSIX_C_SOURCE=200809L

REPO_ROOT ?= ../..
OBJDIR := $(REPO_ROOT)/obj/mytrans

LIBNAME := mytrans
LIB := lib$(LIBNAME).a
LIB_PATH := $(OBJDIR)/$(LIB)

SRCS := mytrans.c myhash.c
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
