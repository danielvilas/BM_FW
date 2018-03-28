disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
rpi_C_Kafka= fbf_GetData('Raspberry','C','Kafka',detected_error, doPlotC);
rpi_C_Kafka = fbf_FillPowerEstimation(rpi_C_Kafka,2520,8);
disp('end C')
rpi_Java_Kafka= fbf_GetData('Raspberry','Java','Kafka',detected_error, doPlotJava);
rpi_Java_Kafka = fbf_FillPowerEstimation(rpi_Java_Kafka,2520,8);
disp('end Java')
rpi_Python_Kafka= fbf_GetData('Raspberry','Python','Kafka',detected_error, doPlotPython);
rpi_Python_Kafka = fbf_FillPowerEstimation(rpi_Python_Kafka,2520,8);
disp('end Python')
rpi_Node_Kafka= fbf_GetData('Raspberry','Node','Kafka',detected_error, doPlotNode);
rpi_Node_Kafka = fbf_FillPowerEstimation(rpi_Node_Kafka,2520,8);
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
bbb_C_Kafka = fbf_FillPowerEstimation(bbb_C_Kafka,2520,8);
disp('end C')
bbb_Java_Kafka= fbf_GetData('BeagleBone','Java','Kafka',detected_error, doPlotJava);
bbb_Java_Kafka = fbf_FillPowerEstimation(bbb_Java_Kafka,2520,8);
disp('end Java')
bbb_Python_Kafka= fbf_GetData('BeagleBone','Python','Kafka',detected_error, doPlotPython);
bbb_Python_Kafka = fbf_FillPowerEstimation(bbb_Python_Kafka,2520,8);
disp('end Python')
bbb_Node_Kafka= fbf_GetData('BeagleBone','Node','Kafka',detected_error, doPlotNode);
bbb_Node_Kafka = fbf_FillPowerEstimation(bbb_Node_Kafka,2520,8);
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