import treePlotter
import trees
import pandas

if __name__ == '__main__':
    # fr = open('lenses.txt')
    # fr1 = open('test.txt')
    #
    # lenses = [inst.strip().split('\t') for inst in fr.readlines()]
    # lensesLabels = ['age', 'prescript', 'astigmatic', 'tearRate']
    # lensesTree = trees.createTree(lenses, lensesLabels)
    # label = ['no lenses', 'soft', 'no lenses', 'hard', 'no lenses']
    myDat, labels = trees.createDataSet()
    myTree = treePlotter.retrieveTree()

    treePlotter.createPlot(lensesTree)