CC = clang++
CFLAGS = -g -Wall
DFLAGS = -DDEBUG
SRC = main.cpp sorts.cpp
OBJ = main.o sorts.o
TARGET = test-me

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJ)
