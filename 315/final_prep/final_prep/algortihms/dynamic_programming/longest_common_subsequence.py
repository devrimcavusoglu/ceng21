"""
Longest-Common Subsequence Problem

Problem definition: Given two iterable objects S_1 & S_2, we try
    to find the longest common subsequnce s.t C ∈ S_1 & C ∈ S_2.

Example:
    S_1 = "aabacba"
    S_2 = "baacab"
    LCS = "bacb" | "aaca" | "aacb"
"""
from typing import List

import numpy as np


def lcs_tabulation(s1: str, s2: str, out: List = None, cache=None):
    m = len(s1)
    n = len(s2)
    if cache is None:
        cache = np.zeros((m+1, n+1))

    for i in range(m):
        for j in range(n):
            is_match = s1[i] == s2[j]
            if is_match:
                cache[i+1, j+1] = cache[i, j] + 1
            else:
                cache[i+1, j+1] = max(cache[i+1, j], cache[i, j+1])

    return cache[m, n]


if __name__ == "__main__":
    import time

    S_1 = "aabacba"
    S_2 = "baacab"

    # print("Method: memoization")
    # start = time.time()
    # out = set()
    # res_mem = binary_knapsack_memoization(my_items, total_capacity, len(my_items)-1, out)
    # print(f"Time elapsed: {time.time() - start} s")
    # print("Result:", res_mem)
    # print("Out set: %r" % out)

    print("Method: recursive")
    start = time.time()
    out = []
    res_tab = lcs_tabulation(S_1, S_2, out)
    print(f"Time elapsed: {time.time() - start} s")
    print("Result:", res_tab)
    print("Out set: %r" % out)
