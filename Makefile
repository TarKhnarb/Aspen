B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(O)/test.o
	g++ -ggdb $(O)/*.o -o $(B)/Aspen -lsfml-graphics -lsfml-window -lsfml-system

$(O)/Aspen.o: $(O)/Game.o
	g++ $(FLAGS) $(S)/Aspen.cpp -o $(O)/Aspen.o

$(O)/test.o: $(O)/Dungeon.o
	g++ $(FLAGS) $(S)/test.cpp -o $(O)/test.o

$(O)/Game.o: $(O)/Window.o
	g++ $(FLAGS) $(S)/Game.cpp -o $(O)/Game.o

$(O)/Window.o:
	g++ $(FLAGS) $(S)/Window.cpp -o $(O)/Window.o

$(O)/Dungeon.o: $(O)/Stage.o
	g++ $(FLAGS) $(S)/Dungeon.cpp -o $(O)/Dungeon.o

$(O)/Stage.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

$(O)/Room.o: $(O)/Rock.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Rock.o:
	g++ $(FLAGS) $(S)/Rock.cpp -o $(O)/Rock.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)
