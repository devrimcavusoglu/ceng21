"""Implementation of Huffman Encoding"""
import queue
from dataclasses import dataclass
from typing import Dict

from final_prep.data_structures.tree import BinaryTree, TreeNode


@dataclass
class Char(object):
    name: str
    frequency: int

    def __lt__(self, other: "Char"):
        """For min-heap to use"""
        return self.frequency < other.frequency

    def __add__(self, other):
        freq = self.frequency + other.frequency
        name = self.name + " " + other.name
        return Char(name=name, frequency=freq)


def huffman(s: str):
    """
    Implementation of Huffman Coding.

    TODO:
        Generating codes from tree is not yet implemented, and it probably
        requires implementation of BinaryTree data structure (no ETA).

    Args:
        s: (str) Input string to be compressed.

    Returns:
        Tuple of compressed string representation of the input and the tree
        used for generating Huffman codes.
    """
    def generate_tree() -> TreeNode:
        alphabet = set(s)
        heap = queue.PriorityQueue(maxsize=len(alphabet))
        for character in alphabet:
            char = Char(name=character, frequency=s.count(character))
            node = TreeNode(char)
            heap.put(node)
        while not heap.empty():
            c1 = heap.get()
            c2 = heap.get()
            if not c1 or not c2:
                break
            p = BinaryTree.merge(c1, c2)
            heap.put(p)
        return p

    def generate_codes(node: TreeNode, codes: Dict[str, str]):
        return codes

    root = generate_tree()
    codes = {c: "" for c in set(s)}
    generate_codes(root, codes)

    compressed = s
    for char, code in codes.items():
        compressed = compressed.replace(char, code)
    return compressed, root


if __name__ == "__main__":
    # file_path = ""
    # with open(file_path, "r") as buffer:
    #     s = buffer.read()
    s = "wdbmakwnabwdnkawnbdkawnkdbaw"
    compressed, tree = huffman(s)
    print(compressed)
