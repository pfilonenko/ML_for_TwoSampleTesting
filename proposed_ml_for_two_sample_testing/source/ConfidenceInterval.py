# необходимые библиотеки
import math
import numpy as np
import pandas as pd
from scipy.stats import t

# объект исследования мощности критериев
class ConfidenceInterval:
    # процедура вычисления мощности критериев
    def computation(self, mas, confidence=0.95):
        # length of mas
        n = len(mas)

        # mean, var, std
        mean = np.mean(mas)
        var = np.var(mas) * n / (n-1)
        std = math.sqrt(var)

        # t-Student
        alpha = 1 - confidence
        p = 1 - alpha/2.
        tq = t.ppf(p, df=n-1)

        # range
        delta = tq * std / math.sqrt(n)

        return mean, delta

# точка входа
if __name__ == '__main__':
    #
    alpha = 0.99
    values = [1.0, 3.2, 1.6, 0.4, 0.12, 0.46]

    # посчитали пример
    pr = ConfidenceInterval()
    pr = pr.computation(mas=values, confidence=alpha)
    print(pr)
