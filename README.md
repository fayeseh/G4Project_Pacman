# Project Pac-Man AI  
This project is to implement AI as a player into a Pac-Man game.  
Our Pac-Man game is based of a re-created C++ console application from https://github.com/dannye/pacplusplusman and we have implemented the neural network and genetic algorithm ourselves.  
We also have to open multiple consoles for each game where we referenced from https://www.codeproject.com/Articles/13368/Multiple-consoles-for-a-single-application and used in our code.  
  
### Neural Network  
The input we have given to the neural network is the X and Y coordinates of the 4 ghosts and Pac-Man himself. The neural network feeds forward the input and calculate it with the corresponding weights for each connection. The output of the neural network is values for w, a, s, d (up, down, left, right) and whichever is the highest, it will be feeded to the game as input. The games runs on a loop where each game tick it will repeatly take input for movements.  
  
### Genetic Algorithm  
All the weights of the neural network and the high score of the game is saved into a DNA. The DNAs will be sorted to the best to worst high score and the top 20% is selected. The selected 20% is crossovered to produce children. The children is then mutated according to the determined mutation probability rate. To make sure a wide variety of genetic is in the pool of population, some random random generated children will have randomly generated weights.  
  
### Clarifications  
This project is meant for learning how to program and code Artificial Intelligence in an application. The code is not optimized and might look messy to some but we are just starting to learn the basics. The code also contains several bugs such as the opened consoles printing weird characters, the generation bottlenecks due to lack of input for neural network and the windows error sounds are produced during the program running. Due to time limitations, we are not able to fix these problems and we might look to improve it in the future.
