SFMLDIR=/home/harsha/packages/SFML-2.5.1
INCLUDEDIR=$(SFMLDIR)/include
LIBDIR=$(SFMLDIR)/lib
CC =g++
LIBFLAGS=-lsfml-window -lsfml-system -lsfml-graphics
	SRCS = State.cpp Main.cpp GameState.cpp MainMenuState.cpp Button.cpp Game.cpp\
	 animation.cpp Player.cpp Bound_Rect.cpp InterfaceState.cpp Tilemap.cpp Tile.cpp\
	  TextureSelector.cpp QuitState.cpp GameInfo.cpp PlayerInfo.cpp collider.cpp \
	  PlayerAttributes.cpp PauseMenu.cpp Enemytile.cpp Enemy.cpp
OBJS =$(addsuffix .o,$(basename $(SRCS)))
EXE = Game
.PHONY = clean all
all = $(EXE)
$(EXE) : $(OBJS)
	$(CC) -o $@ -L $(LIBDIR) $(OBJS) $(LIBFLAGS)

$(OBJS) :%.o :%.cpp
	$(CC) -c -I $(INCLUDEDIR) $<
	
clean:
	rm $(OBJS) $(EXE)