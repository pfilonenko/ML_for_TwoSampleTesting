# libs
import yaml
import pickle
import numpy as np
import pandas as pd

from Power import *
from tqdm import tqdm
from multiprocessing import Pool

import optuna
from xgboost import XGBClassifier
from catboost import CatBoostClassifier
from lightautoml.tasks import Task
from lightautoml.automl.presets.tabular_presets import TabularAutoML

from ML_TwoSample_Method import ML_TwoSample_Method

from sklearn.model_selection import train_test_split
from sklearn.inspection import permutation_importance
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.metrics import roc_auc_score, confusion_matrix, f1_score, precision_score, recall_score, accuracy_score, average_precision_score
from sklearn.model_selection import StratifiedShuffleSplit, KFold, ShuffleSplit, RandomizedSearchCV, GridSearchCV

import warnings
warnings.filterwarnings('ignore')

# Simulation Object
class InvestigationPower:
    # deserialization of the saved object
    def load_object_by_pickle(self, path):
        loaded_obj = pickle.load(open(path, 'rb'))
        return loaded_obj

    # serialization of the object to save
    def save_object_by_pickle(self, path, saved_obj):
        s = pickle.dumps(saved_obj)
        fd = open(path, 'wb')
        fd.write(s)
        fd.close()

    # config-file loading
    def load_config(self, config_path):
        with open(config_path, 'r') as file:
            self.config = yaml.safe_load(file)

    # dataset reading
    def read_data(self):
        # dataset loading
        path_simulation_data = self.config['path_simulation_data']
        data = pd.read_csv(path_simulation_data, sep='\t', nrows=self.config['nrows_simulation']).set_index('iter')

        # transform H0 / H1 to 0 / 1
        data['H0_H1'] = data['H0_H1'].apply(lambda y: 1 if y == 'H1' else 0)

        print('Data has been loaded.')
        return data

    # pre-trained models loading
    def load_models(self):
        models = {
            'CatBoost': ML_TwoSample_Method(CONFIG_NAME='./CONFIGS/CatBoost_CONFIG.yaml'),
            'XGBoost': ML_TwoSample_Method(CONFIG_NAME='./CONFIGS/XGBoost_CONFIG.yaml'),
            'LightAutoML': ML_TwoSample_Method(CONFIG_NAME='./CONFIGS/LightAutoML_CONFIG.yaml'),
            'SKLEARN_RF': ML_TwoSample_Method(CONFIG_NAME='./CONFIGS/SKLEARN_RF_CONFIG.yaml'),
            'SKLEARN_LogReg': ML_TwoSample_Method(CONFIG_NAME='./CONFIGS/SKLEARN_LogReg_CONFIG.yaml'),
            'SKLEARN_GB': ML_TwoSample_Method(CONFIG_NAME='./CONFIGS/SKLEARN_GB_CONFIG.yaml'),
        }

        return models

    # statistics computation of the proposed tests
    def make_prediction(self, models, data):
        # add pre-trained models
        x_pred = None
        for model_name in models:
            print(model_name)

            # get model data
            model_class = models[model_name]
            model = model_class.model_obj['model']
            features = model_class.model_obj['features']

            # once making x_pred for prediction (to avoid repeating actions)
            if x_pred is None:
                x_pred = model_class.feature_engineering(data)
                x_pred = x_pred.loc[:, features]

            # test statistic computation by the model
            if model_name != 'LightAutoML':
                y_pred = [p[1] for p in model.predict_proba(x_pred)]
            else:
                y_pred = list(model.predict(x_pred).data.flatten())

            # add new column in the dataset
            new_col = f'{model_name}_test'
            data[new_col] = y_pred
            self.critical_area[new_col] = 'right'

        # save dataset using ML-predictions
        data.to_csv(self.config['path_dataset_with_ML_pred'], sep='\t', compression='gzip')

        print('Predictions have been done.')
        return data

    # test power computation for a fixed alternative
    def computation(self, data):
        # get input parameters of an alternative
        order = data[0]['order']
        model = data[0]['Hi']
        n1 = data[0]['n1']
        n2 = data[0]['n2']
        perc = data[0]['perc']
        data = pd.DataFrame(data)

        # create resulting dict
        param = {
            'order': order,
            'model': model,
            'n1': n1,
            'n2': n2,
            'perc': perc
        }

        # make message in Command Line
        if n1 == 20 and perc == 0:
            print(model)

        # An error of the 1-st kind
        alpha = self.config['alpha']
        param['alpha'] = alpha

        # get list of two-sample tests
        mask = data.columns.str.contains('_test')
        tests = list(data.loc[:, mask].columns)

        # select only needed alternative hypothesis
        mask = data['Hi'] == model
        data = data[mask]

        # make Object to compute a power value using G(S|H0) and G(S|H1)
        power = Power()

        # iterating over tests
        for test in tests:
            # get test statistics for G(S|H0) and G(S|H1)
            mask = (data['Hi'] == model) & (data['n1'] == n1) & (data['n2'] == n2) & (data['perc'] == perc)
            df = data[mask]

            # split test statistics on G(S|H0) and G(S|H1)
            GSH0 = df[df['H0_H1'] == 0][test]
            GSH1 = df[df['H0_H1'] == 1][test]

            # compute sizes of samples
            param['G(S|H0)_n'] = len(GSH0)
            param['G(S|H1)_n'] = len(GSH1)

            # computaton of test power
            critical_area = self.critical_area[test]
            param[test] = power.computation(GSH0, GSH1, critical_area, alpha=alpha)

        del data
        return param

    # main steps of test power computation
    def power_research(self, data):
        # make list of parameters
        vars = data[['Hi', 'n1', 'n2', 'perc']].drop_duplicates()
        order_max = len(vars)

        # ranking unique combination of parameters
        d = {}
        order = 0
        for Hi,n1,n2,perc in zip(vars['Hi'],vars['n1'],vars['n2'],vars['perc']):
            key = (Hi,n1,n2,perc)
            d[key] = order
            order += 1

        # mark any raw in dataset using ranking
        orders = []
        for Hi,n1,n2,perc in zip(data['Hi'],data['n1'],data['n2'],data['perc']):
            key = (Hi, n1, n2, perc)
            order = d[key]
            orders.append(order)

        # add to the dataset
        data['order'] = orders
        data = data.to_dict('records')

        # split rows of dataset to parts
        mas = [[] for order in range(order_max)]
        for i in tqdm(range(len(data))):
            elem = data.pop()
            order = elem['order']
            mas[order].append(elem.copy())
        del data

        # get parameters of test power computation
        n_cores = self.config['n_cores']
        n_chunks = n_cores

        # processing by parts
        res = []
        while len(mas) > 0:
            print(f'REST: {len(mas)}')
            sel = [mas.pop() for i in range(n_chunks) if len(mas) > 0]

            # paralleling computation
            with Pool(n_cores) as p:
                part = p.map(self.computation, sel)
                res += part

        # save of results
        report = pd.DataFrame(res).sort_values(by='order', ascending=True)
        path_report = self.config['report_dir'] + 'POWER_SIMULATION.tsv'
        report.to_csv(path_report, sep='\t', index=False)

    # main steps of Simulation
    def processing(self):
        # dataset reading
        data = self.read_data()

        # pre-trained models loading
        models = self.load_models()

        # statistics computation of the proposed tests
        data = self.make_prediction(models, data)

        # main steps of test power computation
        self.power_research(data)

    # initializing of critical_area tests
    def set_critical_area(self):
        self.critical_area = {
            'Peto_test': 'double',
            'Gehan_test': 'double',
            'logrank_test': 'double',
            'CoxMantel_test': 'double',
            'BN_GPH_test': 'right',
            'BN_MCE_test': 'right',
            'BN_SCE_test': 'right',
            'WLg_logrank_test': 'right',
            'WLg_TaroneWare_test': 'right',
            'WLg_Breslow_test': 'right',
            'WLg_PetoPrentice_test': 'right',
            'WLg_Prentice_test': 'right',
            'WKM_test': 'double',
            'MAX_Value_test': 'right',
            'MIN3_test': 'left',
            'Q_test': 'double',
        }

    # constructor
    def __init__(self, CONFIG_NAME):
        # config-file loading
        self.load_config(CONFIG_NAME)

        # initializing of critical_area tests
        self.set_critical_area()

        # main steps of Simulation
        self.processing()

# start point
if __name__ == '__main__':
    # path for config-file
    CONFIG_NAME = './CONFIGS/CONFIG_InvestigationPower.yaml'

    # Simulation Object
    ip = InvestigationPower(CONFIG_NAME=CONFIG_NAME)
