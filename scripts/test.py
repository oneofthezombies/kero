import math

assert 1 + 2 == 3
assert 1 - 2 == -1
assert 1 * 2 == 2
assert 1 / 2 == 0.5
assert 1 + 2 * 3 == 7
assert (1 + 2) * 3 == 9
assert 1 + 2 / 3 == 1.6666666666666665
assert (1 + 2) / 3 == 1.0
assert -(2 + 5) * 16 == -112

assert math.isclose(1.1 + 2.2, 3.3)
assert math.isclose(1.1 - 2.2, -1.1)
assert math.isclose(1.1 - 2.2, -1.1)
assert math.isclose(1.1 * 2.2, 2.42)
assert math.isclose(1.1 / 2.2, 0.5)
assert math.isclose(1.1 / 2.2, 0.5)
assert math.isclose(1.1 + 2.2 * 3.3, 8.36)
assert math.isclose((1.1 + 2.2) * 3.3, 10.89)
assert math.isclose(1.1 + 2.2 / 3.3, 1.7666666666666668)
assert math.isclose((1.1 + 2.2) / 3.3, 1.0)
assert math.isclose(-(2.2 + 5.5) * 16.16, -124.432)
