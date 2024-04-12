# Chess AI
![alt text](image.png)
## Building

The game is written in C++ and uses features from the C++17
standard. [CMake](https://cmake.org/) is used to build all components.
and works well with the
[CMakeTools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
extension in VSCode.

To configure it manually, type

```
cd build
cmake ..
```

then build it using

```
cmake --build .
```

Either method will generate an executable in the build directory.

## Running

Running this game requires the SDL2 library to be installed. This
is done very easily on MacOS and Windows through [MSYS2](https://www.msys2.org/#installation). <br>

In the MSYS2 terminal, the following command can be run to install the library and
configure all pathing for DLL files.<br>
`pacman -S mingw64/mingw-w64-x86_64-SDL2 mingw64/mingw-w64-x86_64-SDL2_mixer mingw64/mingw-w64-x86_64-SDL2_image mingw64/mingw-w64-x86_64-SDL2_ttf mingw64/mingw-w64-x86_64-SDL2_net`

The terminal used to run the game must be in the parent directory that the "assets" folder is within. From there, you can run `.\build\____` (name of executable within build folder)

## Assets 

All assets used in this game were found on https://opengameart.org/content/chess-pieces-and-board-squares and are free to use. They are included in this repository. The sprites are manually initialized. Because of this, in order to run the game properly, the game must be ran from the build directory.

Assets are drawn to the screen within the `Engine` class. This class handles the conversion between pixel coordinates and chess board tile indices. It draws all of the sprites initially, and then every time a move is made. This is all called from within the `Engine` class.

## Chess Board

The datastructure used to store all of the data required is a one dimmensional vector of `Tiles`. Since the vector is one dimmensional, the positions of the board are represented by indices 0-63. Each `Tile` holds the value of a `std::optional<Piece>`. If the tile does not hold a piece, the value is `NULL`.

## Game Flow
The game is run using the `Engine` loop that I created. It alternates who's turn it is, allowing either the player to move, or for the AI to decide on its best move and take it. When selecting a move to take, the `Piece` class regulates what moves can be made by doing checks on what piece is selected by the player. The `Agent` class handles all checking for the AI's movement.

