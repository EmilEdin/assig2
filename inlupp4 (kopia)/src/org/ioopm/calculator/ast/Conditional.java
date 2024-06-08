package org.ioopm.calculator.ast;

public class Conditional extends Binary {
    private SymbolicExpression trueBranch;
    private SymbolicExpression falseBranch;
    private String name;

    public Conditional(SymbolicExpression lhs, SymbolicExpression rhs, String name, SymbolicExpression trueBranch, SymbolicExpression falseBranch) {
        super(lhs, rhs);
        this.name = name;
        this.trueBranch = trueBranch;
        this.falseBranch = falseBranch;
    }

    public String getName() {
        return name;
    }

    public SymbolicExpression getTrueBranch() {
        return trueBranch;
    }
    
    public SymbolicExpression getFalseBranch() {
        return falseBranch;
    }

    
    @Override
    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        throw new UnsupportedOperationException("Unimplemented method 'eval'");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    public String toString() {
        return String.valueOf("if " + getLhs() + " " + getName() + " " + getRhs() + 
                        " { " + getTrueBranch() + " }" + " else " + "{ " + getFalseBranch() + " }");
    }

    public boolean equals(Object other) {
        if (other instanceof Conditional) {
            return this.equals((Conditional) other);
        } else {
            return false;
        }
    }
    public boolean equals(Conditional other) {
        /// access a private field of other!
        return getLhs().equals(other.getLhs()) && 
               getRhs().equals(other.getRhs()) && 
               getName().equals(other.getName()) &&
               getTrueBranch().equals(other.getTrueBranch()) &&
               getFalseBranch().equals(other.getFalseBranch());
    }
 }
