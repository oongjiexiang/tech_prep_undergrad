# Problem
1. Height is not regulated. It depends on how keys are inserted. Suppose that the sequence of keys are supplied:
```
50 40 30 20 10
30 50 20 40 10
```
The BST for the former sequence does not look like a tree, but a linear sequence, one node connected to a smaller node. Searching takes $O(n)$ time But the tree for the second sequence is balanced, so searching takes $O(log(n))$ time