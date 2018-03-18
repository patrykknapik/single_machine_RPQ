# README
Brute force and sortR algorithm for solving single machine RPQ problem

Tasks are created in loop. Values of R, P and Q are generated randomly for every task.
Computation time for both algorithms available for comparison.

You may want to change:
1. Number of tasks by changing `TASK_COUNT`
2. Minimal time for step by changing `MIN_TIME`
3. Maximal time for step by changing `MAX_TIME`
4. You can save some time by turning off `SHOW_PERMUTATIONS`
5. I used `GENERATE_TEST_DATA` to generate below tables

### Test times

| Number of tasks: |sortR  | make span | Brute force | make span|
| ------------- |-------------:| -----:| -----:| -----:|
|2|0.005 ms|37|0.017 ms|37|
|3|0.006 ms|36|0.011 ms|36|
|4|0.006 ms|41|0.016 ms|36|
|5|0.008 ms|71|0.038 ms|61|
|6|0.036 ms|76|0.19 ms|59|
|7|0.008 ms|86|1.425 ms|83|
|8|0.009 ms|86|11.719 ms|80|
|9|0.01 ms|114|117.132 ms|112|
|10|0.012 ms|76|1553.26 ms|59|
|11|0.012 ms|136|14976.5 ms|121|
|12|0.016 ms|140|188554 ms|132|

### Summary
SortR is not perfect but is significantly faster.
 
*for SPD lab pt11 on PWR*