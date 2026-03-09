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

Example:

```bash
./philo 5 800 200 200
```

Arguments:

| Argument | Description |
|--------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in milliseconds before a philosopher dies without eating |
| `time_to_eat` | Time a philosopher spends eating |
| `time_to_sleep` | Time a philosopher spends sleeping |
| `number_of_meals` | *(Optional)* Program stops after each philosopher eats this many times |

---

## 📂 Project Structure

```
philo/
├── Makefile
├── include/
│   └── philo.h
├── src/
│   ├── 01-parse/
│   ├── 02-init/
│   ├── 03-threads/
│   ├── 04-routines/
│   └── main.c
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
