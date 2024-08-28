# libs
import numpy as np
import pandas as pd

# Kaplan-Meier estimator
class KaplanMeierEstimator:
    def __init__(self, X, C):
        X = list(X)
        C = list(C)
        
        self.X = X
        self.C = C
        self.N = len(X)
        self.F = [0] * self.N
        
        self.TheLastIsCensoredObservation = C[-1] == 1

        val = 1.0
        for i in range(self.N):
            if C[i] == 0:  # uncensored
                self.F[i] = val * (self.N - (i + 1)) / (self.N - (i + 1) + 1)
                val = self.F[i]
            else:  # censored
                self.F[i] = val

        # Fill F array backwards
        for i in range(self.N - 1, 0, -1):
            self.F[i] = self.F[i - 1]
        self.F[0] = 1.0

    def __call__(self, x):
        if x < self.X[0]:  # before the first observation
            return self.F[0]
        elif x >= self.X[-1]:  # after the last observation
            return 0.0 if not self.TheLastIsCensoredObservation else self.F[-1]
        else:  # between observations
            for i in range(self.N - 1):
                if self.X[i] <= x < self.X[i + 1]:
                    return self.F[i + 1]

    def Quantile(self, alpha):
        if alpha >= 1.0:
            return -np.inf
        elif alpha <= 0.0:
            return np.inf
        else:
            if alpha < self.F[-1]:
                return float('inf') if self.TheLastIsCensoredObservation else self.X[-1]
            else:
                for i in range(self.N - 1):
                    if self.F[i] > alpha >= self.F[i + 1]:
                        return self.X[i]

    def get_estimate_title(self):
        return 'KaplanMeierEstimator'

# init point
if __name__ == '__main__':
    # Estimator fitting
    T = [0.4, 2.6, 1.1, 3.2, 1.8, 1.8]
    C = [0, 0, 0, 0, 0, 0]
    S_KM = KaplanMeierEstimator(T, C)

    # make prediction
    t = 0.20
    print(t, S_KM.Quantile(t))
    
