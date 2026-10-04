# Grammar


Program -> Expr* EOF ;

Expr    -> Factor ("+" Factor) * ";" ;
