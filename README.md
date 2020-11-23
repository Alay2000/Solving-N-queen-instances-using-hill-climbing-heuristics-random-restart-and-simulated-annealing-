# Solving-N-queen-instances-using-hill-climbing-heuristics-random-restart-and-simulated-annealing and visualising performane using Javafx-
N-Queen problem is a standard problem consisting of a n*n matrix with n queens randomly placed in the boxes. We need to arrange these chess queens in a manner that no queen is able to attack another queen that is, all the queens are safe.
About Hill Climbing Algorithm
Hill Climbing is a heuristic search used for mathematical optimisation problems in the field of Artificial Intelligence.
      So, given a large set of inputs and a good heuristic function, the algorithm tries to find the best possible solution to the problem in the most reasonable time period. This solution may not be the absolute best(global optimal maximum) but it is sufficiently good considering the time allotted.
        The definition above implies that hill-climbing solves the problems where we need to maximise or minimise a given real function by selecting values from the given inputs.
## 1. Simple Hill Climbing
Simple hill climbing is the simplest way to implement a hill-climbing algorithm. It only evaluates the neighbour node state at a time and selects the first one which optimizes current cost and set it as a current state. It only checks it’s one successor state, and if it finds better than the current state, then move else be in the same state. This algorithm has the following features:
Less time consuming
Less optimal solution
The solution is not guaranteed
![HillClimbing](https://user-images.githubusercontent.com/46098223/99931633-43ffd880-2d7b-11eb-83da-45982fc75e2a.png)


## 2. Steepest-Ascent Hill Climbing
The steepest-Ascent algorithm is a variation of the simple hill-climbing algorithm. This algorithm examines all the neighbouring nodes of the current state and selects one neighbour node which is closest to the goal state. This algorithm consumes more time as it searches for multiple neighbours.

## 3. Random Restart Hill Climbing
The algorithm repeatedly explores the problem space, that is it conducts a hill climbing search algorithm on the matrix and on being unable to find an optimal solution, it again restarts with a randomly generated matrix and tries to find an optimal solution. Hill Climbing with random restart thus conducts a series of repeated hill climbing algorithms in order to find an optimal solution.

![RandomRestart](https://user-images.githubusercontent.com/46098223/99931634-45c99c00-2d7b-11eb-84ac-2c5841476f26.png)


## 4. Simulated Annealing
A hill-climbing algorithm which never makes a move towards a lower value guaranteed to be incomplete because it can get stuck on a local maximum. And if the algorithm applies a random walk, by moving a successor, then it may be complete but not efficient. 

![SimulatedAnnealing](https://user-images.githubusercontent.com/46098223/99931637-46623280-2d7b-11eb-8e2c-7783d5a150e8.png)

Each method is tested upon inputs ranging from 0 - 500 depending upon the time taken to solve the problem for example with Hill Climbing solving for N = 40 on my machine took 85 seconds as plotted in the graphs. Of all the method hill climbing took longest with number of iteration. Failing to solve the problem we tried again with new states as will be visible in the code files for each. Data file generated generated during the final run (captured in video) are included in the jar file submitted with csv extension.
C++ compiled with g++ is used to code the basic logic of the tree algorithms. Clock with precision 6 is used to measure the time between each solution. Care has been taken care to avoid I/O overheads in calculation of Runtime. Data generated in form of ‘N’ and Runtime is logged into a CSV file in runtime dynamically. Parallel to this operation java program is running which loads the the CSV and displays it against the scale of integer N and double time. This data is updated every 1 seconds which is configurable for faster updation. 
To develop the visualizaiton aspect we used java openjdk version 11  javafx 11.02 library and maven in Intellijidea.
