### UPDATES :

0.1 : git is now fully functionnal, to get started, read below. The game is in an early early early stage of devlopment.


# ** What's Mortal Kitchen ? ** 

Mortal Kitchen is a funny WTF game, developed by twelve amazing students from Nancy.

These twelve awesome guys are from an engineering school (Mines Nancy) and an art schol (ENSA Nancy).

Dreamerz :
  * Mila (Memé)
  * Emilien
  * Louison
  * Albéric
  * Anne
  * Clara

Code Monkeyz :
  * Bastien (BastouBG)
  * Pierre (PowerPipou)
  * Jules (DaPrez)
  * Nicolas (Hontas)
  * Emmanuel (Elesin)
  * Matthieu (Matteo)

 
# ** Getting Started **
 
To get started you need to install : 
  * CMake
  * Python 3 or above
  * Visual Studio 2013 or above
 
Then, launch CMake and configure :
  * The sources to src-2015 folder
  * The build path to a folder named BUILD (exactly) at the root of the repo (next to src-2015)
 
You should now have a fully functional version of Mortal Kitchen, the gameprog.sln might be in the newly created BUILD folder.

Any added file to the project should be mentioned in the corresponding CMakeLists.txt so other can generate solution including this new file. 
 
# ** Testing sprites, tiles, etc with this projects **
 
  * All content should be added to src-2015\data (in tilemap for map, sprites for sprites, etc)
  * Sprite may then be referenced in the scripts src-2015\data\scripts
  * To launch the game, click on Mortal_Kitchen.exe in src-2015
  * Any added file may be (or will be) added to the installer project so they're packed in the installer
 
N.B : Push the space bar to reload your scripts/sprites
 
Have fun on this awesome project ! =)
 
 

