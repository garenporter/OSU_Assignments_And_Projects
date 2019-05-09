-- Garen Porter, porterga

module KarelSemantics where

import Prelude hiding (Either(..))
import Data.Function (fix)

import KarelSyntax
import KarelState


-- | Valuation function for Test.
test :: Test -> World -> Robot -> Bool
test (Not t) w r
    | (test t w r) == False = True
    | otherwise = False
test (Facing c) _ (_,cr,_) 
    | c == cr = True
    | otherwise = False
test (Clear d) w (p,c,_) 
    | isClear (neighbor (cardTurn d c) p) w == True = True
    | otherwise = False
test Beeper w (p,_,_)
    | hasBeeper p w == True = True
    | otherwise = False
test Empty _ (_,_,b)
    | b == 0 = True
    | otherwise = False

-- | Valuation function for Stmt.
stmt :: Stmt -> Defs -> World -> Robot -> Result
stmt Shutdown   _ _ r = Done r
stmt PickBeeper _ w r = let p = getPos r
                        in if hasBeeper p w
                              then OK (decBeeper p w) (incBag r)
                              else Error ("No beeper to pick at: " ++ show p)
stmt Move _ w r
    | test (Clear Front) w r == True = OK w (moveFront r)
    | otherwise = Error ("Blocked at: " ++ (show (getPos(moveFront r))))
stmt PutBeeper _ w r 
    | isEmpty r == False = OK (incBeeper (getPos r) w) (decBag r)
    | otherwise = Error "No beeper to put."
stmt (Turn d) _ w r = OK w (setFacing (cardTurn d (getFacing r)) r)
stmt (Block [x]) d w r = stmt x d w r
stmt (Block (h:t)) d w r
    | isOK (stmt h d w r) == True = stmt (Block t) d (getWorld (stmt h d w r)) (getRobot (stmt h d w r))
    | otherwise = stmt h d w r
stmt (If t s1 s2) d w r 
    | test t w r == True = stmt s1 d w r
    | otherwise = stmt s2 d w r
stmt (Call m) d w r 
    | lookup m d == Nothing = Error ("Undefined macro: " ++ m)
    | otherwise = stmt (fromJust (lookup m d)) d w r
stmt (Iterate 0 s) d w r = OK w r
stmt (Iterate n s) d w r 
    | isOK (stmt s d w r) == True = stmt (Iterate (n-1) s) d (getWorld (stmt s d w r)) (getRobot (stmt s d w r))
    | otherwise = stmt s d w r
stmt (While t s) d w r
    | test t w r == False = OK w r
    | (isOK (stmt s d w r) == True) && (test t w r == True) = stmt (While t s) d (getWorld (stmt s d w r)) (getRobot (stmt s d w r))
    | isError (stmt s d w r) == True = stmt s d w r
    | otherwise = Done r

-- | Run a Karel program.
prog :: Prog -> World -> Robot -> Result
prog (m,s) w r = stmt s m w r

-- | Helper functions
moveFront :: Robot -> Robot
moveFront ((x,y),c,b)
    | c == East = ((x+1,y),c,b)
    | c == West = ((x-1,y),c,b)
    | c == North = ((x,y+1),c,b)
    | c == South = ((x,y-1),c,b)

isOK :: Result -> Bool
isOK (OK _ _) = True
isOK _ = False

isDone :: Result -> Bool
isDone (Done _) = True
isDone _ = False

isError :: Result -> Bool
isError (Error _) = True
isError _ = False

getWorld :: Result -> World
getWorld (OK w _) = w

getRobot :: Result -> Robot
getRobot (OK _ r) = r

fromJust :: Maybe a -> a
fromJust (Just a) = a