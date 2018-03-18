# README
Brute force and sortR algorithm for solving single machine RPQ problem

Tasks are created in loop. Values of R, P and Q are generated randomly for every task.
Computation time for both algorithms available for comparison.

You may want to change:
1. Number of tasks by changing `TASK_COUNT`
2. Minimal time for step by changing `MIN_TIME`
3. Maximal time for step by changing `MAX_TIME`
4. You can save some time by turning of `SHOW_PERMUTATIONS`
5. I used `GENERATE_TEST_DATA` to generate below tables

###Test times

#####Two Machines
| Number of tasks: |sortR  | make span | Brute force | make span|
| ------------- |-------------:| -----:| -----:| -----:|


###Summary
SortR is not perfect but is significantly faster.
 
*for SPD lab pt11 on PWR*