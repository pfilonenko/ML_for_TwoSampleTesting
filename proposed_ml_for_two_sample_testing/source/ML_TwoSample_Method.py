# libs
import os
os.environ['CUDA_VISIBLE_DEVICES'] = '-1'
os.environ['OMP_NUM_THREADS'] = '20'

import yaml
import pickle
import joblib
import optuna
import numpy as np
import pandas as pd
import scipy.stats as st

from tqdm import tqdm
from multiprocessing import Pool

from xgboost import XGBClassifier
from catboost import CatBoostClassifier
from lightautoml.tasks import Task
from lightautoml.automl.presets.tabular_presets import TabularAutoML

from TwoSample_Tests import *
from ConfidenceInterval import ConfidenceInterval

from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.inspection import permutation_importance
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.metrics import roc_auc_score, confusion_matrix, f1_score, precision_score, recall_score, accuracy_score, average_precision_score
from sklearn.model_selection import StratifiedShuffleSplit, KFold, ShuffleSplit, RandomizedSearchCV, GridSearchCV

import warnings
warnings.filterwarnings('ignore')

# Object of the proposed ML-method for Two-Sample Problem
class ML_TwoSample_Method:
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

    # list of used features
    def get_X_usecols(self):
        usecols = [
            'iter', 'n1', 'n2', 'real_perc1', 'real_perc2',
            'Peto_test', 'Gehan_test', 'logrank_test',
            'BN_GPH_test', 'BN_MCE_test', 'BN_SCE_test',
            'Q_test', 'MAX_Value_test', 'MIN3_test',
            'WLg_TaroneWare_test', 'WLg_PetoPrentice_test', 'WLg_Prentice_test',
            'WKM_test'
        ]

        return usecols

    # list of target columns
    def get_Y_usecols(self):
        usecols = ['H0_H1']
        return usecols

    # dataset reading
    def read_dataset(self):
        # read data
        path_dataset = self.config['path_train_data']
        usecols = self.get_X_usecols() + self.get_Y_usecols()
        data = pd.read_csv(path_dataset, sep='\t', usecols=usecols, nrows=self.config['nrows']).set_index('iter')

        # transform H0 / H1
        data['H0_H1'] = data['H0_H1'].apply(lambda y: 1 if y == 'H1' else 0)

        # sample sizes
        validate_size = self.config['validate_size']
        test_size = self.config['test_size']
        train_size = 1 - validate_size - test_size

        nums = list(set(data.index))
        nums.sort()
        n = len(nums)

        k_train = int(n * train_size)
        k_val = int(n * validate_size)
        k_test = n - k_train - k_val

        train_nums =[nums.pop(0) for i in range(k_train)]
        val_nums = [nums.pop(0) for i in range(k_val)]
        test_nums = [nums.pop(0) for i in range(k_test)]

        # data split
        mask = data.index.isin(train_nums)
        x_train = data[mask]
        data = data[~mask]
        y_train = x_train.pop('H0_H1')

        mask = data.index.isin(val_nums)
        x_val = data[mask]
        data = data[~mask]
        y_val = x_val.pop('H0_H1')

        mask = data.index.isin(test_nums)
        x_test = data[mask]
        data = data[~mask]
        y_test = x_test.pop('H0_H1')

        return x_train, y_train, x_val, y_val, x_test, y_test

    # feature engineering
    def feature_engineering(self, xxx):
        # empty features
        features = xxx[[]]

        # minimal sample size
        features['min_n'] = xxx[['n1', 'n2']].T.min()
        features['min_n_0_50'] = features['min_n'].apply(lambda n: 1 if 0 <= n < 50 else 0)
        features['min_n_50_100'] = features['min_n'].apply(lambda n: 1 if 50 <= n < 100 else 0)
        features['min_n_100_500'] = features['min_n'].apply(lambda n: 1 if 100 <= n < 500 else 0)
        features['min_n_500+'] = features['min_n'].apply(lambda n: 1 if n >= 500 else 0)
        del features['min_n']

        # censoring rates
        features['weigh_cens_rate'] = (xxx['n1']*xxx['real_perc1'] + xxx['n2']*xxx['real_perc2']) / (xxx['n1'] + xxx['n2'] + 1.0e-14) / 100.
        features['cens_rate_zero'] = features['weigh_cens_rate'].apply(lambda x: 1 if x < 1.0e-14 else 0)
        features['cens_rate_low'] = features['weigh_cens_rate'].apply(lambda x: 1 if 0. < x <= 0.15 else 0)
        features['cens_rate_mid'] = features['weigh_cens_rate'].apply(lambda x: 1 if 0.15 < x <= 0.35 else 0)
        features['cens_rate_high'] = features['weigh_cens_rate'].apply(lambda x: 1 if x > 0.35 else 0)
        del features['weigh_cens_rate']

        # statistics to p-values
        tests = ['Peto_test', 'Gehan_test', 'logrank_test', 'BN_GPH_test', 'BN_MCE_test', 'BN_SCE_test', 'Q_test', 'MAX_Value_test', 'MIN3_test', 'WLg_TaroneWare_test', 'WLg_PetoPrentice_test', 'WLg_Prentice_test', 'WKM_test']
        for test_name in tqdm(tests):
            features[test_name] = xxx[test_name]
            if test_name in ['Peto_test', 'Gehan_test', 'logrank_test', 'WKM_test']:
                vals = st.norm.cdf(features[test_name])
                p_values = [2*min(val, 1-val) for val in vals]
                features[test_name] = p_values
            elif test_name in ['BN_GPH_test', 'BN_SCE_test']:
                vals = stats.chi2.cdf(features[test_name], df=2)
                p_values = [1 - val for val in vals]
                features[test_name] = p_values
            elif test_name in ['BN_MCE_test']:
                vals = stats.chi2.cdf(features[test_name], df=3)
                p_values = [1 - val for val in vals]
                features[test_name] = p_values
            elif test_name in ['WLg_TaroneWare_test', 'WLg_PetoPrentice_test', 'WLg_Prentice_test']:
                vals = stats.chi2.cdf(features[test_name], df=1)
                p_values = [1 - val for val in vals]
                features[test_name] = p_values
            else:
                continue

        # MAX_Value_test (Sn to p-value): Sn = MAX(|Sn_Gehan|, |Sn_logrank|) = MIN(|pvalue_Gehan|, |pvalue_logrank|)
        features['MAX_Value_test'] = features[['logrank_test', 'Gehan_test']].T.min()

        return features

    # OPTUNA objective
    def objective(self, trial):
        # params for optimization
        model_name = self.config['model_name']
        x_train = self.optuna_param['x_train']
        y_train = self.optuna_param['y_train']
        x_val = self.optuna_param['x_val']
        y_val = self.optuna_param['y_val']
        best_metric = self.optuna_param['best_metric']

        # model training XGBoost
        if model_name == 'XGBoost':
            # create model instance
            model = XGBClassifier(
                n_estimators=trial.suggest_categorical('n_estimators', self.config['n_estimators']),
                max_depth=trial.suggest_categorical('max_depth', self.config['max_depth']),
                learning_rate=trial.suggest_categorical('learning_rate', self.config['learning_rate']),
                objective=trial.suggest_categorical('objective', self.config['objective']),
                verbose=self.config['verbose'],
                n_jobs=self.config['n_cores'],
                random_state=self.config['seed'],
            ).fit(x_train, y_train)

        # model training SKLEARN_LogReg
        elif model_name == 'SKLEARN_LogReg':
            # create model instance
            model = LogisticRegression(
                penalty=trial.suggest_categorical('penalty', self.config['penalty']),
                dual=trial.suggest_categorical('dual', self.config['dual']),
                tol=trial.suggest_categorical('tol', self.config['tol']),
                C=trial.suggest_categorical('C', self.config['C']),
                fit_intercept=trial.suggest_categorical('fit_intercept', self.config['fit_intercept']),
                solver=self.config['solver'],
                max_iter=self.config['max_iter'],
                n_jobs=self.config['n_cores'],
                verbose=self.config['verbose'],
                random_state=self.config['seed'],
            ).fit(x_train, y_train)

        # model training SKLEARN_RF
        elif model_name == 'SKLEARN_RF':
            # create model instance
            model = RandomForestClassifier(
                n_estimators=trial.suggest_categorical('n_estimators', self.config['n_estimators']),
                max_depth=trial.suggest_categorical('max_depth', self.config['max_depth']),
                min_samples_split=trial.suggest_categorical('min_samples_split', self.config['min_samples_split']),
                min_samples_leaf=trial.suggest_categorical('min_samples_leaf', self.config['min_samples_leaf']),
                max_features=trial.suggest_categorical('max_features', self.config['max_features']),
                bootstrap=trial.suggest_categorical('bootstrap', self.config['bootstrap']),
                n_jobs=self.config['n_cores'],
                random_state=self.config['seed'],
                verbose=self.config['verbose'],
                ccp_alpha=trial.suggest_categorical('ccp_alpha', self.config['ccp_alpha']),
            ).fit(x_train, y_train)

        # model training SKLEARN_GB
        elif model_name == 'SKLEARN_GB':
            # create model instance
            model = GradientBoostingClassifier(
                loss=trial.suggest_categorical('loss', self.config['loss']),
                learning_rate=trial.suggest_categorical('learning_rate', self.config['learning_rate']),
                n_estimators=trial.suggest_categorical('n_estimators', self.config['n_estimators']),
                criterion=trial.suggest_categorical('criterion', self.config['criterion']),
                min_samples_split=trial.suggest_categorical('min_samples_split', self.config['min_samples_split']),
                min_samples_leaf=trial.suggest_categorical('min_samples_leaf', self.config['min_samples_leaf']),
                max_depth=trial.suggest_categorical('max_depth', self.config['max_depth']),
                max_features=trial.suggest_categorical('max_features', self.config['max_features']),
                tol=trial.suggest_categorical('tol', self.config['tol']),
                ccp_alpha=trial.suggest_categorical('ccp_alpha', self.config['ccp_alpha']),
                verbose=self.config['verbose'],
                random_state=self.config['seed'],
            ).fit(x_train, y_train)

        # otherwise branch
        else:
            raise 'Unknown model.'

        # model prediction
        y_pred = model.predict(x_val)
        metric = accuracy_score(y_val, y_pred)

        # check for best
        if metric > best_metric:
            self.optuna_param['best_metric'] = metric
            self.optuna_param['best_model'] = model
        print(f"\t metric: {metric} \t best_metric: {self.optuna_param['best_metric']}")

        return metric

    # CatBoost training
    def CatBoost(self, x_train, y_train, x_val, y_val):
        # create model instance
        model = CatBoostClassifier(iterations=self.config['iterations'])
        model.fit(x_train, y_train, verbose=True)

        # feature importance
        print('-------- feature_importance --------')
        fi = pd.Series(
            model.get_feature_importance(),
            index=x_train.columns
        ).sort_values(ascending=False)

        return model, fi

    # metric for LightAutoML training
    def LightAutoML_metric(self, y_true, y_prob):
        y_pred = (y_prob > 0.5) * 1
        score = average_precision_score(y_true=y_true, y_score=y_pred)
        return score

    # LightAutoML training
    def LightAutoML(self, x_train, y_train, x_val, y_val):
        # targets for LAMA should be contained into the dataset
        x_train.insert(0, 'H0/H1', y_train)

        # create model instance
        model = TabularAutoML(
            task=Task(
                name='binary',
                metric=self.LightAutoML_metric
            ),
            cpu_limit=self.config['n_cores'],
            timeout=self.config['timeout'],
            memory_limit=self.config['memory_limit']
        )
        model.fit_predict(x_train, roles={'target': 'H0/H1'}, verbose=self.config['verbose'])

        # feature importance
        fi = None

        return model, fi

    # XGBoost training
    def XGBoost(self, x_train, y_train, x_val, y_val):
        # params making for optuna optimization
        self.optuna_param = {
            'x_train': x_train,
            'y_train': y_train,
            'x_val': x_val,
            'y_val': y_val,
            'best_metric': -np.inf,
            'best_model': None,
        }

        # optuna's study
        study = optuna.create_study(direction='maximize')
        study.optimize(self.objective, n_trials=self.config['optuna_n_trials'])
        model = self.optuna_param['best_model']

        # feature importance
        print('-------- feature_importance --------')
        fi = pd.Series(
            model.feature_importances_,
            index=x_train.columns
        ).sort_values(ascending=False)

        return model, fi

    # SKLEARN_LogReg training
    def SKLEARN_LogReg(self, x_train, y_train, x_val, y_val):
        # params making for optuna optimization
        self.optuna_param = {
            'x_train': x_train,
            'y_train': y_train,
            'x_val': x_val,
            'y_val': y_val,
            'best_metric': -np.inf,
            'best_model': None,
        }

        # optuna's study
        study = optuna.create_study(direction='maximize')
        study.optimize(self.objective, n_trials=self.config['optuna_n_trials'])

        # result
        model = self.optuna_param['best_model']
        fi = None

        return model, fi

    # SKLEARN_RF training
    def SKLEARN_RF(self, x_train, y_train, x_val, y_val):
        # params making for optuna optimization
        self.optuna_param = {
            'x_train': x_train,
            'y_train': y_train,
            'x_val': x_val,
            'y_val': y_val,
            'best_metric': -np.inf,
            'best_model': None,
        }

        # optuna's study
        study = optuna.create_study(direction='maximize')
        study.optimize(self.objective, n_trials=self.config['optuna_n_trials'])
        model = self.optuna_param['best_model']

        # feature importance
        print('-------- feature_importance --------')
        fi = pd.Series(
            model.feature_importances_,
            index=x_train.columns
        ).sort_values(ascending=False)

        return model, fi

    # SKLEARN_GB training
    def SKLEARN_GB(self, x_train, y_train, x_val, y_val):
        # params making for optuna optimization
        self.optuna_param = {
            'x_train': x_train,
            'y_train': y_train,
            'x_val': x_val,
            'y_val': y_val,
            'best_metric': -np.inf,
            'best_model': None,
        }

        # optuna's study
        study = optuna.create_study(direction='maximize')
        study.optimize(self.objective, n_trials=self.config['optuna_n_trials'])
        model = self.optuna_param['best_model']

        # feature importance
        print('-------- feature_importance --------')
        fi = pd.Series(
            model.feature_importances_,
            index=x_train.columns
        ).sort_values(ascending=False)

        return model, fi

    # model training
    def train_model(self, x_train, y_train, x_val, y_val):
        # list of features
        features = list(x_train.columns)

        # select the model
        model_name = self.config['model_name']
        print('model_name: ', model_name)
        if model_name == 'CatBoost':
            model, fi = self.CatBoost(x_train, y_train, x_val, y_val)
        elif model_name == 'LightAutoML':
            model, fi = self.LightAutoML(x_train, y_train, x_val, y_val)
        elif model_name == 'XGBoost':
            model, fi = self.XGBoost(x_train, y_train, x_val, y_val)
        elif model_name == 'SKLEARN_LogReg':
            model, fi = self.SKLEARN_LogReg(x_train, y_train, x_val, y_val)
        elif model_name == 'SKLEARN_RF':
            model, fi = self.SKLEARN_RF(x_train, y_train, x_val, y_val)
        elif model_name == 'SKLEARN_GB':
            model, fi = self.SKLEARN_GB(x_train, y_train, x_val, y_val)
        else:
            model = None
            fi = None

        print(fi)
        return model, features, fi

    # cross-validation (k-Folds)
    def kFoldsCrossValidation(self, y_true, y_prob, y_pred):
        # set key metrics
        metrics = {
            'Accuracy': [],
            'Precision': [],
            'Recall': [],
            'ROC_AUC': [],
            'Avg_Precision': [],
            'Sensitivity': [],
            'Specificity': [],
            'FN_part': [],
        }

        # set parameters of cross-validation
        kFolds = self.config['kFolds']
        n = len(y_true)
        m = int(n / kFolds)

        # iterating of each Fold
        for i in range(kFolds):
            # [a; b]
            a = i*m
            b = (i+1)*m

            # predictions
            true = y_true[a:b]
            prob = y_prob[a:b]
            pred = y_pred[a:b]

            # confusion matrix
            tn, fp, fn, tp = confusion_matrix(y_true=true, y_pred=pred).ravel()

            # metrics computation
            metrics['Accuracy'].append( accuracy_score(y_true=true, y_pred=pred) )
            metrics['Precision'].append( precision_score(y_true=true, y_pred=pred) )
            metrics['Recall'].append( recall_score(y_true=true, y_pred=pred) )
            metrics['ROC_AUC'].append( roc_auc_score(y_true=true, y_score=prob) )
            metrics['Avg_Precision'].append( average_precision_score(y_true=true, y_score=prob) )
            metrics['Sensitivity'].append( tp/(tp + fn + 1.0e-14) )
            metrics['Specificity'].append( tn/(tn + fp + 1.0e-14) )
            metrics['FN_part'].append(1.0 - fn / (tp + fp + fn + tn + 1.0e-14))

        # preparation of confidence intervals
        CI = ConfidenceInterval()
        for metric in metrics:
            # get obtained values
            mas = metrics[metric]

            # confidence interval computation
            mean, delta = CI.computation(mas=mas, confidence=self.config['confidence'])

            # print result
            new_val = '{:.4} ± {:.4}'.format(mean, delta)
            metrics[metric] = new_val

        metrics = pd.Series(metrics)
        return metrics

    # model testing
    def test_model(self, model, features, x_train, y_train, x_val, y_val, x_test, y_test):
        # cross-validation
        report = pd.DataFrame()
        for xxx,yyy,title in [(x_train,y_train,'TRAIN'), (x_val,y_val,'VAL'), (x_test,y_test,'TEST')]:
            print(f'-------- {title} --------')
            # make binary and continuous predictions
            xxx = xxx.loc[:, features]
            if self.config['model_name'] != 'LightAutoML':
                y_pred = model.predict(xxx)
                y_prob = [p[1] for p in model.predict_proba(xxx)]
            else:
                y_prob = list(model.predict(xxx).data.flatten())
                y_pred = [1 if p > 0.5 else 0 for p in y_prob]

            # confusion matrix
            tn, fp, fn, tp = confusion_matrix(y_true=yyy, y_pred=y_pred).ravel()
            conf_matr = f'TP: {tp}, FP: {fp}\nFN: {fn}, TN: {tn}'
            print(conf_matr)

            # cross-validation (k-Folds)
            metrics = self.kFoldsCrossValidation(yyy, y_prob, y_pred)
            report[title] = metrics

        # print results of cross-validation
        print(report)

        # permutation importance
        print('-------- permutation_importance --------')
        try:
            pi = permutation_importance(
                estimator=model,
                X=x_test,
                y=y_test,
                scoring='average_precision',
                n_repeats=self.config['kFolds'],
                n_jobs=self.config['n_cores'],
                random_state=self.config['seed'],
            )
            print(pd.Series(pi['importances_mean'], index=x_test.columns).sort_values(ascending=False))
        except:
            print('- None')

        return report

    # main steps of model training
    def processing(self):
        # split dataset on samples
        x_train, y_train, x_val, y_val, x_test, y_test = self.read_dataset()

        # info about target distribution
        for yyy in [y_train, y_val, y_test]:
            print(f'n: {len(yyy)}, part(y=1): {yyy.mean()*100}')

        # feature engineering
        x_train = self.feature_engineering(x_train)
        x_val = self.feature_engineering(x_val)
        x_test = self.feature_engineering(x_test)

        # training
        model, features, feature_importance = self.train_model(x_train, y_train, x_val, y_val)

        # testing
        report = self.test_model(model, features, x_train, y_train, x_val, y_val, x_test, y_test)

        # the object for saving
        model_obj = {
            'model': model,
            'features': features,
            'feature_importance': feature_importance,
            'config': self.config,
            'report': report,
        }

        return model_obj

    # constructor
    def __init__(self, CONFIG_NAME):
        # config-file loading
        self.load_config(CONFIG_NAME)

        # load the model if one is trained else training
        path_trained_model = self.config['model_dir'] + self.config['model_name'] + '.h5'
        try:
            self.model_obj = self.load_object_by_pickle(path_trained_model)
            print(f'{self.config["model_name"]} была загружена.')
        except:
            print('=' * 40)
            print(f'{self.config["model_name"]} НЕ НАЙДЕНА. Начинается процесс обучения модели...')
            self.model_obj = self.processing()
            self.save_object_by_pickle(path_trained_model, self.model_obj)

    # INFERENCE of the proposed model
    def INFERENCE(self, n1, n2, cens_rate1, cens_rate2, S_peto, S_gehan, S_logrank, S_BN_GPH, S_BN_MCE, S_BN_SCE, S_Q, S_MAX, S_MIN3, S_WLg_TaroneWare, S_WLg_PetoPrentice, S_WLg_Prentice, S_WKM):
        # data preparation
        row = {
            'n1': n1,
            'n2': n2,
            'real_perc1': cens_rate1,
            'real_perc2': cens_rate2,
            'Peto_test': S_peto,
            'Gehan_test': S_gehan,
            'logrank_test': S_logrank,
            'BN_GPH_test': S_BN_GPH,
            'BN_MCE_test': S_BN_MCE,
            'BN_SCE_test': S_BN_SCE,
            'Q_test': S_Q,
            'MAX_Value_test': S_MAX,
            'MIN3_test': S_MIN3,
            'WLg_TaroneWare_test': S_WLg_TaroneWare,
            'WLg_PetoPrentice_test': S_WLg_PetoPrentice,
            'WLg_Prentice_test': S_WLg_Prentice,
            'WKM_test': S_WKM
        }

        # feature engineering
        data = pd.DataFrame()
        data['observation'] = row
        data = data.T
        data = self.feature_engineering(data)

        # get the trained model
        features = self.model_obj['features']
        model = self.model_obj['model']
        df = data.loc[:, features]

        # make prediction
        if self.config['model_name'] != 'LightAutoML':
            Sn = model.predict_proba(df)[0][1]
        else:
            Sn = model.predict(df).data[0][0]

        # p-value
        (pvalue, avg_error) = self.P_VALUE(Sn, n1, n2, cens_rate1, cens_rate2)

        return Sn, pvalue, avg_error

    # P-VALUE
    def P_VALUE(self, Sn, n1, n2, cens_rate1, cens_rate2):
        # reading the percent points
        test = self.config['model_name'] + '_test'
        perc_points = pd.read_csv('../reports/GSH0/percent_points.tsv.gz', sep='\t')
        perc_points = perc_points[perc_points['test'] == test]

        # set sample parameters
        perc_points['avg_n'] = (n1 + n2) / 2.
        perc_points['w_perc'] = (cens_rate1*n1 + cens_rate2*n2) / (n1 + n2)

        # find differences
        perc_points['avg_n'] = np.abs(perc_points['avg_n'] - perc_points['n'])
        perc_points['w_perc'] = np.abs(perc_points['w_perc'] - perc_points['perc'])

        # find optimal (=closest) sample size and censoring rate
        perc_points['func'] = perc_points['avg_n'] * perc_points['w_perc']
        min_val = perc_points['func'].min()
        perc_points = perc_points[perc_points['func'] == min_val]

        # find closest value of the G(S|H0) to Sn
        perc_points['Sn'] = Sn
        perc_points['diff'] = np.abs(perc_points['Sn'] - perc_points['F_AVG(q)'])
        min_val = perc_points['diff'].min()
        perc_points = perc_points[perc_points['diff'] == min_val]
        d = perc_points.iloc[0].to_dict()

        # pvalue and avg_error
        pvalue = d['p']
        avg_error = max(d['|F_MAX(q)-F_AVG(q)|'], d['|F_AVG(q)-F_MIN(q)|'])

        return pvalue, avg_error

# start point
if __name__ == '__main__':
    # list of config-files
    CONFIG_NAMES = [
        './CONFIGS/CatBoost_CONFIG.yaml',
        './CONFIGS/XGBoost_CONFIG.yaml',
        './CONFIGS/LightAutoML_CONFIG.yaml',
        './CONFIGS/SKLEARN_RF_CONFIG.yaml',
        './CONFIGS/SKLEARN_LogReg_CONFIG.yaml',
        './CONFIGS/SKLEARN_GB_CONFIG.yaml',
    ]

    # load samples
    A = Sample('./samples/1Chemotherapy.txt')
    B = Sample('./samples/2Radiotherapy.txt')

    # iterating over config-files
    for CONFIG_NAME in CONFIG_NAMES:
        # load / train the model
        ml = ML_TwoSample_Method(CONFIG_NAME=CONFIG_NAME)

        # inference
        (Sn, pvalue, avg_error) = ml.INFERENCE(
            n1                  = A.N(),
            n2                  = B.N(),
            cens_rate1          = A.censoring_rate(),
            cens_rate2          = B.censoring_rate(),
            S_peto              = GeneralizedPeto_Test().statistic(A, B),
            S_gehan             = GeneralizedGehan_Test().statistic(A, B),
            S_logrank           = Logrank_Test().statistic(A, B),
            S_BN_GPH            = BN_GPH_Test().statistic(A, B),
            S_BN_MCE            = BN_MCE_Test().statistic(A, B),
            S_BN_SCE            = BN_SCE_Test().statistic(A, B),
            S_Q                 = Q_Test().statistic(A, B),
            S_MAX               = MAX_Value_Test().statistic(A, B),
            S_MIN3              = MIN3_Test().statistic(A, B),
            S_WLg_TaroneWare    = WeightedLogrank_Test('TaroneWare').statistic(A, B),
            S_WLg_PetoPrentice  = WeightedLogrank_Test('PetoPrentice').statistic(A, B),
            S_WLg_Prentice      = WeightedLogrank_Test('Prentice').statistic(A, B),
            S_WKM               = WeightedKaplanMeier_Test().statistic(A, B),
        )

        print(f'Sn: {Sn}, p-value: {pvalue}, avg_error: {avg_error}')
