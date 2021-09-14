## Lem-in Project Summary

The goal of this project is to find the quickest way to get X ants across the map. </n>
Quickest way means the solution with the least number of lines (rounds).</n>
Some constraints apply:
* Only one ant per room (except for start and end).
* Ants can only move once per round.</n>

The map consists of rooms and links. Each link is connected to 2 rooms, each room can have any number of links.
There is 1 start and 1 end room.

Your program will receive the data describing the map from the standard output
in the following format:
```
number_of_ants
the_rooms
the_links

Example:
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
#another comment
```

## The Algorithm

I tried to come up with the solution my self instead of using an existing one, so the algorithm is more convoluted than it had to be.
My algorithm starts with checking start and end rooms, which one has least amount of links.
The amount is the theoretical highest possible path amount.
Then is starts for start room moving to each connected room until one reaches the end room (BFS).
It save that path that reached the end first and calculates how many moves current path configuration will take.
If the highest possible path amount is higher that 1 it starts again.
But this time it does not send to the room connected to start that is already used by a saved path.
If during this BFS it travels to a room that is used in a previous path it travels backwards on the previous path and tries to exit to a free node, if not possible the current path is terminated.
If a path that has traveled backwards on a previous path reaches the end first, the current path and the 
backwards traveled path a spliced to make 2 separate paths.
When the ant moving amount start to rise the optimal path configuration has been found.

## Parsing

When reading la map file

## Compiling and Running the Program
```sh
git clone https://github.com/Epicurius/Lem-in.git && cd Lem-in
make && make -f Validator/Makefile

#	Help info for use & flags
./lem-in -h
#	To run the program with map (there are some in Validator/tests/..)
./lem-in < # MAP
#	OR run quick test
./Validator/run.sh
```

## Conclusion

This was the first project where i learned how to use structs and lists. </n>
I had a lot of fun with the project (especially the optimizing part), but due to a team project I had to</n>
finnish the project prematurely. So the end result is not as polished as many of my other projects.

