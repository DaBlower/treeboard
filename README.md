# Treeboard
![](https://hackatime-badge.hackclub.com/U092DB4LGMP/fidget) <br/>
A PCB that you can use to play minigames with 4 LEDs, 4 Cherry MX switches and a XIAO RP2040. 

## Game Modes
### Reaction Tester
- **Start**: Hold the top left button for 3 seconds (the LEDs will slowly light up as you hold it)
- **How to Play**: An LED will turn on within 5 seconds, and you have to press the corresponding button as fast as possible.

### Duel
- **Start**: Hold the top right button for 3 seconds (the LEDs will slowly light up as you hold it)
- **Players**
  - Player 1 uses the left buttons and LEDs
  - Player 2 uses the right buttons and LEDs
- **How to Play**
  - Hold the PCB horizontally
  - A mirrored LED pair will light up (eg the top left and top right)
  - The first person who presses that switch wins and whoever gets to 5 wins first has their LEDs flash as celebration
### Memory Game
- **Start**: Hold the bottom right button for 3 seconds (the LEDs will slowly light up as you hold it)
- **How to Play**
  - The LEDs flash a sequence that you have to exactly recreate with the buttons
  - Each time you succeed, the length of the sequence increases
  - If you fail, the LEDs turn on and off 2 times, and if you win, they turn on one by one.

## Files
To program the XIAO RP2040, follow [this guide](https://wiki.seeedstudio.com/XIAO-RP2040-with-Arduino/) and open [this file](/firmware/treeboard/treeboard.ino) in the Arduino IDE.

## Schematic
<img src="/img/schema.png" alt="Schematic Image" width="600"/>

## PCB
<img src="/img/PCB.png" alt="PCB Image" width="600"/>
<img src="/img/3d_back.png" alt="Front 3D PCB Image" width="300"/>
<img src="/img/3d_front.png" alt="Back 3D PCB Image" width="600"/>

## BOM
* 4 Cherry MX switches
* 4 LEDs
* 4 Resistors
* 1 XIAO RP2040

made by ```@obob``` on the Hack Club Slack for the Pathfinder YSWS!
