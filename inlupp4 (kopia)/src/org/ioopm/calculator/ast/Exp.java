package org.ioopm.calculator.ast;

public class Exp extends Unary {

    public Exp(SymbolicExpression primary) {
        super(primary);
    }

    public String getName() {
        return "Exp";
    }

    public String toString() {
        return this.getName() + "(" + this.getPrimary().toString() + ")";
    }

    public boolean equals(Object other) {
        if (other instanceof Exp) {
            return this.equals((Exp) other);
        } else {
            return false;
        }
    }
    public boolean equals(Exp other) {
        /// access a private field of other!
        return this.getPrimary().equals(other.getPrimary());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression arg = this.getPrimary().eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
