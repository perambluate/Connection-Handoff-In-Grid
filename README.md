A C++ project for one of the projects in the Wireless Communication course I took in the 2020 autumn.

> This is a repo to demonstrate my programming skill in C++ for job hunting though, welcom to ask any question related to this repo.

## Project Description
Consider in a 9-by-9 grid, there are cars moving on the grid points. The distance between two neighbor grid points is 100 meter. When a car moving in the grid, it needs to connect to a based station with which the connection strength is strong enough. There four base stations sat at `(3.3, 3.5)`, `(6.4, 3.1)`, `(3.6, 6.8)`, `(6.6, 6.58)` in the grid coordinates. We want to apply a policy of connections between cars and base stations such that each car should connect to a base station with a connection as strong as better while keeping the number of handoffs not too high.
> A handoff happens when a car switch its connection from one base station to another.

### Key points
1. A 9-by-9 grid with **cell length 100 meter**
2. The entry of the cars follows the model of the **Poisson process** (characterized by the parameter $\lambda$) in each entry point
3. In each step, each car moves towards the neighbor grid point in one of the three directions: **straight (.6), turn right (.2), turn left (.2) following the probabilities in the brackets**
3. 4 base stations (in grid coordinates): **`(3.3, 3.5)`, `(6.4, 3.1)`, `(3.6, 6.8)`, `(6.6, 6.58)`**
4. Handoff policies: In each step, decide whether to switch to another base station for a better connection or keep the same connection to avoid the handoff
5. **One-day simulation time** with **one-second time step**
6. **In each step, before cars moving, there is a 1000-step entry time**, in which cars entering the grid following the Poisson process

### Policies
1. *Best policy*: Always connect to the base station with the strongest connection strength.
2. *Threshold policy*: Switch to another base station when the current connection strength **belows a preset parameter (threshold)** and the new connection strength is better than the current one and the rest at the same time.
3. *Entropy policy*: Switch to another base station when it provides a conection of which strength is **larger than the current one by a preset parameter (gap)**.
4. *My policy*: A policy kinda mixing the *entropy policy* and *threshold policy* with **two preset parameters for the threshold and the gap** while the handoff in *entropy policy* follows the probability in the following formula
$$P(d_\text{old}, d_\text{new}) = 1 - \frac{d_\text{new}}{d_\text{old}}.$$
> $d_\text{old}$ ($d_\text{new}$) is the distance between the car and the current (new) base station.

### Performance
1. **Average connection power**: the **larger** the better
2. **Number of handoffs**: the **less** the better

### Simulation results
You can find the statistics of the simulations in `Handoff_Table.txt` or `Handoff_Table.xlsx` and a *Chinese* report with detail explaination for my policy in `report.docx` or `report.pdf`.

## Quick use
### Prerequisite
Require `g++` for compiling the executable from `.cpp` files.

### Compilation
Create a folder to collect executables
```
mkdir bin/
```
Compile the executable with the command
```
g++ -o bin/main.exe src\main.cpp src\BS_power.cpp src\car.cpp src\random.cpp src\policy.cpp
```

Alternatively, one can compile the submodules to object files and link them when compiling the main file
```
mkdir lib/
g++ -o lib/BS_power.o -c src/BS_power.cpp
g++ -o lib/car.o -c src/car.cpp
g++ -o lib/random.o -c src/random.cpp
g++ -o lib/policy.o -c src/policy.cpp
g++ lib/car.o lib/BS_power.o lib/random.o lib/policy.o -o bin/main.exe src\main.cpp
```

### Run
```
./bin/main.exe
```

### Output
Check `out/main.txt` to see the example output.

## Tests
There are two tests one can perform to test 1) for `BS_power.cpp` and 2) the simulation.
Compile them with the command
```
g++ -o bin/test_BS_power.exe tests\test_BS_power.cpp src\BS_power.cpp
g++ -o bin/test_simulation.exe tests\test_simulation.cpp src\BS_power.cpp src\car.cpp src\random.cpp src\policy.cpp
```

Similary, one can also use
```
g++ lib/BS_power.o -o bin/test_BS_power.exe tests\test_BS_power.cpp
g++ lib/car.o lib/BS_power.o lib/random.o lib/policy.o -o bin/test_simulation.exe tests\test_simulation.cpp
```
### Run the tests
```
./bin/test_BS_power.exe
./bin/test_simulation.exe
```

### Check the test
1. Compare the output from `test_BS_power.exe` and `out/test_BS_power.txt`, they should be exactly the same.
2. Compare the output from `test_simulation.exe` and `out/test_simulation.txt`, their format should be the same while the numbers could be different as the simulation including random number generation.