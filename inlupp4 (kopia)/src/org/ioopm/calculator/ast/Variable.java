package org.ioopm.calculator.ast;

import java.util.Objects;

public class Variable extends Atom implements Comparable<Variable> {
    private String identifier;
    
    public Variable(String identifier) {
        this.identifier = identifier;
    }

    public String toString() {
        return String.valueOf(this.identifier);
    }

    public String getVariable() {
        return this.identifier;
    }

    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } else {
            return false;
        }
    }
    
    public boolean equals(Variable tmp) {
        /// access a private field of other!
        return this.identifier.compareTo(tmp.toString()) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(identifier);
    }

    public SymbolicExpression eval(Environment vars) {
        if (vars.get(this) != null) {
            return vars.get(this);
        } else {
            return new Variable(this.identifier);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    @Override
    public int compareTo(Variable other) {
        Objects.requireNonNull(other);

        // Compare variable names in a case-insensitive manner
        return this.getVariable().compareToIgnoreCase(other.getVariable());
    }

}
