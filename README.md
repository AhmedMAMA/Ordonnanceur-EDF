# EDF Scheduling Algorithm Implementation

This project is a C-based implementation of the **Earliest Deadline First (EDF)** scheduling algorithm, commonly used in real-time systems. The algorithm schedules tasks based on their deadlines, giving higher priority to tasks with earlier deadlines. The implementation manages a set of tasks with attributes like execution time, deadline, and period, and provides a way to simulate their execution while taking into account potential task preemptions.

## Features

- **Task Structure**: Each task is represented by a `Tache` structure, which includes properties such as ID, execution time, deadline, period, priority, and remaining execution time.
- **EDF Algorithm**: The algorithm selects and executes tasks based on their nearest deadlines. Tasks with shorter deadlines have higher priority.
- **Preemption Handling**: If a task with a higher priority becomes available, the current task can be interrupted.
- **Task Management**: Functions to manage and display tasks, update their remaining execution time, and track their execution progress.

## Code Overview

### Structures

- **`Tache`**: Represents a task with attributes like execution time, deadline, period, and remaining time.
- **`DeadLineRelative`**: Used to calculate absolute deadlines and periods during execution.

### Functions

1. **`display_tasks(Tache tasks[], int n)`**: Displays the details of each task (ID, execution time, deadline, period, etc.).
   
2. **`RemainingTime(Tache task[], int n)`**: Resets the remaining execution time of each task to its original execution time.

3. **`TachePrioritaire(Tache task[], int n)`**: Determines the task with the nearest deadline that is ready for execution.

4. **`verifier_temps_activation(int tableau[], int taille)`**: Verifies if a task is ready to be executed by checking its activation time.

5. **`execution(Tache task[], int n, int tache_prioritaire)`**: Simulates the execution of tasks based on the EDF algorithm. It also handles task preemption if a higher priority task becomes available.

6. **`periodEtudde(Tache* task, int n)`**: Analyzes the system to calculate the response time and checks if all tasks are schedulable.

### Example Main Function

The **`main`** function initializes a set of tasks and runs the EDF algorithm. It shows how to display tasks, execute them, and simulate task switching based on priority.

```c
int main(){
    Tache tache[] = {
        {1, 2, 4, 6, 20},
        {2, 3, 8, 8, 15},
        {3, 1, 3, 4, 10}
    };

    printf("Période de testing : %d", periodEtudde(tache, 3));
    printf("Matrice Initial\n");
    display_tasks(tache, 3);
    printf("\n\n");

    RemainingTime(tache, 3);

    printf("Execution 1\n\n");
    execution(tache, 3, TachePrioritaire(tache, 3));
    display_tasks(tache, 3);

    // Continue the execution and display the tasks
    // as the algorithm progresses through the tasks
}
```

## Compilation and Execution

To compile and run the code, use the following commands:

```bash
gcc -o edf_scheduler your_code_file.c -lm
./edf_scheduler
```

Make sure to link the math library (`-lm`) during compilation as functions like `ceil()` are used in the code.

## How the EDF Algorithm Works

1. **Task Selection**: At each step, the task with the nearest deadline that is ready to run is selected.
2. **Preemption**: If a task with a higher priority (earlier deadline) becomes available, the current task may be preempted.
3. **Execution**: The selected task is executed until it completes or gets preempted.

## TODO / Potential Improvements

- Refine the preemption mechanism to handle more complex real-time constraints.
- Further optimize the calculation of deadlines and periods for dynamic scheduling environments.
- Add unit tests for each function to ensure reliability in various scenarios.