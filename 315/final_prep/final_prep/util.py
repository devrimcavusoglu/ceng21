import time


def time_fn(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        res = func(*args, **kwargs)
        end = time.time()
        print(f"Time elapsed {start - end: .5f} s")
        return res
    return wrapper
