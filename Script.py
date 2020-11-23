import subprocess
import sys

cmd = "HillClimbingWithRandomRestart.cpp"

print("Running Cpp code for Hill Climbing with Random Restart\n")


f1 = open("./HillClimbingWithRandomRestart.cpp", 'r+')

for n in range(4, 50):
   count = 0
   k = str(n);
   print(k)
   for line in f1:
      count = count+1;
      if(count == 8):
         f2 = open("./HillClimbingRandomRestartII.cpp", 'a')
   #    
         f2.write(line.replace("8", k))
         f2.flush()
         f2.close()
      else:
         f2 = open("./HillClimbingRandomRestartII.cpp", 'a')
    #print(line)
         f2.write(line)
         f2.flush()
         f2.close()
   
