# libs
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from tqdm import tqdm
from EmpiricalDistributionFunction import EmpiricalDistributionFunction

# read data with predictions
def read_data(path, nrows):
    # used columns
    usecols = [
        'iter', 'H0_H1', 'Hi', 'n1', 'n2', 'perc',
        'CatBoost_test', 'XGBoost_test', 'LightAutoML_test',
        'SKLEARN_RF_test', 'SKLEARN_LogReg_test', 'SKLEARN_GB_test'
    ]

    # data reading
    data = pd.read_csv(
        path,
        sep='\t',
        usecols=usecols,
        nrows=nrows
    ).set_index('iter')

    # only the H0 selection (without other alternatives)
    mask = data['H0_H1'] == 0
    data = data[mask]

    return data

# main process to compute the percent points
def processing(data):
    # INPUT PARAMETERS
    sizes = [20, 30, 50, 75, 100, 150, 200, 300, 500, 1000]
    sizes_for_draw = [20, 50, 100, 1000]
    rates = [0, 10, 20, 30, 40, 50]
    Hi = np.sort(list(set(data['Hi'])))
    tests = [
        'CatBoost_test', 'XGBoost_test', 'LightAutoML_test',
        'SKLEARN_RF_test', 'SKLEARN_LogReg_test', 'SKLEARN_GB_test'
    ]

    # GRID
    k = 1001
    x = np.linspace(0.0, 1.0, k)

    # COLORS
    color = ['lightblue', 'moccasin', 'lightgreen', 'salmon']
    border_color = ['blue', 'orange', 'green', 'red']
    color = {n: c for n, c in zip(sizes_for_draw, color)}
    border_color = {n: c for n, c in zip(sizes_for_draw, border_color)}

    # RESULTING VAR
    perc_points = []

    # PROCESSING
    for test in tests:
        for rate in rates:
            plt.figure(figsize=(5, 5))
            print(test, rate)

            for n in tqdm(sizes):
                # CONSTRUCTING G(S|H0)_min, G(S|H0)_avg, G(S|H0)_max
                G_min = [1.0] * k
                G_avg = [0.5] * k
                G_max = [0.0] * k

                for H in Hi:
                    mask = (data['n1'] == n) & (data['perc'] == rate) & (data['Hi'] == H)
                    df = data[mask]

                    cdf = EmpiricalDistributionFunction(df[test])
                    y = [cdf(x_val) for x_val in x]

                    G_min = [min(a, b) for a, b in zip(G_min, y)]
                    G_max = [max(a, b) for a, b in zip(G_max, y)]
                    G_avg = [(a + b) / 2. for a, b in zip(G_min, G_max)]

                # PLOT
                if n in sizes_for_draw:
                    #plt.plot(x, G_min, color=border_color[n])
                    plt.plot(x, G_min, color=color[n])
                    plt.plot(x, G_avg, color='white')
                    #plt.plot(x, G_max, color=border_color[n])
                    plt.plot(x, G_max, color=color[n])
                    plt.fill_between(x, G_min, G_max, label=f'n={n}', color=color[n])

                # PERCENTAGE POINTS + DEVIATION
                cdf_MAX = EmpiricalDistributionFunction(G_max)
                cdf_AVG = EmpiricalDistributionFunction(G_avg)
                cdf_MIN = EmpiricalDistributionFunction(G_min)

                for p in x:
                    q = cdf_AVG.quantile(p)
                    max_val = cdf_MAX(q)
                    avg_val = cdf_AVG(q)
                    min_val = cdf_MIN(q)

                    d = {
                        'test': test,
                        'n': n,
                        'perc': rate,
                        'N': len(df),
                        'p': p,
                        'q=F_AVG^-1(p)': q,
                        'F_MIN(q)': min_val,
                        'F_AVG(q)': avg_val,
                        'F_MAX(q)': max_val,
                        '|F_MAX(q)-F_AVG(q)|': abs(max_val - avg_val),
                        '|F_AVG(q)-F_MIN(q)|': abs(min_val - avg_val),
                    }

                    perc_points.append(d.copy())

            # DRAW AND SAVE THE PLOT
            plt.title(f'{test}, PERC: {rate}')
            plt.grid()
            #plt.legend()
            plt.savefig(f'../plots/GSH0/{test}_perc{rate}_n{n}.png', dpi=600)

    return perc_points

# percent points saving
def save(perc_points):
    # RESULTING TABLE
    perc_points = pd.DataFrame(perc_points).set_index('test')
    for col in ['q=F_AVG^-1(p)', 'F_MIN(q)', 'F_AVG(q)', 'F_MAX(q)', '|F_MAX(q)-F_AVG(q)|', '|F_AVG(q)-F_MIN(q)|']:
        perc_points[col] = perc_points[col].astype(np.float16)
    perc_points.to_excel('../reports/GSH0/percent_points.xlsx')

# init point
if __name__ == '__main__':
    # path of the data
    path_dataset_with_ML_pred = '../data/3_dataset_with_ML_pred/dataset_with_ML_pred.tsv.gz'
    nrows = 1000000000

    # read data with predictions
    data = read_data(path_dataset_with_ML_pred, nrows)

    # main process to compute the percent points
    perc_points = processing(data)

    # percent points saving
    save(perc_points)
