disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
rpi_C_Kafka= fbf_GetData('Raspberry','C','Kafka',detected_error, doPlotC);
disp('end C')
rpi_Java_Kafka= fbf_GetData('Raspberry','Java','Kafka',detected_error, doPlotJava);
disp('end Java')
rpi_Python_Kafka= fbf_GetData('Raspberry','Python','Kafka',detected_error, doPlotPython);
disp('end Python')
rpi_Node_Kafka= fbf_GetData('Raspberry','Node','Kafka',detected_error, doPlotNode);
disp('end Node')


%fbf_PlotMemData('Raspberry','C','Kafka');
%PlotData('Raspberry','Java','Kafka');
%PlotData('Raspberry','Node','Kafka');
%PlotData('Raspberry','Python','Kafka');

disp('BBB');

doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;


bbb_C_Kafka= fbf_GetData('BeagleBone','C','Kafka',detected_error, doPlotC);
disp('end C')
bbb_Java_Kafka= fbf_GetData('BeagleBone','Java','Kafka',detected_error, doPlotJava);
disp('end Java')
bbb_Python_Kafka= fbf_GetData('BeagleBone','Python','Kafka',detected_error, doPlotPython);
disp('end Python')
bbb_Node_Kafka= fbf_GetData('BeagleBone','Node','Kafka',detected_error, doPlotNode);
disp('end Node')

%PlotData('BeagleBone','C','Kafka');
%PlotData('BeagleBone','Java','Kafka');
%PlotData('BeagleBone','Node','Kafka');
%PlotData('BeagleBone','Python','Kafka');


fbf_PrintData(rpi_C_Kafka);
fbf_PrintData(rpi_Java_Kafka);
fbf_PrintData(rpi_Python_Kafka);
fbf_PrintData(rpi_Node_Kafka);

fbf_PrintData(bbb_C_Kafka);
fbf_PrintData(bbb_Java_Kafka);
fbf_PrintData(bbb_Python_Kafka);
fbf_PrintData(bbb_Node_Kafka);