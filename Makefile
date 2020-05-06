B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(O)/Aspen.o
	g++ -ggdb $(O)/*.o -o $(B)/Aspen -lsfml-graphics -lsfml-window -lsfml-system

$(O)/Aspen.o: $(O)/Game.o
	g++ $(FLAGS) $(S)/Aspen.cpp -o $(O)/Aspen.o

$(O)/Game.o: $(O)/Window.o
	g++ $(FLAGS) $(S)/Game.cpp -o $(O)/Game.o

$(O)/Window.o:
	g++ $(FLAGS) $(S)/Window.cpp -o $(O)/Window.o

$(O)/Dungeon.o:
	g++ $(FLAGS) $(S)/Dungeon.cpp -o $(O)/Dungeon.o

$(O)/Collider.o:
	g++ $(FLAGS) $(S)/Collider.cpp -o $(O)/Collider.o

$(O)/AnimatedSprite.o: $(O)/Animation.o
	g++ $(FLAGS) $(S)/AnimatedSprite.cpp -o $(O)/AnimatedSprite.o

$(O)/Animation.o:
	g++ $(FLAGS) $(S)/Animation.cpp -o $(O)/Animation.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)
