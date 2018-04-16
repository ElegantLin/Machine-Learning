from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier, RandomForestClassifier
from sklearn import preprocessing
from sklearn.decomposition import PCA
from sklearn.metrics import classification_report, accuracy_score
from sklearn.cross_validation import train_test_split
from imblearn.ensemble.easy_ensemble import EasyEnsemble
from imblearn.ensemble.balance_cascade import BalanceCascade
from imblearn.over_sampling import SMOTE
from sklearn.externals.six import StringIO
from sklearn import tree
from matplotlib.ticker import MultipleLocator
from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
from IPython.display import Image

def test_RandomForestClassifier_num(*data):
    X_train, X_test, y_train, y_test = data
    nums = np.arange(100, 500, step=1)
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    testing_scores = []
    training_scores = []
    for num in nums:
        clf = RandomForestClassifier(n_estimators=num)
        clf.fit(X_train, y_train)
        training_scores.append(clf.score(X_train, y_train))
        testing_scores.append(clf.score(X_test, y_train))
    ax.plot(nums, training_scores, label="Training score")
    ax.plot(nums, testing_scores, label="Testing score")
    ax.legend(loc="low right")
    ax.set_ylim(0, 1.05)
    spacing_x = 1
    minorLocator_x = MultipleLocator(spacing_x)
    ax.xaxis.set_minor_locator(minorLocator_x)
    ax.grid(which='minor')
    plt.show()
    plt.grid(which='minor')

def test_RandomForestClassifier_max_depth(*data):
    X_train, X_test, y_train, y_test = data
    maxdepth = range(1, 50)
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    testing_scores = []
    