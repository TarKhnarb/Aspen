B = bin
O = obj
S = src
FLAGS = -c -Wall
STAT_O = $(O)/State_Intro.o $(O)/State_Dungeon.o $(O)/State_GamePause.o

all: $(O) $(B) $(O)/Aspen.o
	g++ -ggdb $(O)/*.o -o $(B)/Aspen -lsfml-graphics -lsfml-window -lsfml-system

$(O)/Aspen.o: $(O)/Game.o $(O)/SpriteSheet.o
	g++ $(FLAGS) $(S)/Aspen.cpp -o $(O)/Aspen.o

$(O)/test.o:
	g++ $(FLAGS) $(S)/test.cpp -o $(O)/test.o

$(O)/Game.o: $(O)/Window.o $(O)/StateManager.o
	g++ $(FLAGS) $(S)/Game.cpp -o $(O)/Game.o

$(O)/Window.o: $(O)/EventManager.o
	g++ $(FLAGS) $(S)/Window.cpp -o $(O)/Window.o

$(O)/StateManager.o: $(STAT_O)
	g++ $(FLAGS) $(S)/StateManager.cpp -o $(O)/StateManager.o

$(O)/State_Intro.o: $(O)/EventManager.o
	g++ $(FLAGS) $(S)/State_Intro.cpp -o $(O)/State_Intro.o

$(O)/State_Dungeon.o: $(O)/EventManager.o $(O)/Dungeon.o
	g++ $(FLAGS) $(S)/State_Dungeon.cpp -o $(O)/State_Dungeon.o

$(O)/State_GamePause.o: $(O)/EventManager.o
	g++ $(FLAGS) $(S)/State_GamePause.cpp -o $(O)/State_GamePause.o

$(O)/EventManager.o:
	g++ $(FLAGS) $(S)/EventManager.cpp -o $(O)/EventManager.o

$(O)/SpriteSheet.o: $(O)/Anim_Base.o $(O)/Anim_Directional.o
	g++ $(FLAGS) $(S)/SpriteSheet.cpp -o $(O)/SpriteSheet.o

$(O)/Anim_Base.o:
	g++ $(FLAGS) $(S)/Anim_Base.cpp -o $(O)/Anim_Base.o

$(O)/Anim_Directional.o:
	g++ $(FLAGS) $(S)/Anim_Directional.cpp -o $(O)/Anim_Directional.o

$(O)/Dungeon.o: $(O)/Stage.o
	g++ $(FLAGS) $(S)/Dungeon.cpp -o $(O)/Dungeon.o

$(O)/Stage.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

$(O)/Room.o: $(O)/Hole.o $(O)/Rock.o $(O)/Door.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o: $(O)/Entity.o
	g++ $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O)/Rock.o: $(O)/Entity.o
	g++ $(FLAGS) $(S)/Rock.cpp -o $(O)/Rock.o

$(O)/Hole.o: $(O)/Entity.o
	g++ $(FLAGS) $(S)/Hole.cpp -o $(O)/Hole.o

$(O)/Entity.o:
	g++ $(FLAGS) $(S)/Entity.cpp -o $(O)/Entity.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)
