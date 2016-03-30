FILENAME=nygc_2016
CC=arm-linux-gnueabihf-gcc
IDIR =../include
CFLAGS=-I$(IDIR)
LIBS=
ODIR=../obj

DRV_FILES := $(wildcard ../drivers/*.c)
DOBJ_FILES := $(patsubst ../drivers/%.c,../obj/$.o,$(DRV_FILES))
