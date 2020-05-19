# Monsters

---
## Description :
> Aspen had 9 different monsters distributed into two categories, `monster` & `boss`.
> Each Monster have a different IA tu fight player.
---
## Monsters :
### Monstres :
>    * Gripe espagnole
>    * Peste noire
>    * Tenia
>    * Listéria
>    * Blob

### Boss :
>    * Cymothoa exigua
>    * Gripe H1N1
>    * VIH
>    * Covid 19

---
---
``A developer``
## Monsters IA:
* Gripe espagnole:
> Type:
>> Flying monster, infighting.
>
> IA:
>> The monster alternates between a pause time (2s) and two consecutive dash in direction of the player of  ~100px

* Peste noire:
> Type:
>> Walking monster, range fighting.
>
> IA:
>> The monster alternates between a pause time (1.5s) and try to line up with the player while walking of ~50px, if he's line up fire 4 projectiles around him 3 time with a pause time of 0.5/1s between each shoot.

* Tenia:
> Type: 
>> Walking monster, infighting.
>
> IA:
>> The monster use A* or an other algorithm to follow the player (monster have medium speed).

* Listéria:
> Type:
>> Walking monster, range fighting.
>
> IA: Dash and shoot the player.
>> The monster alternate between line up with the player (with no obstacles between them) + shoot him and pause time (2s), if the player position is in a radius of 50px around the monster, he flees to be at 100px of the player.

* Blob:
>Type:
>> Walking monster, infighting.
>
> IA: Jump to hit the player.
>> The monster alternate between a pause time (3/4s may be a random time) and jump (in some time) on the position of the player.
---
* Cymothoa exigua:
> Type:
>> Walking monster, infighting and range fighting.
>
> IA:
>> The monster alternate between time pause (0./1.5s) and line up with the player in dash and shooting him if the dash don't touch the player.

* Gripe H1N1:
> Type:
>> Flying monster, infighting.
>
> IA:
>> The monster alternate between pause time (0.5/1s), try to align with the player and then, shoot the player and if the projectile exceeds a certain distance (200/250px) it was split in 4 smallest projectile in 4 directions.

* VIH:
> Type:
>> Walking monster, infighting.
>
> IA:
>> Bounces on the walls and splits twice in half each time it loses 1/5 of his life. He split 3 time in all before dying.

* Covid 19:
> Type:
>> Flying monster, range fighting.
>
> IA:
>> Teleports to align with the player, shooting him and teleports randomly into the room immediately after and wait 1 to 3 second. If the player shoots him twice he teleport elsewhere and starts his attacks again after a pause time of 0.5 / 1s

---
---