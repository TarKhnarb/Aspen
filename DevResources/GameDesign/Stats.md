# Character Stats

---
## Description :

All characters have the same stats.
>
> * Life
> * Attack
> * AttackSpeed
> * Defence
> * Speed
> * Fly

---

## Life :

Life points of a character 0 -> death

---

## Attack :

Attack corresponds to the damage given to a character with 0 in Defence

---

## AttackSpeed :

AttackSpeed correspond to the number of projectiles send per seconds.

---

## Defence :

When a character was hit, we calculate the damage received as follows :
* If the Defence is greater than 0 :
> Damage = (AttackEnemy) * 100/(100 + Defence) 

* If the Defence is lower than 0 :
> Damage = (AttackEnemy) * (2 - 100/(100 + Defence))
---

## Speed :

Speed corresponds to the following calculation:
> PxMove = 150px * (1 + Speed/100)

---

## Fly :

Fly affects collisions in the rooms of the dungeon. Flying avoids colliding with rocks and holes.

---