# src/mybash/Makefile

CC = gcc
CFLAGS = -Wall -I../../include -std=c11 -D_POSIX_C_SOURCE=200809L

REPO_ROOT ?= ../..
BINDIR := $(REPO_ROOT)/bin
OBJDIR := $(REPO_ROOT)/obj/mybash

TARGET := mybash
TARGET_PATH := $(BINDIR)/$(TARGET)

SRCS := main.c
OBJS := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

LINKDIRS := -L$(REPO_ROOT)/obj/myfile -L$(REPO_ROOT)/obj/mysed -L$(REPO_ROOT)/obj/mywc -L$(REPO_ROOT)/obj/mytrans
LDLIBS := -lmyfile -lmysed -lmywc -lmytrans

all: $(TARGET_PATH)

$(BINDIR) $(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_PATH): $(OBJS) | $(BINDIR)
	$(CC) -o $@ $(OBJS) $(LINKDIRS) $(LDLIBS)

clean:
	rm -rf $(OBJDIR) $(TARGET_PATH)

.PHONY: all clean
