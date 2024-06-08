# assig3

# How to run the program
// Make sure to be in inlupp4 directory first!
*make run
    Runs the Calculator program
*make test
    Runs the tests
    
# Run the files
make classes
java -cp classes org.ioopm.calculator.Calculator < Test1.txt > Test1Output.txt
diff -w Test1Output.txt Test1Expected.txt
java -cp classes org.ioopm.calculator.Calculator < Test2.txt > Test2Output.txt
diff -w Test2Output.txt Test2Expected.txt

# Documentation
* Scopes
The syntax for scopes is the following: {Symbolic Expression}
The semantics for scopes is that when a scope is created, the Symbolic Expression inside of the scope has a new environment that is at the top of a stack of environments, and can access variables assigned down the stack. However, variables inside of the scope can not be accessed outside of it. 
* Conditional
The syntax for conditionals is the following: if (Conditional Expression) {Consequent} else {Alternative}
The semantics for conditional is that when a conditional object is instantiated, it stores the conditional expression, consequent and alternative. Upon evaluation of the conditional expression, it will return either the consequent; if the condition is true, or the alternative; if the condition is false.

* Functions
FunctionList is used to store functiondeclarations, meaning when we define a function it is stores to be used as a checker for when we call an already defined function.

Parameters in function declarations are stored in an ArrayList inside the functionDeclaration object and parameters from a function call are stored aswell in an ArrayList but inside a functionCall object instead. When calling and evaluating a function call, arguments are assigned to their respective variable and placed in a ArrayList in a Sequence object, stored in the functionDeclaration. All other 'orders' from the function declaration are stored in another Arraylist in Sequence so that, when calling a function mulitple times, one list gets replaced and the other is kept static.   

During the time when declaring a function, commands can be used but they will not be stored as an order in the new function.