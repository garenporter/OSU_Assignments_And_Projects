-- Garen Porter, porterga

-- Problem 1
-- Define the abstract syntax of MiniLogo as a set of Haskell data types.

type Macro = String
type Var = String
type Prog = [Cmd]

data Mode = Down | Up
         deriving(Eq, Show)

data Cmd = Pen Mode
         | Move Expr Expr
         | Define Macro [Var] Prog
         | Call Macro [Expr]
        deriving(Eq, Show)

data Expr = Var Var
          | Int Int
          | Add Expr Expr
        deriving(Eq, Show)


-- Problem 2
-- Define a MiniLogo macro line (x1,y1,x2,y2) that (starting from anywhere on the canvas) draws a line segment from (x1,y1) to (x2,y2).

{-|

define line (x1,y1,x2,y2) {
        pen up; move (x1,y1);
        pen down; move (x2,y2)
}

-}

line = Define "line" ["x1", "y1", "x2", "y2"] 
                     [(Pen Up), (Move (Var "x1") (Var "y1")), (Pen Down), (Move (Var "x2") (Var "y2"))]


-- Problem 3
-- Use the line macro you just defined to define a new MiniLogo macro nix (x,y,w,h) that draws a big “X” of width w and height h, starting from position (x,y).

{-|

define nix (x,y,w,h) {
        call line (x,y,x+w,y+h);
        call line (x+w,y,x,y+h);
}

-}

nix = Define "nix" ["x", "y", "w", "h"] 
                   [Call "line" [Var "x", Var "y", (Add (Var "x") (Var "w")), (Add (Var "y") (Var "h"))], 
                   Call "line" [(Add (Var "x") (Var "w")), Var "y", Var "x", (Add (Var "y") (Var "h"))]]


-- Problem 4
-- Define a Haskell function steps :: Int -> Prog that constructs a MiniLogo program that draws a staircase of n steps starting from (0,0).

steps :: Int -> Prog
steps 0 = []
steps n = steps (n-1) ++ [(Pen Up), (Move (Int n) (Int n)), (Pen Down), (Move (Int (n-1)) (Int n)), (Move (Int (n-1)) (Int (n-1)))]


-- Problem 5
--  Define a Haskell function macros :: Prog -> [Macro] that returns a list of the names of all of the macros that are defined anywhere in a given MiniLogo program.

macros :: Prog -> [Macro]
macros [] = []
macros ((Define m _ _):t) = m : macros t
macros (h:t) = macros t  


-- Problem 6
-- Define a Haskell function pretty :: Prog -> String that pretty-prints a MiniLogo program. 

pretty :: Prog -> String
pretty [] = ""
pretty (h:t) = makePrettyCmd h ++ pretty t

-- Helper functions for pretty

makePrettyCmd :: Cmd -> String
makePrettyCmd (Pen Down) = "pen down;\n"
makePrettyCmd (Pen Up) = "pen up;\n"
makePrettyCmd (Move e1 e2) = "move (" ++ (makePrettyExpr e1) ++ "," ++ (makePrettyExpr e2) ++ ");\n"
makePrettyCmd (Define m t p) = "define " ++ m ++ "(" ++ (makePrettyVarList t) ++ ")" ++ "{\n" ++ (pretty p) ++ "}\n"
makePrettyCmd (Call m e) = "call " ++ m ++ "(" ++ (makePrettyExprList e) ++ ")" ++ ";\n"

makePrettyExpr :: Expr -> String
makePrettyExpr (Var v) = v
makePrettyExpr (Int i) = show i
makePrettyExpr (Add e1 e2) = (makePrettyExpr e1) ++ "+" ++ (makePrettyExpr e2)

makePrettyVarList :: [Var] -> String
makePrettyVarList [] = ""
makePrettyVarList [h] = h
makePrettyVarList (h:t) = h ++ "," ++ (makePrettyVarList t)

makePrettyExprList :: [Expr] -> String
makePrettyExprList [] = ""
makePrettyExprList [h] = makePrettyExpr h
makePrettyExprList (h:t) = (makePrettyExpr h) ++ "," ++ (makePrettyExprList t)