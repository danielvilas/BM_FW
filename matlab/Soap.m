disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
rpi_C_Soap= fbf_GetData('Raspberry','C','Soap',detected_error, doPlotC);
rpi_C_Soap = fbf_FillPowerEstimation(rpi_C_Soap,2520,8);
disp('end C')
rpi_Java_Soap= fbf_GetData('Raspberry','Java','Soap',detected_error, doPlotJava);
rpi_Java_Soap = fbf_FillPowerEstimation(rpi_Java_Soap,2520,8);
disp('end Java')
rpi_Python_Soap= fbf_GetData('Raspberry','Python','Soap',detected_error, doPlotPython);
rpi_Python_Soap = fbf_FillPowerEstimation(rpi_Python_Soap,2520,8);
disp('end Python')
rpi_Node_Soap= fbf_GetData('Raspberry','Node','Soap',detected_error, doPlotNode);
rpi_Node_Soap = fbf_FillPowerEstimation(rpi_Node_Soap,2520,8);
disp('end Node')


%fbf_PlotMemData('Raspberry','C','Soap');
%PlotData('Raspberry','Java','Soap');
%PlotData('Raspberry','Node','Soap');
%f

disp('BBB');

doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;


bbb_C_Soap= fbf_GetData('BeagleBone','C','Soap',detected_error, doPlotC);
bbb_C_Soap = fbf_FillPowerEstimation(bbb_C_Soap,2520,8);
disp('end C')
bbb_Java_Soap= fbf_GetData('BeagleBone','Java','Soap',detected_error, doPlotJava);
bbb_Java_Soap = fbf_FillPowerEstimation(bbb_Java_Soap,2520,8);
disp('end Java')
bbb_Python_Soap= fbf_GetData('BeagleBone','Python','Soap',detected_error, doPlotPython);
bbb_Python_Soap = fbf_FillPowerEstimation(bbb_Python_Soap,2520,8);
disp('end Python')
bbb_Node_Soap= fbf_GetData('BeagleBone','Node','Soap',detected_error, doPlotNode);
bbb_Node_Soap = fbf_FillPowerEstimation(bbb_Node_Soap,2520,8);
disp('end Node')

%PlotData('BeagleBone','C','Soap');
%PlotData('BeagleBone','Java','Soap');
%PlotData('BeagleBone','Node','Soap');
%PlotData('BeagleBone','Python','Soap');


fbf_PrintData(rpi_C_Soap);
fbf_PrintData(rpi_Java_Soap);
fbf_PrintData(rpi_Python_Soap);
fbf_PrintData(rpi_Node_Soap);

fbf_PrintData(bbb_C_Soap);
fbf_PrintData(bbb_Java_Soap);
fbf_PrintData(bbb_Python_Soap);
fbf_PrintData(bbb_Node_Soap);