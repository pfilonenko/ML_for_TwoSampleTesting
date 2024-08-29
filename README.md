# Machine Learning for Two-Sample Testing under Right-Censored Data: A Simulation Study
- [Petr PHILONENKO](https://orcid.org/0000-0002-6295-4470), Ph.D. in Computer Science;
- [Sergey POSTOVALOV](https://orcid.org/0000-0003-3718-1936), D.Sc. in Computer Science.

# About
This repository is a part of the paper addressed to solve the two-sample problem under right-censored observations using Machine Learning.

The problem statement can be formualted as $H_0: S_1(t) = S_2(t)$ vs $H: S_1(t) \neq S_2(t)$.


# Repository
This repository includes following parts:
- **DATASET** contains the C++ project for the dataset simulation and a fragment of resulting dataset. The full dataset can be downloaded at the Hugging Face (pfilonenko/ML_for_TwoSampleTesting/).
- **PROPOSED_ML_FOR_TWO_SAMPLE_TESTING** contains an python-project for the proposed methods. This implementation represents the end-to-end pipeline (from two right-censored samples to the $p$-value).
- **SUPPLEMENTARY_MATERIALS** contains results of the test power and percentage points for the proposed methods.

For this repository there is corresponding repository at the Hugging Face with full version of used datasets ([pfilonenko/ML_for_TwoSampleTesting/](https://huggingface.co/datasets/pfilonenko/ML_for_TwoSampleTesting)).

# Pipeline for the proposed two-sample methods
**TWO-SAMPLE TESTING VIA THE PROPOSED METHODS CONTAINS FOLLOWING STEPS:**
1) Select 2 samples with right-censored observations;
2) Compute test statistics of several classical two-sample tests;
3) Load test statistics into the proposed method;
4) Compute test statistic of the proposed method;
5) Compute corresponding $p$-value using the table of percentage points.

![Pipeline of the proposed methods](https://github.com/pfilonenko/ML_for_TwoSampleTesting/blob/main/ML_flow.png)

# Example

To run the proposed methods, you have to run the script **Example.py** in the folder:
> ML_for_TwoSampleTesting / proposed_ml_for_two_sample_testing / source /

To get there, click [here](https://github.com/pfilonenko/ML_for_TwoSampleTesting/tree/main/proposed_ml_for_two_sample_testing/source).

The source code of the Example.py:
```python
# Example.py
import numpy as np
import pandas as pd

from TwoSample_Tests import *
from ML_TwoSample_Method import ML_TwoSample_Method

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

        print('Sn: {:.4}, p-value: {:.3}±{:.3}'.format(Sn,pvalue,avg_error))
        
```
