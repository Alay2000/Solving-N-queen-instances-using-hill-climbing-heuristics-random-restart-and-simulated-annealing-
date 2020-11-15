# Solving-N-queen-instances-using-hill-climbing-heuristics-random-restart-and-simulated-annealing-
N-Queen problem is a standard problem consisting of a n*n matrix with n queens randomly placed in the boxes. We need to arrange these chess queens in a manner that no queen is able to attack another queen that is, all the queens are safe.
About Hill Climbing Algorithm
Hill Climbing is a heuristic search used for mathematical optimisation problems in the field of Artificial Intelligence.
      So, given a large set of inputs and a good heuristic function, the algorithm tries to find the best possible solution to the problem in the most reasonable time period. This solution may not be the absolute best(global optimal maximum) but it is sufficiently good considering the time allotted.
        The definition above implies that hill-climbing solves the problems where we need to maximise or minimise a given real function by selecting values from the given inputs.
1. Simple Hill Climbing
Simple hill climbing is the simplest way to implement a hill-climbing algorithm. It only evaluates the neighbour node state at a time and selects the first one which optimizes current cost and set it as a current state. It only checks it’s one successor state, and if it finds better than the current state, then move else be in the same state. This algorithm has the following features:
Less time consuming
Less optimal solution
The solution is not guaranteed

2. Steepest-Ascent Hill Climbing
The steepest-Ascent algorithm is a variation of the simple hill-climbing algorithm. This algorithm examines all the neighbouring nodes of the current state and selects one neighbour node which is closest to the goal state. This algorithm consumes more time as it searches for multiple neighbours.

3. Random Restart Hill Climbing
The algorithm repeatedly explores the problem space, that is it conducts a hill climbing search algorithm on the matrix and on being unable to find an optimal solution, it again restarts with a randomly generated matrix and tries to find an optimal solution. Hill Climbing with random restart thus conducts a series of repeated hill climbing algorithms in order to find an optimal solution. A pseudo code for the same is shown below.


Pseudo code -
1 function hill climbing with random restart(problem)   returns an optimal solution
2	inputs : problem
3	static : current node
4		next node
5	current ← make_node(Random Initial State[problem])
6	loop do
7		next ← highest valued successor of current node
8		If VALUE[next node] < value[current node] then return current node
9		current ← next
10	end loop
11	if(optimal solution found)
12		return optimal solution
13	else 
14		back to step 5
15 end 

4. Simulated Annealing
A hill-climbing algorithm which never makes a move towards a lower value guaranteed to be incomplete because it can get stuck on a local maximum. And if the algorithm applies a random walk, by moving a successor, then it may be complete but not efficient. 

