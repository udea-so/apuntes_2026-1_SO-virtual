# CPU Scheduling

## Objectives

* **Identify and Describe** the primary objectives and purposes of scheduling policies within an operating system.
* **Explain** the key assumptions made when designing and implementing scheduling policies.
* **Measure** and evaluate the performance of different scheduling policies based on essential metrics.
* **Compare and Contrast** the advantages and disadvantages of different scheduling policies in various scenarios.
* **Apply** theoretical knowledge of scheduling to practical situations, ensuring efficient CPU utilization and process execution.

## Contenido

* Introduction to CPU Scheduling
* Scheduling metrics
* FIFO: First In, First Out
* SCF: Shortest Completion First
* STCF: Shortest Time-to-Completion First 
* A new metric: Response Time
* Round Robin
* Incorporating I/O
* The Final Assumption
* Summary

## Introduction to CPU Scheduling

Now that we’re equipped with an understanding of low-level process mechanisms, it’s time to delve into the world of the OS **scheduler**.

The **scheduler** is the brain behind determining which processes run, when, and for how long. We’ll explore various **scheduling policies** or **disciplines** that dictate these decisions.

## Workload Assumptions

Before diving into the specifics, it’s important to set some ground rules. These rules, known as **workload assumptions**, form the basis for our initial exploration. By understanding your workload, you’re better positioned to design an effective scheduling policy.

To start, we’ll introduce some **unrealistic workload assumptions**. While these might seem oversimplified, they’ll help us understand core concepts. As we move forward, we’ll gradually modify these assumptions to mirror real-world scenarios more closely.
* **Assumption 1**: All jobs run for the same duration.
* **Assumption 2**: Jobs arrive at the CPU at the same time.
* **Assumption 3**: All jobs run until they are completed.
* **Assumption 4**: All jobs only use the CPU (no I/O operations).
* **Assumption 5**: The OS knows the duration of each job in advance.
Again, all of these assumptions are completely unrealistic, but they are just starting points for us to build our foundation.

## Simulation

Te file [`scheduler_simulation.c`](scr/simple_scheduler/scheduler_simulation.c) simulates the running of processes based on our above assumptions.
* Explore the code and its comments to get a grasp of how it works.
* In the terminal to the lower left, run compile and run the simulator to see it in action.

```
gcc scheduler_simulation.c -o scheduler_simulation
./scheduler_simulation
```

We can modify process parameters and see the scheduler’s decision in real-time.
1. **Jobs' Duration**: Each job has a set duration (in seconds) that it will run for.
   * Currently, all jobs have a default duration 5 of 
 seconds (as per the `DURATION` macro).
   * By modifying this duration, we can change how long each job takes to execute.
   * For example, changing the value of `DURATION` in the code to `#define DURATION 3` will make each job run 3 for seconds.
2. **Number of Jobs**: The current simulation has **three** jobs.
   * We can increase or decrease the number of jobs to see how the scheduler handles more or fewer tasks.
   * Adjust the `JOB_COUNT` macro and ensure that the `jobs` array in the `main` function matches the new count.
   * For example, to simulate **four** jobs:
     * Change `JOB_COUNT` to 4
     * Add another job, like `{4, DURATION}`, to the `jobs` array.
3. **Individual Job Durations**: While our current assumptions state that **all jobs run for the same duration**, we might want to see how the scheduler behaves if one job has a different duration than the others.
   * Directly adjust the duration in the `jobs` array.
   * If we want the second job to run for 7
 seconds, modify the array entry to `{2, 7}`.
4. **Job Arrival Order**: By changing the order of jobs in the `jobs` array, we can simulate the effect of different job arrival sequences on the scheduler.
   * Rearrange the order of the job structures in the `jobs` array.
   * To have **Job 3** run before **Job 1**, adjust the array to: 

   ```c
   Job jobs[JOB_COUNT] = {
      {3, DURATION}
      {1, DURATION},
      {2, DURATION},  
   };
   ```

After making your modifications, **compile** and **run** the code again in the terminal panel to see the scheduler’s decisions in real-time.

As we progress, keep these assumptions in mind. They’ll serve as our initial guiding light, setting the stage for more complex scheduling disciplines.

## Scheduling Metrics

* Turnaround time
* Response time

## Scheduling

* FIFO
* SJF
* STCF
* RR
