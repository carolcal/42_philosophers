# Philosophers

A C implementation of the classic Dining Philosophers problem, demonstrating concurrent programming with threads and mutex.

## Project Overview

A number of philosophers sit in a circle around a table with one fork between each pair. Philosophers alternately think, eat, and sleep. To eat, a philosopher must pick up both the left and right forks. Only one philosopher can hold a fork at a time. The simulation continues until a philosopher dies (fails to eat in time) or all philosophers have eaten a certain number of times.

**This project emphasizes:**
- Thread creation and management
- Fork protection via mutexes
- Avoidance of race conditions and deadlocks
- High-precision timing in milliseconds
- Clean shutdown logic via a monitoring thread

## Program Behavior & Logging

- Philosophers numbered from 1 to n.
- Circular layout: Philosopher 1’s left neighbor is Philosopher n.
- Logs must include timestamps in milliseconds since the simulation start.
- Each message on its own line.
- The “died” message must appear no more than 10 ms after the actual simulated death time.

Expected log:
```
- [timestamp] X has taken a fork
- [timestamp] X is eating
- [timestamp] X is sleeping
- [timestamp] X is thinking
- [timestamp] X died
```


## Implementation Details
1. ### Threads & Mutexes
- Each philosopher is implemented as a thread.
- Forks have each a `status` are represented by `pthread_mutex_t`, one per philosopher.
- Philosophers must lock both adjacent forks before eating and unlock them afterward to prevent race conditions.

2. ### Avoiding Deadlocks
   The used strategy was ordered fork acquisition: Even-indexed philosophers pick up the left fork first, odd-indexed pick up the right first, this resource ordering avoids circular wait.

4. ### Time Function
   `get_time()` function returns current time in milliseconds using `gettimeofday()`.

5. ### Monitoring Thread
   A monitor thread constantly checks:
    - If any philosopher has exceeded time_to_die since their last meal → declare death and stop simulation.
    - If all philosophers have eaten the required number of times (when specified) → stop simulation.
    - `stop` function is used to stop simulation and comunicate that to other parts of the program.

## Compile and Run

### Usage

Compile using the provided Makefile in the root directory:

```
make
```


Run the executable with:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments
- number_of_philosophers: Number of philosophers (and forks)
- time_to_die (ms): Maximum time a philosopher can go without eating
- time_to_eat (ms): How long eating lasts
- time_to_sleep (ms): How long sleeping lasts
- number_of_times_each_philosopher_must_eat (optional): Simulation ends when every philosopher has eaten this many times; otherwise, it ends on a philosopher’s death 

### Examples
- `./philo 1 800 200 200`: One philosopher with only one fork—cannot eat and will die after ~800 ms.
- `./philo 5 800 200 200`: All five philosophers should eat, think, and sleep indefinitely without any deaths.
- `./philo 5 800 200 200 7`: The simulation stops once each philosopher has eaten 7 times.
- `./philo 4 310 200 100`: Likely results in a philosopher dying due to tight timing constraints.
