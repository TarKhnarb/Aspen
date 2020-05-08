# Event Manager :

---
## Description :

---

## Files :

### key.cfg :

---
`ActionName EventTypeNb:KeyBoardValue`

* ActionName : The name of the desired action.

* EventTypeNb : refers to the value of EventType enum class.

* KeyBoardValue : ASCII code of the key

---

* Window_close 0:0
---
> '0' --> Closed = sf::Event::Closed
> '0' --> `NUL` character
---

* Fullscreen_toggle 3:70
---
> '3' --> WindowResized = sf::Event::Resized
> '70' --> `F` key
---

* MoveUp 1:90
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '90' --> `Z` key
---

* MoveRight 1:68
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '68' --> `D` key
---

* MoveDown 1:83
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '83' --> `S` key
---

* MoveLeft 1:81
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '81' --> `Q` key
---

* OpenInventory 1:69
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '' --> `E` key
---

* InventoryInteraction 1:32
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '' --> `SpaceBar` key
---

* InventoryAction 1:8
---
> '1' --> KeyDown = sf::Event::KeyPressed
> '' --> `Return` key
---