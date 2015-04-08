cd tools
# set the input and output of the ENLU a

testfile=../test_sets/test_sub.txt
resultfile=../results/result-model-based.txt 

./ENLU_Test -c 2 -r $resultfile $testfile

######to run the Evaluator.pyc, you need to install two libs: matplotlib and numpy

##numpy
#e.g. Ubuntu: sudo apt-get install python-numpy
##matplotlib
#e.g. Ubuntu : sudo apt-get install python-matplotlib

python ./Evaluator.pyc $resultfile
