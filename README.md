# MAST

The algorithm loads a set of n rooted trees in the NEWICK format e.g.:

((9,(1,(4,6,(2,7)))),2,(6,(3,4)));
(5, (3, (4,7)), (1, 6, (4, (1, 5,8))));

then for every pair of trees finds the minimum number of leaves that need to be removed to make those trees isomorphic. Known as the Maximum Agreement Subtree Problem.

Project made for the classes at University, written in C.
