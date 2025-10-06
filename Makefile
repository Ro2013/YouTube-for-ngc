# Makefile for GameCube client
TARGET = GameCubeClient
OBJS = main.o gui.o network.o input.o video.o history.o

CXX = powerpc-eabi-g++   # devkitPPC 的編譯器
CFLAGS = -O2 -Wall
LDFLAGS = -lgc -lSDL2 -lcurl -ljsoncpp

all: $(TARGET).dol

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(TARGET).dol: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f $(TARGET).dol $(OBJS)
