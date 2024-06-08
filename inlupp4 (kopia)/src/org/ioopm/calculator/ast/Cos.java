package org.ioopm.calculator.ast;

public class Cos extends Unary {

    public Cos(SymbolicExpression primary) {
        super(primary);
    }

    public String getName() {
        return "Cos";
    }

    public String toString() {
        // return this.getName() + " " + this.getPrimary().toString();
        return this.getName() + "(" + this.getPrimary().toString() + ")";
    }

    public boolean equals(Object other) {
        if (other instanceof Cos) {
            return this.equals((Cos) other);
        } else {
            return false;
        }
    }
    public boolean equals(Cos other) {
        /// access a private field of other!
        return this.getPrimary().equals(other.getPrimary());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression arg = this.getPrimary().eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
