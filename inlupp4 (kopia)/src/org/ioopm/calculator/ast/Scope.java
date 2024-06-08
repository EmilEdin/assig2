package org.ioopm.calculator.ast;


public class Scope extends Unary {
    
    public Scope(SymbolicExpression expression) {
        super(expression);
    }

    @Override
    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'eval'");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    public String toString() {
        return "{" + this.getPrimary().toString() + "}";
    }

    public boolean equals(Object other) {
        if (other instanceof Scope) {
            return this.equals((Scope) other);
        } else {
            return false;
        }
    }
    public boolean equals(Scope other) {
        /// access a private field of other!
        return this.getPrimary().equals(other.getPrimary());
    }

}
