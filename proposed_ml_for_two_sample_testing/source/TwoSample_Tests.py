###################################################################################################
#  DISCLAIMER:
#  1) IMPLEMENTATIONS OF TWO-SAMPLE TESTS ARE EXACTLY THE SAME AS IN C++ AND HAVE BEEN PROVIDED
#     ONLY TO DEMONSTRATE THE END-TO-END PIPELINE OF THE PROPOSED ML-BASED METHODS.
#  2) THESE IMPLEMENTATIONS HAVE BEEN TRANSLATED FROM C++ TO PYTHON USING GPT-4o
#     AND SUCCESSFUL VALIDATED IN SEVERAL EXAMPLES.
#  3) ANYWAY WE STRONGLY RECOMMEND USING THE C++ IMPLEMENTATION OF THE TWO-SAMPLE TESTS.
###################################################################################################

# libs
import numpy as np
import pandas as pd
import scipy.stats as stats
from scipy.stats import norm
from KaplanMeierEstimator import *

# Right-Censored Sample object
class Sample:
    # constructor
    def __init__(self, first_param=None, second_param=None):
        # X,C
        if second_param != None:
            self.make_from_mas(first_param, second_param)
        # filename
        else:
            self.make_from_file(first_param)

    # make Sample from massives
    def make_from_mas(self, X, C):
        if len(X) == len(C):
            data = pd.DataFrame({'X': X, 'C': C}).sort_values(by='X', ascending=True)
            self.mas = data['X']
            self.C = data['C']
        else:
            raise 'Lengths of T and C are unequal.'

    # make Sample from the file
    def make_from_file(self, filename):
        with open(filename, 'r') as f:
            num = 0
            X = []
            C = []

            for line in f:
                # read text information about sample
                if num == 0:
                    info = line

                # read technical information about sample
                elif num == 1:
                    [mod, n] = str(line).split(' ')
                    mod = int(mod)
                    n = int(n)

                # read data of sample
                else:
                    if mod == 0:
                        x = int(line)
                        c = 0
                    elif mod == 1:
                        [x, c] = str(line).split(' ')
                        x = float(x)
                        c = int(c)
                    else:
                        raise 'Unexepected type MOD of the Sample'

                    # save values
                    X.append(x)
                    C.append(c)

                num += 1

        # make Sample
        self.Information = info
        self.mas = X
        self.C = C

        # special fields
        self.PracticeCensoredPercent = np.mean(self.C) * 100.
        self.isCensored = True if self.PracticeCensoredPercent > 0 else False

    # censoring rate
    def censoring_rate(self):
        cens_rate = np.mean(self.C) * 100
        return cens_rate

    # get size of Sample
    def N(self):
        return len(self.mas)

    # Sample is censored or not
    def IsCensored(self):
        return self.isCensored

    # sort the sample - get a variation series
    def SortSample(self):
        df = pd.DataFrame()
        df['X'] = self.mas
        df['C'] = self.C
        df.sort_values(by=['X', 'C'], ascending=(True, True), inplace=True)

        self.mas = list(df['X'])
        self.C = list(df['C'])

    # direct-return of MAS-element
    def _X(self, i):
        if i < len(self.mas):
            return self.mas[i]
        else:
            return np.inf

    # direct-return of C-element
    def _C(self, i):
        if i < len(self.C):
            return self.C[i]
        else:
            return np.inf

# Abstract class for tw-sample tests
class TwoSample_Test:
    # returns p-value for the test statistic Sn
    def p_value(self, Sn):
        critical_area = self.critical_area_type()
        if critical_area == 'left':
            val = self.F(Sn)
        elif critical_area == 'right':
            val = 1 - self.F(Sn)
        elif critical_area == 'double':
            val = 2*min( self.F(Sn), 1 - self.F(Sn) )
        else:
            raise 'Unknown type of critical area.'

        return val

    # getting the test name
    def get_test_name(self):
        return self.test_name

# Generalized Peto Wilcoxon test
class GeneralizedPeto_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'Peto'

    class Point:
        def __init__(self, M=0.0, C=0, V=0, rang=0):
            self.M = M  # значение
            self.C = C  # флаг, сведённый ли элемент
            self.V = V  # принадлежность 1-й или 2-й выборке (0 или 1)
            self.rang = rang  # rank

        def __lt__(self, other):
            if self.M == other.M:
                return self.C < other.C
            return self.M < other.M

    def kaplan_meyer_estimate(self, T, k):
        res = 1.0
        for i in range(k):
            if T[i].C == 0:
                res *= (len(T) - (i + 1)) / (len(T) - (i + 1) + 1)
        return res

    def statistic(self, A, B):
        A.SortSample()
        B.SortSample()

        T = []
        for i in range(A.N()):
            T.append(self.Point(M=A._X(i), C=A._C(i), V=0))

        for i in range(B.N()):
            T.append(self.Point(M=B._X(i), C=B._C(i), V=1))

        T.sort()

        S = 1.0
        SU = [(0.0, 0.0) for _ in range(len(T))]

        for i in range(len(T)):
            if T[i].C == 0:
                first = self.kaplan_meyer_estimate(T, i + 1)
                second = S + first - 1
                SU[i] = (first, second)
                S = SU[i][0]
            else:
                SU[i] = (-1.0, S - 1.0)

        W = sum(SU[i][1] for i in range(len(T)) if T[i].V == 0)
        VarW = sum(pow(SU[i][1], 2) for i in range(len(T)))

        VarW *= (A.N() * B.N()) / ((A.N() + B.N()) * (A.N() + B.N() - 1))

        Sn = W / (VarW ** 0.5)

        return Sn

    def F(self, Sn):
        cdf_value = stats.norm.cdf(Sn)
        return cdf_value

    def critical_area_type(self):
        return 'double'

# Generalized Gehan Wilcoxon test
class GeneralizedGehan_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'Gehan'

    class Point:
        def __init__(self, M=0.0, C=0, V=0):
            self.M = M  # значение
            self.C = C  # флаг, сведён ли элемент
            self.V = V  # принадлежность 1-й или 2-й выборке (0 или 1)
            self.rang = 0  # ранг (используется в вычислениях)

        def __lt__(self, other):
            if self.M == other.M:
                return self.C < other.C
            return self.M < other.M

    def step1(self, T):
        r = 1
        for point in T:
            if point.C == 0:
                point.rang = r
                r += 1

    def step2(self, T):
        r = 0
        for point in T:
            if point.C == 0:
                r = point.rang + 1
            else:
                point.rang = r

    def step3(self, T):
        for i in range(1, len(T)):
            if abs(T[i].M - T[i - 1].M) < np.finfo(float).eps and T[i].C == T[i - 1].C:
                T[i].rang = T[i - 1].rang

    def step4(self, T, R1):
        for i in range(len(R1)):
            R1[i] = T[i].rang

    def step5(self, T):
        for i in range(len(T)):
            T[i].rang = len(T) - i

    def step6(self, T):
        for i in range(len(T) - 1):
            j = i + 1
            while j < len(T) and T[i].M == T[j].M and T[i].C == T[j].C:
                j += 1
            for k in range(i, j):
                T[k].rang = T[j - 1].rang

    def step7(self, T):
        for point in T:
            if point.C == 1:
                point.rang = 1

    def step8(self, T, R1):
        for i in range(len(T)):
            T[i].rang = R1[i] - T[i].rang

    def statistic(self, A, B):
        A.SortSample()
        B.SortSample()

        T = [self.Point() for _ in range(A.N() + B.N())]
        R1 = [0] * len(T)

        for i in range(A.N()):
            T[i].M = A._X(i)
            T[i].C = A._C(i)
            T[i].V = 0

        for i in range(A.N(), len(T)):
            j = i - A.N()
            T[i].M = B._X(j)
            T[i].C = B._C(j)
            T[i].V = 1

        T.sort()

        # Вычисление R1i
        self.step1(T)
        self.step2(T)
        self.step3(T)
        self.step4(T, R1)

        # Вычисление R2i
        self.step5(T)
        self.step6(T)
        self.step7(T)
        self.step8(T, R1)

        W = sum(point.rang for point in T if point.V == 0)
        VarW = sum(point.rang ** 2 for point in T)

        VarW *= (A.N() * B.N()) / ((A.N() + B.N()) * (A.N() + B.N() - 1))

        Sn = W / (VarW ** 0.5)

        return Sn

    def F(self, Sn):
        cdf_value = stats.norm.cdf(Sn)
        return cdf_value

    def critical_area_type(self):
        return 'double'

# log-rank
class Logrank_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'logrank'

    class Point:
        def __init__(self):
            self.T = 0.0  # значение времени
            self.C = 0.0  # флаг цензурирования
            self.M = 0.0  # счетчик
            self.r = 0.0  # ранг
            self.V = 0  # принадлежность 1-й или 2-й выборке (0 или 1)

        def __lt__(self, other):
            if self.T == other.T:
                return self.C < other.C
            return self.T < other.T

    def exists(self, t, T):
        for i, point in enumerate(T):
            if abs(point.T - t) <= np.finfo(float).eps:
                return i
        return -1

    def calc(self, XX, n1, n2):
        TEST = 0.0
        n = n1 + n2
        Lg = 0.0
        summ = 0.0
        sume = 0.0
        last_e = 0.0
        vars = 0.0

        for point in XX:
            if point.C == 0:
                point.r = n - summ
                sume += point.M / point.r
                last_e = sume

                if point.V == 2:
                    Lg += (1.0 - sume) * point.M
                vars += (1.0 - sume) ** 2 * point.M

                TEST += (1.0 - sume) * point.M
            else:
                if point.V == 2:
                    Lg += -last_e
                vars += (-last_e) ** 2

                TEST += -last_e
            summ += point.M

        vars *= n1 * n2 / (n * (n - 1))
        Sn = Lg / np.sqrt(vars)

        return Sn

    def statistic(self, A, B):
        XX = []

        for i in range(A.N()):
            temp = A._X(i)
            k = self.exists(temp, XX)
            if k != -1 and XX[k].C == 0:
                XX[k].M += 1
            else:
                P = self.Point()
                P.T = temp
                P.C = A._C(i)
                P.M = 1
                P.V = 1
                XX.append(P)

        for i in range(B.N()):
            temp = B._X(i)
            k = self.exists(temp, XX)
            if k != -1 and XX[k].C == 0:
                XX[k].M += 1
                XX[k].V = 2
            else:
                P = self.Point()
                P.T = temp
                P.C = B._C(i)
                P.M = 1
                P.V = 2
                XX.append(P)

        XX.sort()
        return self.calc(XX, A.N(), B.N())

    def F(self, Sn):
        cdf_value = stats.norm.cdf(Sn)
        return cdf_value

    def critical_area_type(self):
        return 'double'

# Bagdonavicius-Nikulin Generalized PH-model Test
class BN_GPH_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'BN_GPH'

    class MDTStruct:
        def __init__(self, x, v):
            self.X = x  # значение
            self.V = v  # принадлежность к выборке

        def __lt__(self, other):
            return self.X < other.X

    def Y(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) >= t)

    def N(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) <= t and C._C(i) == 0)

    def calc(self, A, B, XX, DBL_EPS_MD):
        u1 = u2 = E11 = E12 = E22 = 0.0
        y1 = A.N()
        y2 = B.N()

        lam1_last = lam1_new = lam2_last = lam2_new = 0.0
        n1_last = n1_new = n2_last = n2_new = 0.0
        lambda_last = lambda_new = 0.0

        for point in XX:
            n1_new = self.N(1, point.X + DBL_EPS_MD, A, B)
            n2_new = self.N(2, point.X + DBL_EPS_MD, A, B)

            lambda_new = lambda_last + (n1_new + n2_new - (n1_last + n2_last)) / (y1 + y2)

            lam1_new = lam1_last + (n1_new - n1_last) / y1 if abs(y1) > np.finfo(float).eps else lam1_last + 0.0
            lam2_new = lam2_last + (n2_new - n2_last) / y2 if abs(y2) > np.finfo(float).eps else lam2_last + 0.0

            a1 = y1 * y2 / (y1 + y2)
            a2 = (lam2_new - lam1_new) - (lam2_last - lam1_last)
            a3 = np.log(1 + lambda_last)
            a4 = (n1_new + n2_new) - (n1_last + n2_last)

            u1 += a1 * a2
            u2 -= a1 * a3 * a2

            E11 += a1 / (y1 + y2) * a4
            E12 -= a1 / (y1 + y2) * a3 * a4
            E22 += a1 / (y1 + y2) * (a3 ** 2) * a4

            lam1_last, lam2_last = lam1_new, lam2_new
            n1_last, n2_last = n1_new, n2_new

            y1 -= 1 if point.V == 1 else 0
            y2 -= 0 if point.V == 1 else 1

            lambda_last = lambda_new

        det = E11 * E22 - E12 * E12
        A11 = E22 / det
        A12 = -E12 / det
        A22 = E11 / det

        t1 = u1 * A11 + u2 * A12
        t2 = u1 * A12 + u2 * A22

        Sn = t1 * u1 + t2 * u2

        return Sn

    def statistic(self, A, B):
        XX = []
        DBL_EPS_MD = 1e-13

        for i in range(A.N()):
            XX.append(self.MDTStruct(A._X(i), 1))

        for i in range(B.N()):
            XX.append(self.MDTStruct(B._X(i), 2))

        XX.sort()

        return self.calc(A, B, XX, DBL_EPS_MD)

    def F(self, Sn):
        cdf_value = stats.chi2.cdf(Sn, df=2)
        return cdf_value

    def critical_area_type(self):
        return 'right'

# Bagdonavicius-Nikulin Multi Cross-Effect-model Test
class BN_MCE_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'BN_MCE'

    class MDTStruct:
        def __init__(self, x, v):
            self.X = x  # значение
            self.V = v  # принадлежность к выборке

        def __lt__(self, other):
            return self.X < other.X

    def Y(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) >= t)

    def N(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) <= t and C._C(i) == 0)

    def calc(self, A, B, XX, DBL_EPS_MD):
        u1 = u2 = u3 = 0.0
        E11 = E12 = E22 = E23 = E33 = 0.0

        y1 = A.N()
        y2 = B.N()
        lam1_last = lam1_new = lam2_last = lam2_new = 0.0
        n1_new = n1_last = n2_new = n2_last = 0.0
        lambda_new = lambda_last = 0.0

        for point in XX:
            n1_new = self.N(1, point.X + DBL_EPS_MD, A, B)
            n2_new = self.N(2, point.X + DBL_EPS_MD, A, B)

            lambda_new = lambda_last + (n1_new + n2_new - (n1_last + n2_last)) / (y1 + y2)

            lam1_new = lam1_last + (n1_new - n1_last) / y1 if abs(y1) > np.finfo(float).eps else lam1_last + 1.0
            lam2_new = lam2_last + (n2_new - n2_last) / y2 if abs(y2) > np.finfo(float).eps else lam2_last + 1.0

            a1 = y1 * y2 / (y1 + y2)
            a2 = (lam2_new - lam1_new) - (lam2_last - lam1_last)
            a3 = lambda_last
            a4 = (n1_new + n2_new) - (n1_last + n2_last)

            u1 += a1 * a2
            u2 += a1 * a3 * a2
            u3 += a1 * (a3 ** 2) * a2

            E11 += a1 / (y1 + y2) * a4
            E12 += a1 / (y1 + y2) * a3 * a4
            E22 += a1 / (y1 + y2) * (a3 ** 2) * a4
            E23 += a1 / (y1 + y2) * (a3 ** 3) * a4
            E33 += a1 / (y1 + y2) * (a3 ** 4) * a4

            # Обновление переменных
            lam1_last, lam2_last = lam1_new, lam2_new
            n1_last, n2_last = n1_new, n2_new
            lambda_last = lambda_new

            if point.V == 1:
                y1 -= 1
            else:
                y2 -= 1

        # Вычисление матрицы S
        E21 = E12
        E13 = E31 = E22
        E32 = E23

        det = (E31 * E12 * E23 - E31 * E13 * E22 -
               E21 * E12 * E33 + E21 * E13 * E32 +
               E11 * E22 * E33 - E11 * E23 * E32)

        S = np.zeros((3, 3))
        S[0][0] = (E22 * E33 - E23 * E32) / det
        S[0][1] = (-E12 * E33 + E13 * E32) / det
        S[0][2] = (E12 * E23 - E13 * E22) / det
        S[1][0] = (E31 * E23 - E21 * E33) / det
        S[1][1] = (-E31 * E13 + E11 * E33) / det
        S[1][2] = (E21 * E13 - E11 * E23) / det
        S[2][0] = (-E31 * E22 + E21 * E32) / det
        S[2][1] = (E31 * E12 - E11 * E32) / det
        S[2][2] = (-E21 * E12 + E11 * E22) / det

        Sn = (S[0][0] * u1 ** 2 + S[1][1] * u2 ** 2 +
              S[2][2] * u3 ** 2 + 2 * S[0][1] * u1 * u2 +
              2 * S[0][2] * u1 * u3 + 2 * S[1][2] * u2 * u3)

        return Sn

    def statistic(self, A, B):
        XX = []
        DBL_EPS_MD = 1e-13

        for i in range(A.N()):
            XX.append(self.MDTStruct(A._X(i), 1))

        for i in range(B.N()):
            XX.append(self.MDTStruct(B._X(i), 2))

        XX.sort()

        return self.calc(A, B, XX, DBL_EPS_MD)

    def F(self, Sn):
        cdf_value = stats.chi2.cdf(Sn, df=3)
        return cdf_value

    def critical_area_type(self):
        return 'right'

# Bagdonavicius-Nikulin Single Cross-Effect-model Test
class BN_SCE_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'BN_SCE'

    class MDTStruct:
        def __init__(self, x, c, v):
            self.X = x  # значение
            self.C = c  # принадлежность к выборке
            self.V = v  # тип выборки (1 или 2)

        def __lt__(self, other):
            return self.X < other.X

    def Y(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) >= t)

    def N(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) <= t and C._C(i) == 0)

    def K(self, num, expL, n):
        if num == 1:
            return expL / np.sqrt(float(n))
        else:
            return (expL - 1.0) / np.sqrt(float(n))

    def calc(self, A, B, XX, DBL_EPS_MD):
        u1 = u2 = E11 = E12 = E22 = 0.0
        y1 = A.N()
        y2 = B.N()
        lam1_last = lam1_new = lam2_last = lam2_new = 0.0
        n1_new = n1_last = n2_new = n2_last = lambda_new = lambda_last = 0.0

        for point in XX:
            n1_new = self.N(1, point.X + DBL_EPS_MD, A, B)
            n2_new = self.N(2, point.X + DBL_EPS_MD, A, B)

            lambda_new = lambda_last + (n1_new + n2_new - (n1_last + n2_last)) / (y1 + y2)

            if abs(n1_new - n1_last) <= np.finfo(float).eps and abs(y1) <= np.finfo(float).eps:
                lam1_new = lam1_last + 1.0
            else:
                lam1_new = lam1_last + (n1_new - n1_last) / y1 if abs(y1) > np.finfo(float).eps else lam1_last

            if abs(n2_new - n2_last) <= np.finfo(float).eps and abs(y2) <= np.finfo(float).eps:
                lam2_new = lam2_last + 1.0
            else:
                lam2_new = lam2_last + (n2_new - n2_last) / y2 if abs(y2) > np.finfo(float).eps else lam2_last

            a1 = y1 * y2 / (y1 + y2)
            a2 = (lam2_new - lam1_new) - (lam2_last - lam1_last)

            K1 = self.K(1, np.exp(-lambda_last), len(XX))
            K2 = self.K(2, np.exp(-lambda_last), len(XX))

            u1 += a1 * a2 * K1
            u2 += a1 * a2 * K2

            E11 += (1.0 - point.C) * K1 * K1 * a1 / (y1 + y2)
            E12 += (1.0 - point.C) * K1 * K2 * a1 / (y1 + y2)
            E22 += (1.0 - point.C) * K2 * K2 * a1 / (y1 + y2)

            # Обновление переменных
            lam1_last, lam2_last = lam1_new, lam2_new
            n1_last, n2_last = n1_new, n2_new

            if point.V == 1:
                y1 -= 1
            else:
                y2 -= 1

            lambda_last = lambda_new

        det = E11 * E22 - E12 * E12
        A11 = E22 / det
        A12 = -E12 / det
        A22 = E11 / det

        t1 = u1 * A11 + u2 * A12
        t2 = u1 * A12 + u2 * A22

        Sn = t1 * u1 + t2 * u2

        return Sn

    def statistic(self, A, B):
        XX = []
        DBL_EPS_MD = 1e-13

        for i in range(A.N()):
            XX.append(self.MDTStruct(A._X(i), A._C(i), 1))

        for i in range(B.N()):
            XX.append(self.MDTStruct(B._X(i), B._C(i), 2))

        XX.sort()

        return self.calc(A, B, XX, DBL_EPS_MD)

    def F(self, Sn):
        cdf_value = stats.chi2.cdf(Sn, df=2)
        return cdf_value

    def critical_area_type(self):
        return 'right'

# Q-test
class Q_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'Qtest'

        self.kaplan_meyer = True
        self.sample_size_a = -1
        self.sample_size_b = -1
        self.sn = None

    def set_survival_estimator(self, set_kaplan_meyer):
        self.kaplan_meyer = set_kaplan_meyer

    def statistic(self, A, B):
        A.SortSample()
        B.SortSample()
        self.sample_size_a = A.N()
        self.sample_size_b = B.N()

        S1 = KaplanMeierEstimator(A.mas, A.C)
        S2 = KaplanMeierEstimator(B.mas, B.C)

        x1 = S1.Quantile(0.6)
        x2 = S1.Quantile(0.2)

        Q = abs(S2(x1) - S1(x1)) - abs(S2(x2) - S1(x2))

        if Q < 0:
            # If Q < 0, then use logrank test
            lg = Logrank_Test()
            sn = lg.statistic(A, B)
        else:
            # Otherwise, use Wilcoxon test
            p = GeneralizedPeto_Test()
            sn = p.statistic(A, B)

        return sn

    def F(self, x):
        '''must be simulated by the Monte Carlo method'''
        return 0.0

    def critical_area_type(self):
        return 'double'

# Maximum Value Test
class MAX_Value_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'MAX'
        self.SampleSizeA = -1
        self.SampleSizeB = -1

    def F0(self, x):
        return norm.cdf(x) - norm.cdf(0.0)

    def phi(self, x):
        return np.exp(-x * x / 2.0) / np.sqrt(2.0 * np.pi)

    def func(self, x):
        if x < 0.0:
            return 0.0

        r = np.sqrt(3.0) / 2.0  # Константа
        if abs(r) == 1.0:
            return 2.0 * self.phi(x)
        elif r == 0.0:
            return 8.0 * self.phi(x) * self.F0(x)
        else:
            return (4 * self.phi(x) *
                    (self.F0(x * np.sqrt((1.0 - r) / (1.0 + r))) +
                     self.F0(x * np.sqrt((1.0 + r) / (1.0 - r)))))

    def Gauss4(self, e, f):
        xj = np.zeros(4)
        q = np.zeros(4)

        # Points
        xj[0] = np.sqrt((3.0 - 2.0 * np.sqrt(6.0 / 5.0)) / 7.0)
        xj[1] = np.sqrt((3.0 + 2.0 * np.sqrt(6.0 / 5.0)) / 7.0)
        xj[2] = -xj[1]
        xj[3] = -xj[0]

        # Weights
        q[0] = (18 + np.sqrt(30.0)) / 36.0
        q[1] = (18 - np.sqrt(30.0)) / 36.0
        q[2] = q[1]
        q[3] = q[0]

        summ = 0
        s = 0

        for k in range(4):
            theta = (e + f + xj[k] * (f - e)) / 2.0
            s += q[k] * self.func(theta)

        summ += s * (f - e) / 2.0

        return summ

    def statistic(self, A, B):
        A.SortSample()
        B.SortSample()
        self.SampleSizeA = A.N()
        self.SampleSizeB = B.N()

        T1 = Logrank_Test()
        T2 = GeneralizedGehan_Test()

        S1 = abs(T1.statistic(A, B))
        S2 = abs(T2.statistic(A, B))

        Sn = max(S1, S2)

        return Sn

    def F(self, x):
        h = 0.05
        res = 0.0
        a = 0
        b = a + h
        P = True

        while P:
            if b > x:
                b = x
                P = False

            res += self.Gauss4(a, b)

            a = b
            b += h

        return min(res, 1.0)

    def critical_area_type(self):
        return 'right'

# MIN3-test
class MIN3_Test(TwoSample_Test):
    def __init__(self, p=None):
        self.test_name = 'MIN3'

        self.a1 = 1.0
        self.a2 = 1.0
        self.a3 = 1.0
        self.GSH0 = None

        if p is not None:
            self.a1 = p[0]
            self.a2 = p[1]
            self.a3 = p[2]

        # Пример кода для генерации случайных выборок (закомментирован):
        # N = 30000
        # Sn = np.zeros(N)
        # for i in range(N):
        #     A = Sample(CRVExponential(0, 1), 100, GwMT19937[i % num_threads])
        #     B = Sample(CRVExponential(0, 1), 100, GwMT19937[i % num_threads])
        #     Sn[i] = self.CalculateStatistic(A, B)
        # self.GSH0 = EDF(Sn)

    def statistic(self, A, B):
        T1 = WeightedKaplanMeier_Test()
        T2 = BN_MCE_Test()
        T3 = BN_SCE_Test()

        S1 = T1.statistic(A, B)
        S2 = T2.statistic(A, B)
        S3 = T3.statistic(A, B)

        pv1 = 2 * min(T1.F(S1), 1 - T1.F(S1))
        pv2 = 1.0 - T2.F(S2)
        pv3 = 1.0 - T3.F(S3)

        Sn1 = self.a1 * pv1
        Sn2 = self.a2 * pv2
        Sn3 = self.a3 * pv3

        return min(Sn1, Sn2, Sn3)

    def F(self, x):
        '''must be simulated by the Monte Carlo method'''
        return 0.0

    def critical_area_type(self):
        return 'left'

# Weighted log-rank tests (TaroneWare, PetoPrentice, Prentice)
class WeightedLogrank_Test(TwoSample_Test):
    def __init__(self, test_name):
        self.test_name = 'WLg_' + test_name
        if test_name == 'Prentice':
            self.sel = 5
        elif test_name == 'PetoPrentice':
            self.sel = 4
        elif test_name == 'Breslow':
            self.sel = 3
        elif test_name == 'TaroneWare':
            self.sel = 2
        else:
            self.sel = 1    # 'logrank'

    def k(self, Y, n, Sm):
        if self.sel == 1:
            return 1.0 / np.sqrt(n)  # logrank
        elif self.sel == 2:
            return np.sqrt(Y) / n  # TaroneWare
        elif self.sel == 3:
            return Y / (n ** (3.0 / 2.0))  # Breslow
        elif self.sel == 4:
            return Sm / np.sqrt(n)  # PetoPrentice
        elif self.sel == 5:
            return Sm * Y / (np.sqrt(n) * (Y + 1))  # Prentice

    def y(self, num, t, A, B):
        C = A if num == 1 else B
        return sum(1 for i in range(C.N()) if C._X(i) >= t)

    def statistic(self, A, B):
        A.SortSample()
        B.SortSample()

        KMA = KaplanMeierEstimator(A.mas, A.C)
        V = Sigma = 0.0

        DBL_EPSILON = np.finfo(float).eps
        for i in range(A.N()):
            X = A._X(i)
            y1 = self.y(1, X, A, B)
            y2 = self.y(2, X, A, B)
            Kx = self.k(y1 + y2, A.N() + B.N(), 1.0 - KMA(X - DBL_EPSILON))

            V += (1.0 - A._C(i)) * Kx * y2 / (y1 + y2)
            Sigma += (1.0 - A._C(i)) * Kx**2 * y1 * y2 / (y1 + y2)**2

        for i in range(B.N()):
            X = B._X(i)
            y1 = self.y(1, X, A, B)
            y2 = self.y(2, X, A, B)
            Kx = self.k(y1 + y2, A.N() + B.N(), 1.0 - KMA(X - DBL_EPSILON))

            V -= (1.0 - B._C(i)) * Kx * y1 / (y1 + y2)
            Sigma += (1.0 - B._C(i)) * Kx**2 * y1 * y2 / (y1 + y2)**2

        if abs(V) <= DBL_EPSILON and abs(Sigma) <= DBL_EPSILON:
            return 1.0
        else:
            return V**2 / Sigma

    def F(self, Sn):
        cdf_value = stats.chi2.cdf(Sn, df=1)
        return cdf_value

    def critical_area_type(self):
        return 'right'

# Weighted Kaplan-Meier test
class WeightedKaplanMeier_Test(TwoSample_Test):
    def __init__(self):
        self.test_name = 'WeightedKM'
        self.DBL_EPS = 1.0e-10

    class sKM:
        def __init__(self, X, C, v):
            self.X = X
            self.C = C
            self.v = v

        def __lt__(self, other):
            if self.X == other.X:
                return self.C < other.C
            return self.X < other.X

    def calc(self, S1, C1, S2, C2, S, XX):
        KS1 = KaplanMeierEstimator(S1.mas, S1.C)
        KS2 = KaplanMeierEstimator(S2.mas, S2.C)
        KC1 = KaplanMeierEstimator(C1.mas, C1.C)
        KC2 = KaplanMeierEstimator(C2.mas, C2.C)
        KS = KaplanMeierEstimator(S.mas, S.C)

        n1 = S1.N()
        n2 = S2.N()
        V = 0.0
        Sig = 0.0
        sum_w_s = 0.0

        DBL_EPSILON = 1.0e-10
        for i in range(len(XX) - 1, -1, -1):
            t = XX[i].X
            c1 = KC1(t - self.DBL_EPS)
            c2 = KC2(t - self.DBL_EPS)
            s = KS(t)
            smin = KS(t - self.DBL_EPS)

            w = 1.0 if abs(c1) <= DBL_EPSILON and abs(c2) <= DBL_EPSILON else ((n1+n2)*c1*c2 )/(n1 * c1 + n2 * c2)

            V += w * (KS2(t) - KS1(t))

            temp = 0.0 if abs(w) <= DBL_EPSILON or abs(s) <= DBL_EPSILON or abs(smin) <= DBL_EPSILON else (s - smin) / (s * smin)
            sum_w_s += w * s
            Sig -= sum_w_s * sum_w_s * temp

        V *= np.sqrt((S1.N() * S2.N()) / (S1.N() + S2.N()))
        Sn = V / np.sqrt(Sig)

        return Sn

    def statistic(self, A, B):
        A.SortSample()
        B.SortSample()

        XX = []
        m1, m2, m, c1, c2, c = [], [], [], [], [], []

        for i in range(A.N()):
            m1.append(A._X(i))
            c1.append(1 - A._C(i))
            m.append(A._X(i))
            c.append(A._C(i))

            Temp = self.sKM(0, 0, 0)
            Temp.X = A._X(i)
            Temp.C = A._C(i)
            Temp.v = 1
            XX.append(Temp)

        for i in range(B.N()):
            m2.append(B._X(i))
            c2.append(1 - B._C(i))
            m.append(B._X(i))
            c.append(B._C(i))

            Temp = self.sKM(0, 0, 0)
            Temp.X = B._X(i)
            Temp.C = B._C(i)
            Temp.v = 2
            XX.append(Temp)

        XX.sort()

        # Создание выборок C1 и C2
        C1 = Sample(m1, c1)
        C2 = Sample(m2, c2)
        S = Sample(m, c)
        S.SortSample()

        return self.calc(A, C1, B, C2, S, XX)

    def F(self, Sn):
        cdf_value = stats.norm.cdf(Sn)
        return cdf_value

    def critical_area_type(self):
        return 'double'

# initial point
if __name__ == '__main__':
    # Samples from files
    EX_NUM = 1
    if EX_NUM == 1:
        # EXAMPLE: doi:10.1002/0471458546 , p.109
        A = Sample('./samples/CMF(group1).txt')
        B = Sample('./samples/Control(group2).txt')
    else:
        A = Sample('./samples/1Chemotherapy.txt')
        B = Sample('./samples/2Radiotherapy.txt')

    # tests
    tests = [
        GeneralizedPeto_Test(),
        GeneralizedGehan_Test(),
        Logrank_Test(),
        BN_GPH_Test(),
        BN_MCE_Test(),
        BN_SCE_Test(),
        Q_Test(),
        MAX_Value_Test(),
        MIN3_Test(),
        WeightedLogrank_Test('TaroneWare'),
        WeightedLogrank_Test('PetoPrentice'),
        WeightedLogrank_Test('Prentice'),
        WeightedKaplanMeier_Test()
    ]

    # two-sample testing
    stat = []
    for test in tests:
        name = test.get_test_name()
        Sn = test.statistic(A, B)
        pv = test.p_value(Sn)

        d = {
            'name': name,
            'Sn': Sn,
            'p-value': pv
        }
        stat.append(d.copy())

    stat = pd.DataFrame(stat).set_index('name')
    print(stat)
