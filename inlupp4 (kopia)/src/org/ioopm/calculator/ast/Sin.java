package org.ioopm.calculator.ast;

public class Sin extends Unary {

    public Sin(SymbolicExpression primary) {
        super(primary);
    }

    public String getName() {
        return "Sin";
    }

    public String toString() {
        // return this.getName() + " " + this.getPrimary().toString();
        return this.getName() + "(" + this.getPrimary().toString() + ")";
    }

    public boolean equals(Object other) {
        if (other instanceof Sin) {
            return this.equals((Sin) other);
        } else {
            return false;
        }
    }
    public boolean equals(Sin other) {
        /// access a private field of other!
        return this.getPrimary().equals(other.getPrimary());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression arg = this.getPrimary().eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
