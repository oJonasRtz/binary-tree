This is a study of how binary trees and red-black trees work.

# Binary tree

	doc - trees/bin_tree.c
	executable - trees/executables/bin_tree

	How to use:
	-No args
		$ ./bin_tree
		$ Too few arguments.
	-Using args
		$ ./bin_tree 30 43 1 15
		$ 1 15 30 43 

	Explanation:

	A binary tree works by adding new values at the curent position at the moment when we get it:

	Ex: First value
		num = 7;

		Node:
		    7
		   / \
		NULL NULL
		
	Ex: Second value
		if the value is less then the current node's value it goes to the left
			otherwise it goes to the right;
		
		num = 8;

		Node:
		    7
		   / \
		NULL  8
	
	Ex: more values
		This left/right rules applies to the subsequent nodes
		
		num = 20, 5, 2, 6;

		Node:
		    7
		   / \
		  5   8
		 / \   \
		2   6  20

	Other way to see it:

		2 - 5 - 6 - 7 - 8 - 20

# Red Black tree

Akita explanation: https://youtu.be/9GdesxWtOgs?si=d1kXPanv_OcezZTK&t=2148

	doc - trees/red_black_tree.c
	executable = trees/executables/red_black

