# GameCube DOL build with devkitPPC

TARGET = GameCubeClient
OBJS = main.o gui.o network.o input.o video.o history.o

# 指定 devkitPPC 編譯器
CXX = powerpc-eabi-g++
CC  = powerpc-eabi-gcc
CXXFLAGS = -O2 -Wall
LDFLAGS = -lgc -lSDL2 -lcurl -ljsoncpp

all: $(TARGET).dol

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CXXFLAGS) -c $< -o $@

$(TARGET).dol: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f $(TARGET).dol $(OBJS)
