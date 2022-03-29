"""Implementation of Rabin-Karp algorithm"""
from typing import List


def fermat_prime(n: int):
    """Returns nth Fermat Prime."""
    return 2 ** (2 ** n) + 1


def hash_fn(s: str, base: int, mod: int):
    """
    Encodes the given string to a hash value using ASCII values
    for the characters.
    """
    if s == "":
        return 0
    hash_value = ord(s[-1]) + base * hash_fn(s[:-1], base, mod)
    if hash_value < 0:
        return hash_value + mod
    return hash_value % mod


class RollingHash:
    def __init__(self, text: str, window_size: int, initial_hash_value: int, mod_value: int = None,
                 hash_factor: int = None):
        self.text = text
        self.window_size = window_size
        self._shift = 0
        self._hash_value = initial_hash_value
        self._mod = mod_value or fermat_prime(4)
        self._hash_factor = hash_factor or window_size
        self._delete_factor = self._hash_factor ** (self.window_size-1)  # Precomputing deletion factor

    def get(self):
        return self._hash_value

    def get_span(self):
        return self.text[self._shift: self._shift + self.window_size]

    def get_shift(self):
        return self._shift

    def update(self):
        if self._shift >= len(self.text) - self.window_size:
            self._hash_value = None
        else:
            old_value = self.text[self._shift]
            new_value = self.text[self._shift + self.window_size]
            self.update_hash(old_value, new_value)
        self._shift += 1
        return self.get()

    def update_hash(self, old_value: str, new_value: str):
        self._hash_value = self._hash_value - self._delete_factor * ord(old_value) % self._mod
        self._hash_value = ord(new_value) + self._hash_factor * self._hash_value % self._mod
        if self._hash_value < 0:
            self._hash_value += self._mod
        else:
            self._hash_value %= self._mod


def rabin_karp(text: str, pattern: str, base: int = None, q: int = None) -> List[int]:
    """
    Implementation of Rabin-Karp algorithm to find matching strings
    in the text given the pattern. It uses rolling hash technique to
    keep the hashing operation time constant. You can see the
    algorithm and the pseudo-code in detail via the following URL.

    URL: https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm

    Worst-case:
        - O((n-m+1)m) assuming every shift has collision.
        - Practically speaking; O(n) if hashing is performed in O(1) time.
        - Practically speaking; O(mn) if hashing is performed in O(m) time.

    Args:
        text: (str) Input text to be searched.
        pattern: (str) Pattern to be searched in the text.
        base: (int) (default=None) Hash factor/Base for the hash values. By
            default, it will be set as 2.
        q: (int) (default=None) Mod value for the hash function. By default,
            it will be set as 4th Fermat's Prime.

    Returns:
        List of valid shifts.
    """
    # Preprocessing, we do case-insensitive matching
    # as both text and pattern are converted to lowercase.
    text = text.lower()
    pattern = pattern.lower()

    # Setting some default values used in hash function
    base = base or len(pattern)
    q = q or fermat_prime(4)

    # Computing required values
    pattern_hash = hash_fn(pattern, base, q)
    initial_hash_value = hash_fn(text[:len(pattern)], base, q)
    rolling_hash = RollingHash(text, len(pattern), initial_hash_value, mod_value=q, hash_factor=base)

    valid_shifts = []
    current_hash = rolling_hash.get()
    while current_hash:
        current_hash = rolling_hash.get()
        current_span = rolling_hash.get_span()
        if current_hash == pattern_hash:
            if current_span == pattern:
                # Only comparing if hash values are equal for pattern
                # and the current span is not sufficient due to hash
                # collision. If the hash values are equal we still need
                # to compare the strings themselves.
                valid_shifts.append(rolling_hash.get_shift())
        current_hash = rolling_hash.update()

    return valid_shifts


if __name__ == "__main__":
    text = "Some books are to be tasted, others to be swallowed, and some few to be chewed and digested."
    pattern = "some"
    valid_shifts = rabin_karp(text, pattern)

    expand_window = 5  # Used to expand the window for illustration purposes
    for shift in valid_shifts:
        start = shift if shift < expand_window else shift - expand_window
        end = shift + 2 * expand_window
        print(f"shift: {shift} | ...{text[start:end]}...")
