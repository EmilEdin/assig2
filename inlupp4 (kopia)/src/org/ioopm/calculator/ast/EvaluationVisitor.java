package org.ioopm.calculator.ast;

import java.util.ArrayList;

import org.ioopm.calculator.parser.Constants;

public class EvaluationVisitor implements Visitor {
    private EnvironmentHandler env = null;
    private ArrayList<FunctionDeclaration> functionList = null;

    public SymbolicExpression evaluate(SymbolicExpression topLevel, EnvironmentHandler env, ArrayList<FunctionDeclaration> functionList) {
        this.functionList = functionList;
        NamedConstantChecker namedConstantChecker = new NamedConstantChecker();
        ReassignmentChecker reassignmentChecker = new ReassignmentChecker();
        
        this.env = env;
        // System.out.println(topLevel.toString() + "  [EvaluationVisitor, Rad 13]");
        if (namedConstantChecker.check(topLevel) && reassignmentChecker.check(topLevel)) {
            return topLevel.accept(this);
        }
        else {
            return topLevel;
        }
    }

    // This method gets called from Addition.accept(Visitor v) -- you should
    // be able to see from the eval() methods how these should behave (i.e., 
    // compare this method with your Addition::eval() and Symbolic.addition) 
    public SymbolicExpression visit(Addition n) {
        // Visit the left hand side and right hand side subexpressions
        SymbolicExpression left = n.getLhs().accept(this);
        SymbolicExpression right = n.getRhs().accept(this);
        // When we come back here, the visitor has visited all subexpressions, 
        // meaning left and right point to newly created trees reduced to 
        // the extent possible (best case -- both are constants)

        // If subexpressions are fully evaluated, replace them in
        // the tree with a constant whose value is the sub of the
        // subexpressions, if not, simply construct a new addition
        // node from the new subexpressions
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        } else {
            return new Addition(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Assignment n) {
        SymbolicExpression leftEvaluated = n.getLhs().accept(this);

        // if (Constants.namedConstants.containsKey(n.getRhs().getVariable())) {
        //      throw new IllegalAssignment("cannot redefine named constant");
        // } 
        if (leftEvaluated.isConstant()) {
            env.put((Variable) n.getRhs(), leftEvaluated);
            return new Constant(leftEvaluated.getValue());
        } else {
            env.put((Variable) n.getRhs(), leftEvaluated);
            return leftEvaluated;
        }
    }

    @Override
    public SymbolicExpression visit(Clear n) {
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(Constant n) {
        return new Constant(n.getValue());
    }

    @Override
    public SymbolicExpression visit(Cos n) {
        SymbolicExpression arg = n.getPrimary().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Division n) {
        SymbolicExpression left = n.getLhs().accept(this);
        SymbolicExpression right = n.getRhs().accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() / right.getValue());
        } else {
            return new Division(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Exp n) {
        SymbolicExpression arg = n.getPrimary().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Log n) {
        SymbolicExpression arg = n.getPrimary().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Multiplication n) {
        SymbolicExpression left = n.getLhs().accept(this);
        SymbolicExpression right = n.getRhs().accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() * right.getValue());
        } else {
            return new Multiplication(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Negation n) {
        SymbolicExpression arg = n.getPrimary().accept(this);
        if (arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else {
            return new Negation(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Quit n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(End n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(Sin n) {
        SymbolicExpression arg = n.getPrimary().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Subtraction n) {
        SymbolicExpression left = n.getLhs().accept(this);
        SymbolicExpression right = n.getRhs().accept(this);

        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() - right.getValue());
        } else {
            return new Subtraction(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Variable n) {
        if (env.get(n) != null) {
            return env.get(n).accept(this);
        } else {
            return new Variable(n.getVariable());
        }
    }

    @Override
    public SymbolicExpression visit(Vars n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(NamedConstant n) {
        return new NamedConstant(n.getVariable(), n.getValue());
    }

    @Override
    public SymbolicExpression visit(Scope n) {
        env.Environmentpush(new Environment());
        SymbolicExpression arg = n.getPrimary().accept(this);
        env.Environmentpop();
        return arg;
    }

    @Override
    public SymbolicExpression visit(Conditional n) {
        String name = n.getName();
        SymbolicExpression lhs = n.getLhs().accept(this);
        SymbolicExpression rhs = n.getRhs().accept(this);
        if (lhs.isConstant() && rhs.isConstant()) {
            if (name == "<") {
                if (lhs.getValue() < rhs.getValue()) {
                    return n.getTrueBranch().accept(this);
                } else {
                    return n.getFalseBranch().accept(this);
                }
            }
            else if (name == "<=") {
                if (lhs.getValue() <= rhs.getValue()) {
                    return n.getTrueBranch().accept(this);
                } else {
                    return n.getFalseBranch().accept(this);
                }
            }
            
            else if (name == ">=") {
                if (lhs.getValue() >= rhs.getValue()) {
                    return n.getTrueBranch().accept(this);
                } else {
                    return n.getFalseBranch().accept(this);
                }
            }
            else if (name == ">") {
                if (lhs.getValue() > rhs.getValue()) {
                    return n.getTrueBranch().accept(this);
                } else {
                    return n.getFalseBranch().accept(this);
                }
            }
            else { //name == "=="
                if (lhs.getValue() == rhs.getValue()) {
                    return n.getTrueBranch().accept(this);
                } else {
                    return n.getFalseBranch().accept(this);
                }
            }
        }
        System.out.println("Error, cannot compare a free variable: " + n.getLhs().toString() + name + n.getRhs().toString());
        return n;
    }

    @Override
    public SymbolicExpression visit(Sequence n) {
        SymbolicExpression result = null;
        for (SymbolicExpression expr: n.getAssignmentList()) {
            expr.accept(this);
        }
        for (SymbolicExpression expr: n.getList()) {
            result = expr.accept(this);
        }
        return result;
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'visit'");
    }

    @Override
    public SymbolicExpression visit(FunctionCall n) {
        SymbolicExpression result = null;
        for (FunctionDeclaration function: functionList) {
            if (n.getName().equals(function.getName())) {
                ArrayList<SymbolicExpression> arr = n.getArgList();
                function.getBody().createAssignmentList();
                for (int i = 0; i < arr.size(); i++) {
                    function.getBody().insertAssignmentFirst(new Assignment(arr.get(i), new Variable(function.getList().get(i))));
                }
                result = function.getBody().accept(this);
                return result;
            }
        }
        return n;
    }
   
}
