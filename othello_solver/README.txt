We met and worked on a majority of the parts of the project together. We planned out each function on paper,
and then implemented and debugged our programs together. Tara got Minimax to work (she fixed the issues and
bugs that we found on our program) and Ayaana got Heuristic to work (again, by debugging and solving the 
issues we had). Tara also improved on the heuristic function for week 2 in order to make it beat ConstantTimePlayer.

We improved our score calculation by associating each square on the board with a weight. This allows for a more 
sophisticated score calculation. We then experimented with different board weights to find the optimal weight 
assignment that allowed our heuristic player to consistently beat Constant Time Player. We believe that this strategy 
will work because we not only weighted the board squares such that the corners have the greatest weight and the adjacent
squares have a very negative weight, but also such that the rows and columns adjacent to the first and last columns and 
rows are negatively weighted. This will cause our player to avoid choosing those squares, which is good since the smart 
opponent will want to choose the sides of the board. In addition, we weighted the squares diagonally adjacent to the 
corners more heavily than those directly adjacent to the corners, which made a significant difference to the number of 
wins we had against both ConstantTimePlayer and SimplePlayer. 
We tried to implement the alpha-beta pruning method, but were not able to make it work, so instead we worked on 
improving our heuristic function.