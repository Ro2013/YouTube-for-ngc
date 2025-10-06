# 這是 devkitPPC 簡單範例
TARGET = GameCubeClient
OBJS = main.o gui.o network.o input.o video.o history.o

all: $(TARGET).dol

%.o: %.cpp
	$(CXX) -c $< -o $@

$(TARGET).dol: $(OBJS)
	$(CXX) -o $@ $(OBJS) -lgc -lSDL2 -lcurl -ljsoncpp

clean:
	rm -f $(TARGET).dol $(OBJS)