package org.ioopm.calculator.ast;


public class Negation extends Unary {

    public Negation(SymbolicExpression primary) {
        super(primary);
    }

    public String getName() {
        return "Neg";
    }

    public String toString() {
        return this.getName() + " " + this.getPrimary().toString();
    }

    public boolean equals(Object other) {
        if (other instanceof Negation) {
            return this.equals((Negation) other);
        } else {
            return false;
        }
    }
    public boolean equals(Negation other) {
        /// access a private field of other!
        return this.getPrimary().equals(other.getPrimary());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression arg = this.getPrimary().eval(vars);
        if (arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else {
            return new Negation(arg);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
