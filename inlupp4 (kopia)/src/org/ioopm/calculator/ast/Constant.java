package org.ioopm.calculator.ast;

public class Constant extends Atom {
    private double value;

    public Constant(double value) {
        this.value = value;
    }
    
    @Override
    public Boolean isConstant() {
        return true;
    }

    public double getValue() {
        return this.value;
    }

    public String toString() {
        return String.valueOf(this.value);
    }
    
    public boolean equals(Object other) {
        if (other instanceof Constant) {
            return this.equals((Constant) other);
        } else {
            return false;
        }
    }
    public boolean equals(Constant tmp) {
        /// access a private field of other!
        return this.value == tmp.value;
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment{
        return new Constant(this.value);
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
