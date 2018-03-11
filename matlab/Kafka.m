disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
C_Kafka= GetData('Raspberry','C','Kafka',detected_error, doPlotC);
disp('end C')
Java_Kafka= GetData('Raspberry','Java','Kafka',detected_error, doPlotJava);
disp('end Java')
Python_Kafka= GetData('Raspberry','Python','Kafka',detected_error, doPlotPython);
disp('end Python')
Node_Kafka= GetData('Raspberry','Node','Kafka',detected_error, doPlotNode);
disp('end Node')


%PlotData('Raspberry','C','Kafka');
%PlotData('Raspberry','Java','Kafka');
%PlotData('Raspberry','Node','Kafka');
%PlotData('Raspberry','Python','Kafka');


%C_Kafka
%Java_Kafka
%Python_Kafka
%Node_Kafka

disp('BBB');

doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;


C_Kafka= GetData('BeagleBone','C','Kafka',detected_error, doPlotC);
disp('end C')
Java_Kafka= GetData('BeagleBone','Java','Kafka',detected_error, doPlotJava);
disp('end Java')
Python_Kafka= GetData('BeagleBone','Python','Kafka',detected_error, doPlotPython);
disp('end Python')
Node_Kafka= GetData('BeagleBone','Node','Kafka',detected_error, doPlotNode);
disp('end Node')

%PlotData('BeagleBone','C','Kafka');
%PlotData('BeagleBone','Java','Kafka');
%PlotData('BeagleBone','Node','Kafka');
%PlotData('BeagleBone','Python','Kafka');