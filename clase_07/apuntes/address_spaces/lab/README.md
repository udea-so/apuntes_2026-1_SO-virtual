# Lab

The program, `use-memory` has already been created. You can take a look at the [source code](use-memory.c) if you would like. The program allocates memory based on input from the user. We do not, however, want to call this program directly. Instead we want to use the GNU `time` [utility](https://www.gnu.org/software/time/) to monitor memory usage for `use-memory`.


The command below calls a script that invokes the time utility and `use-memory` with `200` being a parameter.

```
bash monitor-memory.sh 200
```

You will be asked to call this script with different input and answer the questions below.

### Lab question 1

Run the following command in the terminal:

```
bash monitor-memory.sh 16

Memory Used: 17664 kilobytes
```


What happens when you pass the script a number smaller than 200?
- [x] Less memory is allocated
- [ ] More memory is allocated
- [ ] The same amount of memory is allocated

> When a number smaller than 200 is used, the amount of memory allocated decreases.

### Lab Question 2

Run the following command in the terminal:

```
bash monitor-memory.sh 400

Memory Used: 410880 kilobytes
```

What happens when you pass the script a number larger than 200?
- [ ] Less memory is allocated
- [x] More memory is allocated
- [ ] The same amount of memory is allocated

> If a number larger than 200 is used, the amount of memory allocated increases.

### Lab Question 3

What does the number (`200`, `16`, `400`) passed to the monitor-memory script represent?
- [ ] The amount of memory to be allocated in bytes.
- [ ] The amount of memory to be allocated in kilobytes.
- [ ] The amount of memory to be allocated in gigabytes.
- [x] The amount of memory to be allocated in megabytes.

> This number represents the amount of memory to be allocated in megabytes. **Important**: memory allocation is a complex issue that depends on a variety of factors in addition to the code you write. That is why the script returns a number of kilobytes that converts a similar but not exact number of megabytes.