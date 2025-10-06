# GameCubeClient Makefile for devkitPPC

TARGET = GameCubeClient
OBJS = main.o gui.o network.o input.o video.o history.o

# 指定編譯器
CXX = powerpc-eabi-g++
CXXFLAGS = -O2 -Wall -I$(DEVKITPRO)/libogc/include -I$(DEVKITPRO)/portlibs/ppc/include
LDFLAGS = -L$(DEVKITPRO)/libogc/lib -L$(DEVKITPRO)/portlibs/ppc/lib -logc -lSDL2 -lcurl -ljsoncpp

all: $(TARGET).dol

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET).dol: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET).dol $(OBJS)
