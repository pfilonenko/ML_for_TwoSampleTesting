# необходимые библиотеки
import numpy as np
import pandas as pd

# объект исследования мощности критериев
class Power:
    # процедура вычисления мощности критериев
    def computation(self, GSH0, GSH1, type, alpha=0.05):
        # привели данные к нужному типу
        GSH0 = list(GSH0)
        GSH0 = pd.Series(GSH0)
        GSH1 = list(GSH1)
        GSH1 = pd.Series(GSH1)

        # отсортировали выборку
        GSH0 = GSH0.sort_values()

        # объемы выборок
        n0 = len(GSH0)
        n1 = len(GSH1)

        # обработали каждый вид критической области -- правая
        if type == 'right':
            num = int(n0 * (1.0 - alpha))
            x_r = GSH0.iloc[num]

            mask = GSH1 >= x_r
            sum = np.sum(mask)

            return 1.0 * sum / n1

        # критическая область -- левая
        elif type == 'left':
            num = int(n0 * alpha)
            x_l = GSH0.iloc[num]

            mask = GSH1 < x_l
            sum = np.sum(mask)

            return 1.0 * sum / n1

        # критическая область -- двойная
        elif type == 'double':
            alpha /= 2.0

            num = int(n0 * alpha)
            x_l = GSH0.iloc[num]

            num = int(n0 * (1 - alpha))
            x_r = GSH0.iloc[num]

            mask = (GSH1<x_l) | (GSH1>x_r)
            sum = np.sum(mask)

            return 1.0 * sum / n1
        else:
            raise Exception('Unknown type of Critial Area.')

# точка входа
if __name__ == '__main__':
    # создали распределения
    GSH0 = np.linspace(0, 1, 2000)
    GSH1 = np.linspace(0.25, 1.50, 2000)

    # посчитали пример
    pr = Power()
    pr = pr.computation(GSH0, GSH1, 'double', alpha=0.05)
    print(pr)
