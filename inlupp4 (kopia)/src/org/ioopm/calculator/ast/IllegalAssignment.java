package org.ioopm.calculator.ast;

public class IllegalAssignment extends RuntimeException {
    public IllegalAssignment() {
        super();
    }
    public IllegalAssignment(String msg) {
        super(msg);
    }   
}
