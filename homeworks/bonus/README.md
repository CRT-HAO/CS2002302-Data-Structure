# Homework Bonus

## Notes

My code is really dirty, but it was successfully accepted by Online Judge

## Description

Use the given information to create a directed graph's adjacency matrix with weight. Then use Bellman-Ford algorithm and Dijkstra algorithm to find out the shortest path and its length.

## Input

First line will give you the amount of vertices and edges and the initial (source) node.

Second to the last will be the information of each node (start point, destination, weight)

## Output

1. print the vertices name and new distance while the distance of the vertices changes (label / relabel) with Bellman-Ford algorithm.

2. print all the vertices' shortest path in order with Bellman-Ford algorithm (if their is no shortest path use - to represent).

3. print the shortest path and its length of all vertices with Dijkstra algorithm (if their is no shortest path print No path to ...).

- if it is unavailable to use the according algorithm print "invalid input".

> !!! there should be a blank in the end of point 2 !!!

## Sample 1

### Input

```
5 10 s
t x 5
t y 8
t z -4
x t -2
y x -3
y z 9
z x 7
z s 2
s t 6
s y 7
```

### Output

```
t 6
y 7
x 11
z 2
x 4
t 2
z -2
0 2 4 7 -2
invalid input
```

## Sample 2

### Input

```
7 9 d
b a 4
a c 2
f c 9
e b 17
e g 11
d b 15
d g 23
d f 5
f g 13
```

### Output

```
b 15
g 23
f 5
g 18
a 19
c 21
c 14
19 15 14 0 - 5 18
d -> b -> a = 19
d -> b = 15
d -> f -> c = 14
d = 0
No path to e
d -> f = 5
d -> f -> g = 18
```

## Sample 3

### Input

```
5 10 s
s t 3
s y 5
t y -2
y t -1
z s 3
y z 6
t x 6
y x 4
x z 2
z x 7
```

### Output

```
invalid input
invalid input
```
