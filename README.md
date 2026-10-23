# Philosophers

**A concurrent programming project developed in C as part of the 42 School curriculum.**

## Overview

Philosophers is a simulation of the classic **Dining Philosophers Problem**, a synchronization problem in concurrent programming.

In this simulation, several philosophers sit around a table and alternate between three activities: **thinking, eating, and sleeping**.

Each philosopher needs two forks to eat, but each fork is shared between neighboring philosophers.

The main challenge is to coordinate multiple threads while managing shared resources and avoiding synchronization problems such as **race conditions** and **deadlocks**.

The project uses **POSIX threads (`pthread`)** to represent philosophers and **mutexes** to synchronize access to shared resources.

It also includes monitoring mechanisms to detect when a philosopher dies and when all philosophers have completed the required number of meals.

## Technical Concepts

### POSIX Threads

Each philosopher is represented by a separate thread created using `pthread_create()`.

Threads allow multiple philosophers to perform their activities concurrently while sharing the same process memory.

### Mutex Synchronization

Each fork is represented by a POSIX mutex (`pthread_mutex_t`).

A philosopher must acquire both forks before eating.

Mutexes ensure that two neighboring philosophers cannot use the same fork simultaneously.

After eating, the philosopher releases both mutexes, allowing other philosophers to access the shared resources.

### Deadlock Prevention

The implementation uses different fork acquisition orders depending on the philosopher's ID:

- Even-numbered philosophers acquire the right fork first.
- Odd-numbered philosophers acquire the left fork first.

This strategy prevents all philosophers from attempting to acquire their forks in the same order, helping avoid circular waiting conditions.

### Monitoring

The simulation uses monitoring threads to detect when a philosopher exceeds the maximum allowed time without eating.

An additional monitor checks whether all philosophers have completed the required number of meals when the optional argument is provided.

## Compilation & Usage

### Compilation

Clone the repository and compile the project using `make`:

```bash
git clone https://github.com/Yuliano96/philo.git
cd philo
make
```

The compilation generates an executable named `philo`.

Available Makefile commands:

| Command | Description |
|---|---|
| `make` | Compiles the project. |
| `make clean` | Removes object files. |
| `make fclean` | Removes object files and the executable. |
| `make re` | Rebuilds the project from scratch. |

### Usage

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

All time values are expressed in milliseconds.

The optional `number_of_meals` argument specifies how many times each philosopher must eat before the simulation can finish successfully.

### Examples

**Example 1 — Basic simulation**

```bash
./philo 5 800 200 200
```

Starts a simulation with five philosophers.

**Example 2 — Limited number of meals**

```bash
./philo 5 800 200 200 5
```

Starts five philosophers and allows the simulation to finish when each philosopher has eaten at least five times.

**Example 3 — Philosopher death**

```bash
./philo 1 800 200 200
```

Starts a simulation with one philosopher, who cannot acquire two forks and eventually dies.

## Testing

The project was successfully validated at **42 School**.

Several tests were performed to verify philosopher synchronization, meal completion, memory management, and thread safety.

### Simulation Tests

| Test | Description | Result |
|---|---|---|
| Single philosopher | Verifies death detection when only one fork is available. | ✅ PASS |
| 5 philosophers | Verifies that all philosophers eat at least 3 times without dying. | ✅ PASS |
| 100 philosophers | Stress test with 100 concurrent philosophers, each completing at least 3 meals. | ✅ PASS |

### Automated Meal Verification

The repository includes a Bash script called `check_meals.sh`.

It verifies that each philosopher has eaten the required number of times and checks whether any philosopher died.

Example:

```bash
./philo 100 800 200 200 3 > philo_log.txt
bash check_meals.sh 100 3
```

The script reports the result for each philosopher and displays a final success or failure message.

### Concurrency Analysis — Helgrind

Helgrind was used to analyze thread synchronization and detect potential race conditions.

```bash
valgrind --tool=helgrind \
    --log-file=helgrind.log \
    ./philo 5 800 200 200 3
```

**Result:** `ERROR SUMMARY: 0 errors from 0 contexts`

No concurrency errors were reported in this test.

### Memory Analysis — Memcheck

Valgrind Memcheck was used to check for memory leaks and invalid memory accesses.

```bash
valgrind --tool=memcheck \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    ./philo 5 2000 200 200 3
```

**Results:**

- 14 memory allocations.
- 14 memory deallocations.
- 0 bytes allocated at program exit.
- 0 reported memory errors.

All allocated heap memory was released during this test.

## Project Structure

```text
philo/
├── Makefile              # Compiles the project
├── README.md             # Project documentation
├── philo.h               # Structures and function declarations
├── check_meals.sh        # Automated meal verification script
├── docs/
│   └── LEARNING_NOTES.md # Original project learning notes
└── src/
    ├── main.c            # Entry point and argument validation
    ├── thread_init.c     # Philosopher and thread initialization
    ├── aux_thread_init.c # Auxiliary initialization functions
    ├── thread_states.c   # Philosopher lifecycle: think, eat, sleep
    ├── death_monitor.c   # Detects philosopher deaths
    ├── meals_monitor.c   # Monitors required meals
    └── tools.c           # Utility functions
```

## Key Learnings

This project helped me strengthen my understanding of concurrent programming and synchronization in C.

Through its development, I learned how to:

- Create and manage multiple threads using POSIX Threads.
- Identify shared resources and protect them with mutexes.
- Design synchronization strategies to reduce the risk of deadlocks.
- Coordinate thread execution and monitor shared state.
- Debug concurrent programs using Valgrind Helgrind.
- Verify memory management using Valgrind Memcheck.

---

My original project plan and study notes are preserved in [docs/LEARNING_NOTES.md](docs/LEARNING_NOTES.md).
