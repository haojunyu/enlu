This is a package of the ENLU solution from Shanghai.
Please use it under Linux.

The structure of the folder is as follows:
--for_builing: the libs, head files, makefile and an example of the code necessary to build the ENLU_Test file.
--model: model files needed for ENLU_Test.
--results: where the result files (before and after evaluation) are directed (at least by default).
--test_sets: the input to the ENLU_Test.
--tools: libs and executable files for ENLU_Test and Evaluator, also a timeLog.txt file recording the latencies.
--runthis.sh: a bash script that runs the whole process of decoding and evaluation.

################     Q&As     ###############
Q: Are there any prerequisites for the system?
A: For the ENLU_Test, you need nothing additional. But for the Evaluator, you should install numpy and matplotlib.
	<numpy>
	e.g. Ubuntu: sudo apt-get install python-numpy
	<matplotlib>
	e.g. Ubuntu : sudo apt-get install python-matplotlib

Q: I know little about the system. What to do first?
A: Run the runthis.sh file. It will test the test2.txt file and do the evaluation of the performance for you.

Q: How can I change the test set?
A: Modify the input variable in the runthis.sh file. The default test2.txt is a small test set for you to play around.
You can change it to test.txt which is a larger test set with more than 80k cases. 
You can also change the output variable to redirect the output of the ENLU system. 
The performance report will be in the same folder of the output.

Q: Are there results already available?
A: Yes. You can check the result-large.txt, result-small.txt and their corresponding folders of performance reports in the "results"folder.

Q: How can I build my own project with the ENLU library?
A: In the for_builing folder, there are all the necessary files: 
----the library: libhybrid_nlu.2.0.0.so 
----the head files: ENLU_API.h, ENLU_Constants.h and ENLU_data_struct.h
----Our main.cpp that calls the lib and generates the ENLU_Test executable
----the makefile: test.mk 
The default files will build the ENLU_Test file used in the tools folder.
You can also modify the main.cpp and the test.mk for your own needs.