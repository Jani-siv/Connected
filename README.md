# Connected
## Background for a project
Most projects that I have done,
I haven't seen class dependency as problematic.
Now I've come more familiar with the subject, and now I want to correct this way of thinking.
I want
to study more deeply object-oriented software development how design
and implement classes with minimal number of dependencies. 
Dependencies are not always bad and with object-oriented programming,
we need to create dependencies to interact with other objects.
Still, when creating class, we need to keep in mind all dependency's and avoid unnecessary dependencies between classes.

# Project diary
## Planning
### 29.1.2029
The current plan is to get an overall overview scope of the project. 
Because this project is related to my thesis work and I have only limited time,
I need to specify scope for this project.
#### Updates
* Fill readme.md file with ideas and what project is about
* Determine project scope

# Dependencies types
## Circular dependencies
[Circular dependencies](https://en.wikipedia.org/wiki/Circular_dependency) are that object A depends on object B and another way around.
This is the same kind problem as a chicken egg dilemma.
Compiler will inform about this issue if classes are set like in picture below. 

![Circular dependency](./images/circularDepend.png)

[Mutual recursion](https://en.wikipedia.org/wiki/Mutual_recursion) is when
two functions share the same data and make recursive calculations for it,
for basic example of this can be found from Wikipedia.
``` 
bool is_even(unsigned int n) {
    if (n == 0)
        return true;
    else
        return is_odd(n - 1);
}

bool is_odd(unsigned int n) {
    if (n == 0)
        return false;
    else
        return is_even(n - 1);
}
```
For test this recursive function, we give number 4 is_odd function. 
is_odd function will pass 4-1 to is_even function.
This continues between functions until the given number is 0.
These two functions depend on each other to perform calculations.

## Cyclic dependencies
A cyclic dependency is formed when two or more abstractions have direct or indirect dependencies on each other.
Cyclic dependencies between abstractions violate the [Acyclic Dependencies Principle (ADP)](https://en.wikipedia.org/wiki/Acyclic_dependencies_principle)
and Ordering Principle.
(Girish Suryanarayana, Ganesh Samarthyam, Tushar Sharma. Refactoring for software. Desing Smells. 2014)
Cyclic dependencies between two abstractions solved using interface.

![Circular dependency](./images/cyclic_solved.png)

# Cmake
# Libraries static and dynamic
# C++