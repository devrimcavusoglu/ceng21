"""Fibonacci Implementations under Dynamic Programming"""
from typing import Dict


def fibonacci(n: int) -> int:
    """Returns the nth Fibonacci number"""
    if n == 1:
        return 0
    if n == 2:
        return 1
    return fibonacci(n-1) + fibonacci(n-2)


def fibonacci_memoization(n: int, cache: Dict[int, int] = None) -> int:
    if cache is None:
        cache = {}

    if not cache.get(n):
        if n == 1:
            num = 0
        elif n == 2:
            num = 1
        else:
            num = fibonacci_memoization(n-1, cache) + fibonacci_memoization(n-2, cache)
        cache[n] = num
    return cache[n]


def fibonacci_tabulation(n: int, cache: Dict[int, int] = None) -> int:
    if cache is None:
        cache = {1: 0, 2: 1}

    for i in range(3, n+1):
        cache[i] = cache[i-1] + cache[i-2]
    return cache[n]


if __name__ == "__main__":
    import time

    # 0 1 1 2 3 5
    n = 100
    print(f"Finding {n}th Fibonacci number..")

    print("Method: memoization")
    start = time.time()
    res_mem = fibonacci_memoization(n)
    print(f"Time elapsed: {time.time() - start} s")
    print("Result:", res_mem)

    print("Method: tabulation")
    start = time.time()
    res_tab = fibonacci_tabulation(n)
    print(f"Time elapsed: {time.time() - start} s")
    print("Result:", res_tab)

    print("Method: recursive")
    start = time.time()
    res_rec = fibonacci(n)
    print(f"Time elapsed: {time.time() - start} s")
    print("Result:", res_rec)

