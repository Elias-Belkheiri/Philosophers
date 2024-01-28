# Dining Philosophers Problem

## Introduction

This project focuses on implementing a solution to the classic Dining Philosophers problem using the concepts of threads, mutexes, data races, and semaphores.

## The Problem

Imagine a circular table where N philosophers are seated, pondering life's profound questions. To eat, each philosopher needs two forks, one on their left and one on their right. However, there are only N forks available, creating a shared resource challenge. The goal is to design a program where philosophers can eat without:

**Starvation:** A philosopher waiting indefinitely due to others always grabbing forks.

**Deadlock:** A circular blocking chain where all philosophers wait for a fork held by another.

## Implementation

**Threads:** Each philosopher is represented by a thread. Threads run concurrently, simulating the actions of the philosophers.

**Mutexes:** Mutexes are used to control access to the forks. A mutex is associated with each fork to prevent more than one philosopher from holding it simultaneously.

**Semaphores:** Semaphores can be used to control the number of philosophers that are allowed to try and acquire forks at any given time.

**Data Race Prevention:** Careful management of shared resources (forks) to prevent data races. Using mutexes to ensure mutual exclusion.


## Getting Started

### Clone the repository:
```
git clone https://github.com/Elias-Belkheiri/Philosophers.git && cd Philosphers && cd Philo
```
### Compile the program:
```
make
```
### Run the simulation: 
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
```
