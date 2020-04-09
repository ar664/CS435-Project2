# CS435 Project2
Anthony Rios

In order to run on a linux based system:
```
make
./main
```
main should have executable permissions if not run this: `chmod +x main`

## Dependencies:
* C Standard Libraries
* [GLib2.0](https://wiki.gnome.org/Projects/GLib/SupportedPlatforms)

## Description
Currently main just runs the 1,000 because I wanted to get to all parts of my code for debugging purposes. Feel free to change nodeNum to whatever value you want. Be careful of stack size with Recursive algorithms.

## Examples
Tests Below Were done on 1,000 sized arrays because 10,000 doesn't really fit the screen.

Recursive BFS Traversal:
![Recursive B.F.S.](https://imgur.com/PQqOo9W.png)

Iterative BFS Traversal:
![Iterative B.F.S.](https://imgur.com/TBFpxFl.png)

Traces for Iterative DFS and Recursive DFS:
![D.F.S. Traces](https://imgur.com/mlI0DRh.png)

Set of Djikstra on:
* [Fully Connected Graph](https://imgur.com/wpcv2MP)
* [Linked List Graph](https://imgur.com/ZX5Qfnm)

Kahn's Algorithm Topological Sort:
![Khans Sort](https://imgur.com/SqBHtYV.png)

Modified DFS Topological Sort:
![Modified D.F.S.](https://i.imgur.com/B1wUfIb.png)

Path for A* on Grid Graph:
![A. Star](https://i.imgur.com/62m5SdZ.png)
