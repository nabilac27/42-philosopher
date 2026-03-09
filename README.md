# **Philosophers**

This repository contains my implementation of the **Philosophers** project from the **42 School** curriculum.

The goal of this project is to explore **multithreading and synchronization** using **POSIX threads (pthreads)** while solving the classic **Dining Philosophers Problem**.

---

## 🍝 About the Project

The Dining Philosophers problem is a classic computer science problem that demonstrates synchronization issues and resource sharing between multiple threads.

In this simulation:

- Philosophers sit around a table.
- Each philosopher alternates between **thinking**, **eating**, and **sleeping**.
- To eat, a philosopher must pick up **two forks** (shared resources).
- The challenge is to manage these resources without causing:
  - **Deadlocks**
  - **Race conditions**
  - **Starvation**

---

## 🧠 Key Concepts

- **Multithreading**
  - Each philosopher is represented by a thread using `pthread`.

- **Mutexes**
  - Forks are protected by mutexes to avoid data races.

- **Synchronization**
  - Proper locking and unlocking ensures philosophers can safely access shared resources.

- **Time Management**
  - Precise timing ensures correct simulation of eating, sleeping, and thinking.

---


## 🛠️ Concepts Practiced

- `pthread_create`
- `pthread_join`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`
- Thread synchronization
- Deadlock prevention
- Resource management

---

## 📂 Project Structure

```
philo/
├── Makefile
├── include/
│   └── philo.h
├── src/
    ├── 01-parse/
    ├── 02-init/
    ├── 03-threads/
    ├── 04-routines/
    └── main.c
```

### Description

| Folder/File | Description |
|-------------|-------------|
| `Makefile` | Compiles the project and generates the `philo` executable |
| `include/philo.h` | Header file containing structures, prototypes, and includes |
| `src/01-parse` | Handles argument parsing and validation |
| `src/02-init` | Initializes philosophers, forks, and simulation data |
| `src/03-threads` | Manages thread creation and synchronization |
| `src/04-routines` | Contains philosopher routines (eat, sleep, think) |
| `src/main.c` | Entry point of the program |

---

## ⚙️ Functions Overview

| Function | Description |
|----------|-------------|
| `error_msg(char *msg)` | Prints an error message and exits the program. |
| `clean(t_table *table)` | Destroys mutexes and frees all allocated memory used by the simulation. |
| `is_positive(const char *str)` | Checks whether a string contains only positive numeric characters. |
| `check_positive(int argc, char *argv[])` | Verifies that all program arguments are positive numbers. |
| `ft_atol(const char *str)` | Converts a numeric string into a `long`. |
| `parse(t_table *table, int argc, char **argv)` | Parses and validates command-line arguments, then stores them in the table structure. |
| `handle_malloc(size_t bytes)` | Allocates memory safely and exits on failure. |
| `handle_mutex(t_mutex *mutex, t_mutex_type type)` | Wraps mutex initialization, locking, unlocking, and destruction. |
| `assign_forks(t_philo *philo, t_fork *forks, int philo_pos, int num_philos)` | Assigns the left and right forks to each philosopher. |
| `init_philo_struct(t_table *table)` | Initializes each philosopher structure and its mutex. |
| `init_forks_mutex(t_table *table)` | Initializes all fork mutexes. |
| `init_table_mutex(t_table *table)` | Initializes the table-level mutexes. |
| `init_table_struct(t_table *table)` | Initializes the main table structure, philosophers, and forks. |
| `handle_thread(pthread_t *thread, void *(*routine)(void *), void *data, t_thread_type type)` | Wraps thread creation, joining, and detaching. |
| `init_philo_threads(t_table *table)` | Creates all philosopher threads. |
| `init_monitor_thread(t_table *table)` | Creates the monitor thread. |
| `wait_all_philo_threads_finish(t_table *table)` | Waits for all philosopher threads to finish. |
| `wait_monitor_thread_finish(t_table *table)` | Waits for the monitor thread to finish. |
| `all_philos_full(t_table *table)` | Checks whether all philosophers have eaten enough meals. |
| `check_philo_died(t_table *table)` | Detects whether a philosopher has died from starvation. |
| `monitor_routine(void *arg)` | Continuously monitors the simulation for death or completion conditions. |
| `log_status(t_philo *philo, const char *status)` | Prints a philosopher status message with a timestamp. |
| `single_philo(t_philo *philo)` | Handles the special case where only one philosopher exists. |
| `wait_for_all_threads_ready(t_philo *philo)` | Synchronizes philosopher threads so they start together. |
| `philo_routine(void *arg)` | Main routine for each philosopher thread. |
| `first_fork_order(t_philo *philo, t_mutex *first_fork, t_mutex *second_fork)` | Locks forks in the chosen order and logs the action. |
| `lock_forks(t_philo *philo)` | Decides fork-locking timing and order to reduce contention. |
| `eat(t_philo *philo)` | Handles eating, meal counting, and fork release. |
| `sleep_philo(t_philo *philo)` | Handles the sleeping state of a philosopher. |
| `think(t_philo *philo)` | Handles the thinking state with adaptive delay timing. |
| `initial_delay(t_philo *philo)` | Applies a small initial delay for even-numbered philosophers. |
| `delay_time(long usec, t_table *table)` | Performs a controlled delay while checking simulation status. |
| `gettime(t_time_type type)` | Returns the current time in milliseconds or microseconds. |
| `precise_sleep(long duration_ms, t_table *table)` | Sleeps accurately for the requested duration while monitoring simulation end. |
| `get_elapsed_time(t_table *table)` | Returns the elapsed time since the simulation started. |

---

## ⚙️ Program Usage

### Compilation

```bash
make
```

This will generate the executable:

```
philo
```

---

### Running the Program

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

Input Example:

```bash
./philo 5 800 200 200
```

Output Example:
```bash
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
```

Arguments:

| Argument | Description |
|--------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in milliseconds before a philosopher dies without eating |
| `time_to_eat` | Time a philosopher spends eating |
| `time_to_sleep` | Time a philosopher spends sleeping |
| `number_of_meals` | *(Optional)* Program stops after each philosopher eats this many times |
