*This project has been created as part of the 42 curriculum by rzaatreh.*

# push_swap

## Description
**push_swap** is a sorting algorithm project from the 42 curriculum.  
The goal is to sort a stack of integers using a limited set of operations, while minimizing the total number of moves.

The program manipulates two stacks, **stack A** and **stack B**, and must output a sequence of instructions that sorts stack A in ascending order.  
Only specific operations are allowed, making algorithmic efficiency and optimization the core challenges of this project.

This project focuses on:
- Algorithm design and optimization
- Stack manipulation
- Complexity analysis
- Writing efficient and clean C code under strict constraints

---

## Allowed Operations

- **sa** — swap the first two elements of stack A  
- **sb** — swap the first two elements of stack B  
- **ss** — `sa` and `sb` at the same time  

- **pa** — push the top element from stack B to stack A  
- **pb** — push the top element from stack A to stack B  

- **ra** — rotate stack A (first element becomes last)  
- **rb** — rotate stack B  
- **rr** — `ra` and `rb` at the same time  

- **rra** — reverse rotate stack A (last element becomes first)  
- **rrb** — reverse rotate stack B  
- **rrr** — `rra` and `rrb` at the same time  

---

## Instructions

### Prerequisites
- Unix-based operating system (Linux or macOS)
- `cc`
- `make`

### Compilation
Clone the repository and compile the project using `make`:

```bash
make

./push_swap 3 2 5 1 4
```
This will output a list of operations needed to sort the stack.

To check the correctness using checker:

        ./checker <list_of_integers>

Then input the operations (or pipe them from push_swap):


        ./push_swap 3 2 5 1 4 | ./checker_OS 3 2 5 1 4

If the stack is sorted correctly, checker will display OK, otherwise KO.

## Resources

Big-O Notation and time complexity basics

Sorting algorithms (insertion sort, radix sort, chunk-based sorting)

https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a

https://42-cursus.gitbook.io/guide/2-rank-02/push_swap

https://github.com/dpetrosy/42-Push-Swap?utm_source=chatgpt.com

### AI Usage

---
AI tools were used as a learning and assistance resource, not as a code generator.

They were used to:

Clarify project requirements and constraints.

Understand algorithmic strategies and complexity trade-offs

Improve code structure and readability
