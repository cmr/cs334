SHELL = /bin/sh
CC = c++
AR = ar
CONFIG = Debug
Base_CFLAGS = -Wall -Wextra -Wconversion -fPIE -fPIC -Wno-unused-parameter \
		 -Wformat=2 -Wformat-security -fstack-protector -Wstrict-overflow \
		 -fstack-protector --param=ssp-buffer-size=4 \
		 -pipe -std=c++11
Base_LDFLAGS = -Wl,-O1,--sort-common,--as-needed,-pie,-z,relro,-z,now

Release_CFLAGS = $(Base_CFLAGS) -DNDEBUG -UDEBUG -g2 -O2 -D_FORTIFY_SOURCE=2
Debug_CFLAGS = $(Base_CFLAGS) -DDEBUG -g3 -ggdb -O0 \
			   -Werror -fsanitize=undefined -fsanitize=address

CFLAGS := $($(CONFIG)_CFLAGS) $(CFLAGS)
LDFLAGS := $($(CONFIG)_LDFLAGS) $(LDFLAGS)

.SUFFIXES:

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
