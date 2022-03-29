import heapq
from typing import List


def swap(a: List, i: int, j: int):
    assert 0 <= i < len(a)
    assert 0 <= j < len(a)
    t = a[i]
    a[i] = a[j]
    a[j] = t


class BinaryHeap:
    def __init__(self, a: List = None):
        a = a or []
        self.heapify(a)
        self.array = a

    def __len__(self):
        return len(self.array)

    def __getitem__(self, idx: int):
        return self.array[idx]

    @staticmethod
    def is_leaf(a: List, i: int):
        if 2*i + 1 >= len(a):
            return True
        return False

    def get_parent(self, a: List, i: int):
        if i == 0:
            return -1
        return a[(i-1)//2]

    def get_left(self, a: List, i: int):
        if self.is_leaf(a, i):
            return -1
        return a[2*i + 1]

    def get_right(self, a: List, i: int):
        if self.is_leaf(a, i):
            return -1
        return a[2*i + 2]

    def bubble_down(self, a: List):
        pass

    def bubble_up(self, a: List, i: int):
        p_idx = (i-1)//2
        while p_idx >= 0:
            if a[p_idx] < a[i]:
                swap(a, i, p_idx)
            i = p_idx
            p_idx = (i-1)//2

    def heapify(self, a: List):
        i = len(a) - 1
        while i >= len(a)//2:
            if self.is_leaf(a, i):
                self.bubble_up(a, i)
            i -= 1
        return a

    def put(self, item: int):
        self.array.append(item)
        self.heapify(self.array)

    def get(self):
        n = len(self) - 1
        item = self.array.pop(n-1)
        self.array[0] = item
        self.bubble_down(a)
        return item


if __name__ == "__main__":
    heapq.heapify()
    a = [1, 4, 5, 3, 2, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16]
    print(a)
    heap = BinaryHeap(a)
    print(a)
