package org.ioopm.calculator.ast;

public class NamedConstant extends Atom {
    private String key;
    private Double value;

    public NamedConstant(String key, double value) {
        this.key = key;
        this.value = value;
    }

    public String toString() {
        return key;
    }
    
    public Boolean isConstant() {
        return true;
    }

    public SymbolicExpression eval(Environment vars) {
        return new NamedConstant(this.key, this.value);
    }

    public String getVariable() {
        return this.key;
    }

    public double getValue() {
        return this.value;
    }
    
    public boolean equals(Object other) {
        if (other instanceof NamedConstant) {
            return this.equals((NamedConstant) other);
        } else {
            return false;
        }
    }
    public boolean equals(NamedConstant tmp) {
        /// access a private field of other!
        return this.value == tmp.value;
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}

