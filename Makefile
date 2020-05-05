B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/Aspen

$(B)/Aspen:
	g++ -ggdb $(S)/Aspen.cpp -o $(B)/Aspen $(O)/*.o -lsfml-graphics -lsfml-window -lsfml-system

$(O)/Dungeon.o:
	g++ $(FLAGS) $(S)/Dungeon.cpp -o $(O)/Dungeon.o

$(O)/Window.o:
	g++ $(FLAGS) $(S)/Window.cpp -o $(O)/Window.o

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
