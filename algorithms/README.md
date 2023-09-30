# Pain Points
1. Many useful video tutorials do not offer clear code implementations, or code that is already domain-specific
2. To compete in the software domain, we need to master algorithms. Which ones are important, and which ones have the seniors learnt?
3. With so many algorithms, what is the core logic; what is the accurate implementation of each algorithm? The total time all university students spent researching for the bugless algorithm is unnecessary as we repeatedly search for the same thing -- algorithms. Yet we do not know which ones are correct

# Purposes
1. Create **accurate and functioning** algorithms that are **reviewed publicly** by university students
2. Mentally prepare students on the **amount of algorithms they should master** before they leave university
3. **Raise the algorithmic standard** among university students by first putting forward all basic algorithms students should learn: implementation and complexity analysis

# Using this Repository
Caution: by using this repo, you agree not to claim this repo as your own or use it for commercial purposes, such as displaying on your, or another third-party personal or commercial website.

## Project Structure

## Principles
1. Code is written as generic as possible for two reasons
   - To learn real-life considerations: e.g. time-memory tradeoff, memory growth
   - In case this repository is reused as a library for students

# Contributions
This repository is first initiated from Nanyang Technological University, with the aim of raising the computing skills of Malaysian students in NTU. However, foreseeing that this project can assist people even outside the community, any students from high school or tertiary institutions are free to contribute. 

## Conventions
We strive to shorten the learning time of our users. Hence, the following conventions shall be adhered:
### C++
```cpp
#include <any_libraries>
/*
(1) annotations right after importing libraries
*/
class ClassNameTitleCase{
    private:
        int anyVariableNoUnderscoreAndCamelCase;
        void _func_prefixed_with_underscore();  // (1) annotate any code, preferably at most 2 lines
    public:
        void func_not_prefixed_with_underscore();
}
```

### Python