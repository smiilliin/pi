CC=g++
CFLAGS=-Wall -g -std=c++11
LIBS=-lgmpxx -lgmp -lpthread
OBJS=
HEADERS=
TARGET=dist/pi
MAIN=src/pi.cpp

all: dist $(TARGET)
dist:
	mkdir dist
clean:
	rm dist/*.o $(TARGET)

dist/%.o: src/%.cpp src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).o: $(MAIN) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(TARGET).o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)