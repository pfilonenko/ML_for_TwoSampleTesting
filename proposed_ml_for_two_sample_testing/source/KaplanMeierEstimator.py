# необходимые библиотеки
import numpy as np
import pandas as pd

# МНОЖИТЕЛЬНАЯ ОЦЕНКА КАПЛАНА-МЕЙЕРА (C=1 -- censored observation; C=0 -- complete observation)
class KaplanMeierEstimator:
    # ВЫЗОВ ПРЕДИКТА ОБУЧЕННОГО ОБЪЕКТА
    def __call__(self, t):
        # определили параметры для множительной оценки
        s = 1.0
        n = len(self.T)

        # обходим значения
        for j in range(n):
            t_val = self.T[j]
            c_val = self.C[j]

            if t <= t_val:
                degree = 1 - c_val
                s *= (n - j)/(n - j + 1)
                s = pow(s, degree)
            else:
                continue

        return s

    # КОНСТРУКТОР ОБЪЕКТА
    def __init__(self, T, C):
        #
        if len(T) == len(C):
            self.T = T
            self.C = C
        else:
            raise Exception('Length of T is not equal to length of C.')

# ТОЧКА ВХОДА
if __name__ == '__main__':
    # обучили Э.ф.р.
    T = [0.4, 2.6, 1.1, 3.2, 1.8, 1.8]
    C = [0, 0, 0, 0, 0, 0]
    S_KM = KaplanMeierEstimator(T, C)

    # сделали предсказание
    t = 3.20
    print(t, S_KM(t))
