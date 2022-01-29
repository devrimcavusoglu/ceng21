"""
Implementation of the solution to the
Binary Knapsack Problem or 0-1 Knapsack Problem

TODO:
    The implementation currently is not complete and fails even
    including the items that exceeds the knapsack capacity.

# Problem description
    You are given a set of items I each of them has an associated weight
    and profit, and also a knapsack capacity M. The objective is to find
    the set of items achieving the maximum profit within the capacity M.

# Constraints:
    - The item weights are of type integer, profits are of type float.
    - Knapsack capacity is integer.
"""

from dataclasses import dataclass
from typing import List, Dict, Set

import numpy as np


@dataclass
class Item:
    name: str
    weight: int
    profit: float


def binary_knapsack(items: List[Item], m: int, n: int) -> float:
    """
    Naive recursive implementation of solution to the
    Binary Knapsack Problem.

    Args:
        items: List of items.
        m: Total knapsack capacity.
        n: nth item to be computed.

    Returns:
        Maximum profit.
    """
    if n == 0 or m == 0:
        return 0

    if items[n].weight > m:
        # If item's weight exceed the capacity m
        # this item can never be included, so skip.
        return binary_knapsack(items, m, n-1)

    # If the weight is less than the capacity, we
    # can reach the maximum profit either by including
    # the item or excluding it.
    p_item_included = items[n].profit + binary_knapsack(items, m-items[n].weight, n-1)
    p_item_excluded = binary_knapsack(items, m, n-1)
    return max(p_item_included, p_item_excluded)


def binary_knapsack_memoization(items: List[Item], m: int, n: int, out: Set = None, cache: Dict[int, int] = None) -> float:
    if cache is None:
        cache = - np.ones((n+1, m+1))

    if (n <= 0):
        return 0

    if cache[n, m] == -1:
        if items[n].weight > m:
            profit = binary_knapsack_memoization(items, m, n - 1, out, cache)
        else:
            p_item_included = items[n].profit + binary_knapsack_memoization(items, m - items[n].weight, n - 1, out, cache)
            p_item_excluded = binary_knapsack_memoization(items, m, n - 1, out, cache)
            if p_item_included > p_item_excluded:
                profit = p_item_included
                if out is not None:
                    out.add(items[n].name)
            else:
                profit = p_item_excluded
        cache[n, m] = profit

    return cache[n, m]


if __name__ == "__main__":
    import time

    total_capacity = 110
    my_items = [
        Item("A", weight=1, profit=11),
        Item("B", weight=11, profit=21),
        Item("C", weight=21, profit=31),
        Item("D", weight=23, profit=33),
        Item("E", weight=33, profit=43),
        Item("F", weight=43, profit=53),
        Item("G", weight=45, profit=55),
        Item("H", weight=55, profit=65),
    ]
    print(f"Total cap: {total_capacity} | Expected output: 55")

    print("Method: memoization")
    start = time.time()
    out = set()
    res_mem = binary_knapsack_memoization(my_items, total_capacity, len(my_items)-1, out)
    print(f"Time elapsed: {time.time() - start} s")
    print("Result:", res_mem)
    print("Out set: %r" % out)

    print("Method: recursive")
    start = time.time()
    res_rec = binary_knapsack(my_items, total_capacity, len(my_items)-1)
    print(f"Time elapsed: {time.time() - start} s")
    print("Result:", res_rec)
