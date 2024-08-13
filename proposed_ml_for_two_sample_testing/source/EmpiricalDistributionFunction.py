# libs
import numpy as np
import pandas as pd

# ЭМПИРИЧЕСКАЯ ФУНКЦИЯ РАСПРЕДЕЛЕНИЯ'
class EmpiricalDistributionFunction:
    # training
    def processing(self, mas):
        # получили массив значений и отсортировали
        mas = list(mas)
        mas.sort()

        # определили частоту одного элемента выборки
        n = len(mas)
        p = 1.0 / n

        # сформировали структуру частот
        s = pd.DataFrame()
        s['x'] = mas
        s['y'] = p
        s = s.groupby('x').sum().sort_index()

        # сформировали значения оценки
        sum = 0
        prob = []
        for val in s['y']:
            sum += val
            prob.append(sum)
        s['y'] = prob

        # получлили окончательные значения Х и У
        self.x = list(s.index)
        self.y = list(s['y'])

    # QUANTILE
    def quantile(self, p):
        n = len(self.x)
        num = int(n * p)
        
        if num <= 0:
            return 0.0
        elif num >= len(self.x):
            return 1.0
        else:
            return self.x[num]

    # CDF
    def __call__(self, x):
        # https://tvims.nsu.ru/chernova/ms/lec/node4.html
        # если вне интервала, возвращаем 0
        if x <= self.x[0]:
            return 0.0

        # если вне интервала, возвращаем 1
        elif x > self.x[-1]:
            return 1.0

        # находим нужный интервал и считаем вероятность
        else:
            n = len(self.x)
            for i in range(n - 1):
                if self.x[i] < x <= self.x[i+1]:
                    return self.y[i]

    # Constructor
    def __init__(self, mas):
        self.fx = self.processing(mas)

# init pount
if __name__ == '__main__':
    # EDF training
    mas = [0.4, 2.6, 1.1, 3.2, 1.8, 1.8]
    F = EmpiricalDistributionFunction(mas)

    # making prediction
    x = 0.55
    print(x, F(x))
