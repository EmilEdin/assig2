package org.ioopm.calculator.ast;

import org.ioopm.calculator.parser.Constants;
import java.util.*;
public class ReassignmentChecker implements Visitor {

    private ArrayList<Variable> assign = new ArrayList();
    private boolean isDouble = true;

    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this); 
        return isDouble;
    }
    
   // Recurse down the AST tree
    public SymbolicExpression visit(Addition a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    // When we hit an assignment, make sure to check!
    public SymbolicExpression visit(Assignment a) {
        a.getLhs().accept(this);
        a.getRhs().accept(this);
        System.out.println(assign.size());
        if (a.getRhs() instanceof Variable) { 
            if (assign.contains(a.getRhs())) {
                System.out.println("Error, the variable " + a.getRhs().toString() + " is reassigned.");
                isDouble = false;
            } else {
                assign.add((Variable) a.getRhs());
            }
        }
        return null;
    }

    @Override
    public SymbolicExpression visit(Clear n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(Constant n) {
        return null;
    }

    @Override
    public SymbolicExpression visit(Cos n) {
        n.getPrimary().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Division n) {
        n.getLhs().accept(this);
        n.getRhs().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Exp n) {
        n.getPrimary().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Log n) {
        n.getPrimary().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Multiplication n) {
        n.getLhs().accept(this);
        n.getRhs().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Negation n) {
        n.getPrimary().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Quit n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(Sin n) {
        n.getPrimary().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Subtraction n) {
        n.getLhs().accept(this);
        n.getRhs().accept(this);
        return null; // We never read the result, so we can return whatever
    }

    @Override
    public SymbolicExpression visit(Variable n) {
        return null;
    }

    @Override
    public SymbolicExpression visit(Vars n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(NamedConstant n) {
        return null;
    }

    @Override
    public SymbolicExpression visit(Scope n) {
        ReassignmentChecker reassignmentChecker = new ReassignmentChecker();
        isDouble = reassignmentChecker.check(n.getPrimary());
        return null;
    }

	@Override
	public SymbolicExpression visit(Conditional n) {
        n.getLhs().accept(this);
        n.getRhs().accept(this);
        n.getTrueBranch().accept(this);
        n.getFalseBranch().accept(this);
		return null;
	}

	@Override
	public SymbolicExpression visit(End n) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'visit'");
	}


    @Override
    public SymbolicExpression visit(Sequence n) {
        for (SymbolicExpression expr: n.getList()) {
            expr.accept(this);
        }
        return null;
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n) {
        return null;
    }

    @Override
    public SymbolicExpression visit(FunctionCall n) {
        return null;
    }

    
}
