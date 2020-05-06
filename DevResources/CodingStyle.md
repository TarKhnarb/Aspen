# Coding style convention

---

## Code formatting

* Always indent with **4 spaces**, not tabulation.
* Return 2 lines after opening a new bock (`{}`) :
    > type function(parameters){
    >   
    >   `Function body`                                                  
    > }
* Do not use space before open new bloc (`{}` or `()`)
* Use line spacings to separate statements that do distinct things
* Use spaces betweens objects and operators
* Write a space after each comma

### Flow-of-control statements

* Do not write a space after `if`, `while`, `switch` and `for`
* In `for` statements, let a space after expressions separators
* In `switch` statements, indent after `case:` and outdent after `break,`

### Classes

* In constuctors initializer list, take one line per attribute and end each line with `,`
* Separate each type of declarations (attributes, methods, type aliases) with the appropriate `public`, `private` or `protected` section

---

## Writing conventions

* Code in english
* Use logical and understandable variable names and write them in CamelCase
* Object and class names begin with an uppercase letter, other names begin with a lowercase letter

### Comments

* Use C style comments (`/* */`) to separate global blocks, and C++ style comments (`//`) otherwise
* If a comment describes a block of code, write it overhead
* If it describes a unique line, write it afterwards, one the same line

---

## Code content

* Don't use `using namespace`
* Use `using` rather than `typedef`

### Declarations

* Don't use global or preprocessor variables for computations
* Declare only one variable per line
* Attach `*` or `&` to the varible name
* As much as possible and if necessary, use `const`, `constexpr`, `static`, `inline`, `explicit`

### Functions

* For unmodified functions parameters, use `const &` if the size of the parameter is variable

---

# Github

* Choose understandable and comprehensive comments, and write them in english
* Don't commit if it doesn't work or doesn't compile

---

And don't forget, be **consistent** !
