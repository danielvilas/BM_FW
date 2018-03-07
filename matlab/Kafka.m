doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

detected_error=0; %we have found 5mv of error in the RP

C_Kafka= GetData('Raspberry','C','Kafka',detected_error, doPlotC);
disp('end C')

Java_Kafka= GetData('Raspberry','Java','Kafka',detected_error, doPlotJava);
disp('end Java')

Python_Kafka= GetData('Raspberry','Python','Kafka',detected_error, doPlotPython);
disp('end Python')

Node_Kafka= GetData('Raspberry','Node','Kafka',detected_error, doPlotNode);
disp('end Python')

C_Kafka
Java_Kafka
Python_Kafka
Node_Kafka