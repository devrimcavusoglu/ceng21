

class TreeNode:
    def __init__(self, obj):
        self.obj = obj
        self._parent = None
        self._left = None
        self._right = None
        self.marked = False

    def __eq__(self, other):
        return self.obj == other.obj

    @property
    def parent(self):
        return self._parent

    @parent.setter
    def parent(self, other):
        if not isinstance(other, TreeNode):
            raise ValueError("Only instances of 'TreeNode' can be set as parent.")
        self._parent = other

    @property
    def left(self):
        return self._left

    @left.setter
    def left(self, other):
        if not isinstance(other, TreeNode):
            raise ValueError("Only instances of 'TreeNode' can be set as parent.")
        self._left = other
        other.parent = self

    @property
    def right(self):
        return self._right

    @right.setter
    def right(self, other):
        if not isinstance(other, TreeNode):
            raise ValueError("Only instances of 'TreeNode' can be set as parent.")
        self._right = other
        other.parent = self


class BinaryTree:
    def __init__(self):
        self._root = None

    @property
    def root(self):
        return self._root

    @staticmethod
    def is_leaf(node: TreeNode) -> bool:
        return node.left is None and node.right is None

    @staticmethod
    def merge(val1: object, val2: object) -> TreeNode:
        node1 = TreeNode(val1)
        node2 = TreeNode(val2)
        parent_val = val1 + val2
        parent = TreeNode(parent_val)
        parent.left = node1
        parent.right = node2
        return parent

    def add(self, val: object, parent: TreeNode):
        node = TreeNode(obj=val)
        if parent is None:
            self._root = node
        elif parent.left is None:
            parent.left = node
        elif parent.right is None:
            parent.right = node
        else:
            raise ValueError("'parent' node has two children already.")
