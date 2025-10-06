# Makefile for GameCubeClient.dol
TARGET = GameCubeClient
OBJS = main.o gui.o network.o input.o video.o history.o

# 使用 devkitPPC 的 g++
CXX = powerpc-eabi-g++

all: $(TARGET).dol

%.o: %.cpp
	$(CXX) -c $< -o $@

$(TARGET).dol: $(OBJS)
	$(CXX) -o $@ $(OBJS) -lgc -lSDL2 -lcurl -ljsoncpp

clean:
	rm -f $(TARGET).dol $(OBJS)
