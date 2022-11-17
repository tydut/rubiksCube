# Rubik's Cube CLI

Rubik's Cube implementation in C used during the 2022 CSAW Final's CTF Colorblind Challenge with @n132

This implementation allows you to play with a Rubik's Cube in the command line: 

```
              R R R
              R R R
              R R R
W W W  G G G  Y Y Y  B B B
W W W  G G G  Y Y Y  B B B
W W W  G G G  Y Y Y  B B B
              O O O
              O O O
              O O O

Enter your move:
```

Moves are in basic cube notation with support of X, Y, and Z moves. Lowercase moves are not supported. 
The cube is in the order of:

```
                        Top Face

Back Face   Left Face   Front Face  Right Face

                        Bottom Face
```

You can compile the code using your preferred C compiler:
```
gcc -o cube cube.c
```
TODO: Add a Scrambler.
