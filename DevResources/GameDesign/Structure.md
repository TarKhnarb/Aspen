# Structure of the files

## Files descriptions :

### Aspen:
> Call to run program and the game

### StartMenu: 
> Start the window for the game and allow to the player to select between 3 saves to play.

### Window:
> Create a Window and manage a SFML window

### PlayMap:
> SFML part : Manage the map of the game

### PlayDungeon:
> SFML part : Manage the dungeon of the game

### DrawPlayer:
> SFML part : Manage the walking animation and the inventory of the player

### DrawInventory:
> SFML part : Manage the inventory interface

### DrawNpc:
> SFML part : Manage the npc on the map

### DrawMonster:
> SFML part : Manager the monster in the dungeon

### Map:
> Contain:
>>* Npc to intacting with them
>>* Base to store dungeon's items in chests
>>* Dungeon entry

### Dungeon:
> Contain:
>>* X stages of Y Rooms
>>* 

### Player:
> Manage player information

> Contain:
>>* Inventory

### Monster:
> Manage monsters information

### Entity:
> Manage information for different etity

### Stats:
> Manage entity stats

### Object:
> Manage object for the game

### Stage:
> Manage a stage of the dongeon

### Room:
> Manage a room of a stage

### Door:
> Manage a door of a room

### RoomContenu:
> Manage the different contenu of a room

> Contain:
>>* Monsters
>>* Chest
>>* Object
>>* Rock
>>* Boost
