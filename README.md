# Start to end searching program

Input format of both the codes
n m         , where n =no. of rows, m = no. of columns
a matrix of size m * n with elements S, E, O, X
where,  S = Starting point 
        E = Ending point
        O = grid where robot is allowed to move
        X = grid where the space is blocked and robot cannot be present there
Eg. 
4 5
SOOOO
XXOOO
XXOOO
EOOOX

output is given in the format of tuple containing the co-ordinates of path from starting to ending point.

 A-starmulti.cpp uses only distance moved from starting as a parameter to determine
	shortest path and it prints all the possible shortest paths

A-starp.cpp uses A* search i.e. both the distance from starting and the distance from
	the end point as a parameter to determine the shortest path.
	It is much more efficient but it gives only a single path as output.
