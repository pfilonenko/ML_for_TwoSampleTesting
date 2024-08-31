# libs
import numpy as np
import pandas as pd

from TwoSample_Tests import *
from ML_TwoSample_Method import ML_TwoSample_Method

# start point
if __name__ == '__main__':
    # list of config-files
    CONFIG_NAMES = [    
        './CONFIGS/SKLEARN_LogReg_CONFIG.yaml',
        './CONFIGS/SKLEARN_RF_CONFIG.yaml',
        './CONFIGS/SKLEARN_GB_CONFIG.yaml',
        './CONFIGS/XGBoost_CONFIG.yaml',
        './CONFIGS/CatBoost_CONFIG.yaml',
        #'./CONFIGS/LightAutoML_CONFIG.yaml',    # before to run, you have to go to the '../models/LightAutoML/' 
    ]                                            # and to unrar the trained model

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

        print('Sn: {:.4}, p-value: {:.3}±{:.3}'.format(Sn,pvalue,avg_error))
        
