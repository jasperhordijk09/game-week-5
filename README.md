# Week 5, dagdeel 4
## Code Challenge
### Pitfall
**Requirements**
1. Gebruik dit [template](pitfall.c). Dit bevat code voor Windows, MacOS en Linux om *non-blocking input* te gebruiken.
2. Voeg een loop toe aan het programma.
3. Iedere iteratie van de loop wordt een regel van 60 `#`'s geprint. Dit is de rotsmuur.
4. Midden in de muur zit een opening van 10 spaties breed.
5. Midden in de opening wordt de capsule van de speler geprint (`V`).
6. Om het niet te snel te laten gaan, bevat de loop een wacht-statement. Je kunt daarvoor de functie `usleep()` gebruiken, met als argument de tijd in microseconden. Begin met 1000000 microseconde.
7. De plaats van de capsule is te veranderen met de toetsen `A` en `D` voor links en rechts. Gebruik hiervoor de functie `getkey()`. Deze geeft de ASCII-code van de ingedrukte toets terug, of 0 als er geen toets ingedrukt werd.
8. De locatie van de opening verandert iedere iteratie één stapje naar links of naar rechts. Gebruik hiervoor de functie `rand()`. Deze geeft een willekeurige integer terug. 
9. Als de capsule de rotswand raakt, stopt het spel en wordt het aantal geprinte regels geprint.
10. Iedere iteratie wordt de wachttijd 20000 microseconde korter, totdat deze 100000 microseconde is.

**Optionele extra's**
- De tunnel wordt langzaamaan steeds smaller.
- Er wordt een highscore bijgehouden.   
- Het spel is ook multiplayer te spelen, met twee tunnels naast elkaar.
