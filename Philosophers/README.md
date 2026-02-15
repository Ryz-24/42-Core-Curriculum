*This project has been created as part of the 42 curriculum by rzaatreh.*

# PHILOSOPHERS

## Description

**philo** is a multithreaded concurrency project from the 42 curriculum that simulates the classical **Dining Philosophers Problem** using POSIX threads and mutexes.

The goal of the project is to manage shared resources safely between multiple threads while preventing:

* Data races
* Deadlocks
* Starvation
* Undefined behavior

Each philosopher is represented by a thread. Philosophers alternately think, eat, and sleep while sharing forks (mutexes) placed between them.

The simulation stops when:

* A philosopher dies (fails to eat within `time_to_die`)
* Or when all philosophers have eaten a required number of times (if specified)

This project focuses on:

* Thread creation and synchronization (`pthread`)
* Mutex usage for shared resources
* Precise time management
* Race condition prevention
* Proper monitoring of thread state
* Clean program termination

---

## The Dining Philosophers Problem

At a round table:

* There are `N` philosophers
* There are `N` forks
* Each philosopher needs **two forks** to eat
* A fork can only be used by one philosopher at a time

Philosophers follow this cycle:

1. Take left fork
2. Take right fork
3. Eat
4. Sleep
5. Think

If a philosopher does not start eating within `time_to_die` milliseconds since their last meal, they die and the simulation ends.

---

## Program Arguments

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

| Argument                     | Description                                                       |
| ---------------------------- | ----------------------------------------------------------------- |
| `number_of_philosophers`     | Number of philosophers (and forks)                                |
| `time_to_die`                | Time (ms) before a philosopher dies if not eating                 |
| `time_to_eat`                | Time (ms) spent eating                                            |
| `time_to_sleep`              | Time (ms) spent sleeping                                          |
| `number_of_meals` (optional) | Simulation stops when every philosopher has eaten this many times |

---

## Example

```
./philo 5 800 200 200
```

* 5 philosophers
* A philosopher dies if they don't eat within 800 ms
* Eating takes 200 ms
* Sleeping takes 200 ms

---

## Output Format

The program prints state changes in the following format:

```
timestamp philosopher_id action
```

Example:

```
0 1 has taken a fork
1 1 is eating
201 1 is sleeping
```

Possible actions:

* `has taken a fork`
* `is eating`
* `is sleeping`
* `is thinking`
* `died`

Output is protected by a mutex to prevent mixed or corrupted lines.

---

## Implementation Details

* One thread per philosopher
* One mutex per fork
* One mutex for printing
* One mutex for meal tracking
* A separate monitor thread checks:

  * Death conditions
  * Meal completion conditions

The implementation guarantees:

* No deadlocks
* No fork stealing
* No mixed output
* Accurate death timing (within acceptable margin)
* Proper cleanup of all allocated memory and mutexes

---

## Evaluation Requirements

The project respects the following constraints:

* No more than 200 philosophers
* No time value below 60 ms
* One fork per philosopher
* One mutex per fork
* No global variables
* No data races
* Clean exit without memory leaks

Test cases include:

```
./philo 1 800 200 200
./philo 5 800 200 200
./philo 4 310 200 100
./philo 5 800 200 200 7
```

---

## Compilation

### Prerequisites

* Unix-based system (Linux/macOS)
* `cc`
* `make`
* POSIX threads library

### Build

```
make
```

### Clean

```
make clean
make fclean
make re
```

---

## Project Structure

```
philo/
├── main.c
├── init.c
├── routine.c
├── actions.c
├── forks.c
├── monitor.c
├── time.c
├── utils.c
├── philo.h
└── Makefile
```

---

## Key Concepts Learned

* Thread synchronization using `pthread_mutex`
* Preventing deadlocks with fork ordering strategy
* Accurate time tracking with millisecond precision
* Designing a monitor system for concurrent programs
* Understanding starvation vs fairness
* Writing deterministic multi-threaded code

---

## Resources
[Philosophers 42 Guide](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

---
## AI Usage

AI tools were used strictly as a learning assistant.

They were used to:

* Clarify concurrency concepts
* Understand thread synchronization behavior
* Review race condition scenarios
* Improve documentation clarity
* Provided multiple test cases
* 
