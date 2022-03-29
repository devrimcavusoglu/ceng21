"""Implementation of Heap Sort"""
from _heapq import _heapify_max
from typing import List


def swap(a: List, i: int, j: int):
    t = a[i]
    a[i] = a[j]
    a[j] = t


def left_child(i: int):
    return 2*i + 1


def bubble_down(a: List, start: int, end: int):
    root = start
    while left_child(root) <= end:
        child = left_child(root)
        swap_idx = root

        if a[swap_idx] < a[child]:
            swap_idx = child
        if child + 1 <= end and a[swap_idx] < a[child + 1]:
            swap_idx = child + 1
        if swap_idx == root:
            break
        else:
            swap(a, root, swap_idx)
            root = swap_idx


def heapsort(a: List[int]):
    """
    Implementation of heap-sort algorithm operating
    inplace on the given input array.

    URL: https://en.wikipedia.org/wiki/Heapsort

    - Worst-case: O(n*log(n))

    Args:
        a: (list) Input array to be sorted.

    Returns:
        Input array as sorted in ascending order.
    """
    n = len(a)
    _heapify_max(a)
    end = n - 1
    while end > 0:
        swap(a, end, 0)
        end -= 1
        # We need the following operation as the heap
        # property is ruined by the swap above.
        bubble_down(a, 0, end)

    return a


if __name__ == "__main__":
    import random
    random.seed(1)
    nums = list(range(50))
    ar = random.choices(nums, k=10)
    print(ar)
    res = heapsort(ar)
    print(res)
