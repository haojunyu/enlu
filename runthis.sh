#cd ENLU_Package/tools
# set the input and output of the ENLU a

testfile=$1
modelfile=ENLU_Package/$3
resultfile=$4 
echo '==========='
echo $testfile $modelfile $resultfile
if [ $# -eq 4 ]
then
./ENLU_Test -c $2 -m $modelfile -r $resultfile $testfile
else
./ENLU_Test -c $2 -m $modelfile -u $5 -r $resultfile $testfile
fi

######to run the Evaluator.pyc, you need to install two libs: matplotlib and numpy

##numpy
#e.g. Ubuntu: sudo apt-get install python-numpy
##matplotlib
#e.g. Ubuntu : sudo apt-get install python-matplotlib

python ./Evaluator.pyc $resultfile
