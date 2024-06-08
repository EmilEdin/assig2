package org.ioopm.calculator.ast;

public class Log extends Unary {

    public Log(SymbolicExpression primary) {
        super(primary);
    }

    public String getName() {
        return "Log";
    }

    public String toString() {
        return this.getName() + "(" + this.getPrimary().toString() + ")";
    }

    public boolean equals(Object other) {
        if (other instanceof Log) {
            return this.equals((Log) other);
        } else {
            return false;
        }
    }
    public boolean equals(Log other) {
        /// access a private field of other!
        return this.getPrimary().equals(other.getPrimary());
    }
    
    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression arg = this.getPrimary().eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
