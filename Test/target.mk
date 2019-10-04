#CMocka Target

SRC = \
../../CommonLibs/cmocka/cmocka.c

LIBS += \
-I ../../CommonLibs/cmocka \
-I ../../CommonLibs/cmocka/cmockery

OBJS = $(SRC:.c=.o)

SOURCES += $(SRC)

USER_OBJS += $(OBJS)
