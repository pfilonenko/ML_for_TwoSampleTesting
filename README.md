TITLE: "Machine Learning for Two-Sample Testing under Right-Censored Data: A Simulation Study"

AUTHORS: 
- PETR PHILONENKO, Ph.D. in Computer Science;
- SERGEY POSTOVALOV, D.Sc. in Computer Science.

This repository includes following parts:
- **DATASET** contains the C++ project for the dataset simulation and a fragment of resulting dataset. The full dataset can be downloaded at the Hugging Face (pfilonenko/ML_for_TwoSampleTesting/).
- **PROPOSED_ML_FOR_TWO_SAMPLE_TESTING** contains an python-project for the proposed methods. This implemention allows us to execute computation as end-to-end pipeline (from two right-censored samples to the $p$-value).
- **SUPPLEMENTARY_MATERIALS** contains results of the test power and percentage points for the proposed methods.

For this reposetory there is corresponding reposetory at the Hugging Face with full version of used datasets ([pfilonenko/ML_for_TwoSampleTesting/](https://huggingface.co/datasets/pfilonenko/ML_for_TwoSampleTesting)).

**TWO-SAMPLE TESTING VIA THE PROPOSED METHODS CONTAINS FOLLOWING STEPS:**
1) Select 2 samples with right-censored observations;
2) Compute test statistics of several classical two-sample tests;
3) Load test statistics into the proposed method;
4) Compute test statistic of the proposed method;
5) Compute corresponding $p$-value using the table of percentage points.
