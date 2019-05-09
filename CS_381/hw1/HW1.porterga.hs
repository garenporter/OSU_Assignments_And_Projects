-- Garen Porter - porterga - 932530483

module HW1 where


  -- | Integer-labeled binary trees.
  data Tree
     = Node Int Tree Tree   -- ^ Internal nodes
     | Leaf Int             -- ^ Leaf nodes
    deriving (Eq,Show)
  
  
  -- | An example binary tree, which will be used in tests.
  t1 :: Tree
  t1 = Node 1 (Node 2 (Node 3 (Leaf 4) (Leaf 5))
                      (Leaf 6))
              (Node 7 (Leaf 8) (Leaf 9))
  
  -- | Another example binary tree, used in tests.
  t2 :: Tree
  t2 = Node 6 (Node 2 (Leaf 1) (Node 4 (Leaf 3) (Leaf 5)))
              (Node 8 (Leaf 7) (Leaf 9))
  
  
  -- | The integer at the left-most node of a binary tree.
  --
  --   >>> leftmost (Leaf 3)
  --   3
  --
  --   >>> leftmost (Node 5 (Leaf 6) (Leaf 7))
  --   6
  --   
  --   >>> leftmost t1
  --   4
  --
  --   >>> leftmost t2
  --   1
  --
  leftmost :: Tree -> Int
  -- leftmost Empty = Nothing
  leftmost (Leaf x) = x
  leftmost (Node x l r) = leftmost l

  
  -- | The integer at the right-most node of a binary tree.
  --
  --   >>> rightmost (Leaf 3)
  --   3
  --
  --   >>> rightmost (Node 5 (Leaf 6) (Leaf 7))
  --   7
  --   
  --   >>> rightmost t1
  --   9
  --
  --   >>> rightmost t2
  --   9
  --
  rightmost :: Tree -> Int
  -- rightmost Empty = Nothing
  rightmost (Leaf x) = x
  rightmost (Node x l r) = rightmost r

  
  
  -- | Get the maximum integer from a binary tree.
  --
  --   >>> maxInt (Leaf 3)
  --   3
  --
  --   >>> maxInt (Node 5 (Leaf 4) (Leaf 2))
  --   5
  --
  --   >>> maxInt (Node 5 (Leaf 7) (Leaf 2))
  --   7
  --
  --   >>> maxInt t1
  --   9
  --
  --   >>> maxInt t2
  --   9
  --
  maxInt :: Tree -> Int
  -- maxInt Empty = Nothing
  maxInt (Leaf x) = x
  maxInt (Node x y z) = maximum [x , maxInt y, maxInt z]
  
  -- | Get the minimum integer from a binary tree.
  --
  --   >>> minInt (Leaf 3)
  --   3
  --
  --   >>> minInt (Node 2 (Leaf 5) (Leaf 4))
  --   2
  --
  --   >>> minInt (Node 5 (Leaf 4) (Leaf 7))
  --   4
  --
  --   >>> minInt t1
  --   1
  --
  --   >>> minInt t2
  --   1
  --
  minInt :: Tree -> Int
  -- minInt Empty = Nothing
  minInt (Leaf x) = x
  minInt (Node x y z) = minimum [x , minInt y, minInt z]
  
  
  -- | Get the sum of the integers in a binary tree.
  --
  --   >>> sumInts (Leaf 3)
  --   3
  --
  --   >>> sumInts (Node 2 (Leaf 5) (Leaf 4))
  --   11
  --
  --   >>> sumInts t1
  --   45
  --
  --   >>> sumInts (Node 10 t1 t2)
  --   100
  --
  sumInts :: Tree -> Int
  -- sumInts Empty = Nothing
  sumInts (Leaf x) = x
  sumInts (Node x y z) = sum [x , sumInts y , sumInts z]
  
  
  -- | The list of integers encountered by a pre-order traversal of the tree.
  --
  --   >>> preorder (Leaf 3)
  --   [3]
  --
  --   >>> preorder (Node 5 (Leaf 6) (Leaf 7))
  --   [5,6,7]
  --
  --   >>> preorder t1
  --   [1,2,3,4,5,6,7,8,9]
  --
  --   >>> preorder t2
  --   [6,2,1,4,3,5,8,7,9]
  --   
  preorder :: Tree -> [Int]
  -- preorder Empty = Nothing
  preorder (Leaf x) = x : []
  preorder (Node x y z) = x : preorder y ++ preorder z
  
  -- | The list of integers encountered by an in-order traversal of the tree.
  --
  --   >>> inorder (Leaf 3)
  --   [3]
  --
  --   >>> inorder (Node 5 (Leaf 6) (Leaf 7))
  --   [6,5,7]
  --
  --   >>> inorder t1
  --   [4,3,5,2,6,1,8,7,9]
  --
  --   >>> inorder t2
  --   [1,2,3,4,5,6,7,8,9]
  --   
  inorder :: Tree -> [Int]
  -- Inorder Empty = Nothing
  inorder (Leaf x) = [x]
  inorder (Node x y z) = inorder y ++ [x] ++ inorder z
  
  -- | Check whether a binary tree is a binary search tree.
  --
  --   >>> isBST (Leaf 3)
  --   True
  --
  --   >>> isBST (Node 5 (Leaf 6) (Leaf 7))
  --   False
  --   
  --   >>> isBST t1
  --   False
  --
  --   >>> isBST t2
  --   True
  --   
  isBST :: Tree -> Bool
  -- isBST Empty = Nothing
  isBST (Leaf x) = True
  isBST (Node x (Leaf y) (Leaf z)) = (x >= y) && (x <= z) && (y <= z)
  isBST (Node x (Leaf y) (Node z l r)) = (x >= y) && (x <= z) && (y <= z) && isBST l && isBST r
  isBST (Node x (Node y l r) (Leaf z)) = (x >= y) && (x <= z) && (y <= z) && isBST l && isBST r
  isBST (Node x (Node y l1 r1) (Node z l2 r2)) = (x >= y) && (x <= z) && (y <= z) && isBST l1 && isBST r2 && isBST l2 && isBST r2
  
  -- | Check whether a number is contained in a binary search tree.
  --   (You may assume that the given tree is a binary search tree.)
  --
  --   >>> inBST 2 (Node 5 (Leaf 2) (Leaf 7))
  --   True
  --
  --   >>> inBST 3 (Node 5 (Leaf 2) (Leaf 7))
  --   False
  --
  --   >>> inBST 4 t2
  --   True
  --
  --   >>> inBST 10 t2
  --   False
  --   
  inBST :: Int -> Tree -> Bool
  -- inBST Empty = Nothing
  inBST x (Leaf y) = x == y
  inBST x (Node y l r) 
    | x == y = True
    | x < y = inBST x l
    | x > y = inBST x r