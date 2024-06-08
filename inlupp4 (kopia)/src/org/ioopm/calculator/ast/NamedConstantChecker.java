package org.ioopm.calculator.ast;

import org.ioopm.calculator.parser.Constants;
import java.util.*;

public class NamedConstantChecker implements Visitor {
    private ArrayList<Assignment> assign = new ArrayList();
    
    public boolean check(SymbolicExpression topLevel) {
        topLevel.accept(this); 
        if (!assign.isEmpty()) {
            System.out.println("Error, assignments to named constant: ");
            for (int i = 0; i < assign.size(); i++) {   
                System.out.println(assign.get(i));
            }  
            return false;           
        } else {
            return true;
        }
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
        if (a.getRhs().isConstant()) { // or maybe you used just isConstant
            if (Constants.namedConstants.containsKey(a.getRhs().getVariable())) {
                assign.add(a);
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
