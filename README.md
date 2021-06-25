
## Simulation of text-editor using Rope Data Structer<br />

This project is a simulation of a text editor that allows you to add text, delete, concatenate, search 
and return a character within a word. At the base of the implementation is a rope, a tree-based data
structure that is used in practice to store very long strings.

For download this project:
```
https://github.com/dinuionica/Text-Editor.git
```
For test you can use de checker :<br />
```
./checker
```
Implementation:

Dinu Ion Irinel:

Functions:

makeRopeNode
- within this function I allocated and created the node, I redirected
the two children, left and right, to NULL, I updated the node value and I
calculated the weight as the length of the string transmitted as a parameter

makeRopeTree
- during the function I created the new rope and updated its root

concat
- within the function we created a new root and a new rope, respectively
and then I tied the roots of the two strings transmitted as a parameter
as children of the newly created rope. In the end I calculated the new weight.


concat_nodes
- I proceeded similarly to the concat function only that the reasoning a
was applied for nodes

split
- within this function we created two nodes that represent references
to the two ropes to be created. Then I called a function
recursive, __split, which modifies these nodes, and I finally returned
the two pairs obtained which practically represent the roots of the ropes.

__split
- in this function we treated the case when the index is negative,
and if so, I concatenated the two nodes left and right. Otherwise
I copied the left side of the string into a temporary string, I created
a left node with it and a right node with the remaining part, and then I have
concatenated the two nodes. Finally I called the recursive function for
the two sons and I updated the weight.



insertion
- within the function I divided the string according to the index, I created
a new rope and I applied two successive concatenations with the first half and
then with the second half of the original string.


Serban Bianca-Sanziana:


Functions:

index_rope
- within this function I called a recursive function, __indexRope,
starting from the root of the rope

__indexRope
- within this function I recursively traversed the right subtree, respectively
the left subtree, and at the end I returned the index from the desired position

search
- within this function I allocated memory for the string, I initialized it
with the string terminator, and then as long as the desired interval is valid I
extracted one character at a time and added it to the resulting string

delete
- within this function I divided the string based on the start index,
I created a new rope with the right side obtained after the split,
I applied a new split according to len, and at the end I concatenated the first one
string obtained with the second and I returned the rope

We used the macro for memory allocation errors DIE taken from the utils.h header
