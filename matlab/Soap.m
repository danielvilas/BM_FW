disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
rpi_C_Soap= fbf_GetData('Raspberry','C','Soap',detected_error, doPlotC);
disp('end C')
rpi_Java_Soap= fbf_GetData('Raspberry','Java','Soap',detected_error, doPlotJava);
disp('end Java')
rpi_Python_Soap= fbf_GetData('Raspberry','Python','Soap',detected_error, doPlotPython);
disp('end Python')
rpi_Node_Soap= fbf_GetData('Raspberry','Node','Soap',detected_error, doPlotNode);
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
disp('end C')
%bbb_Java_Soap= fbf_GetData('BeagleBone','Java','KafSoapka',detected_error, doPlotJava);
disp('end Java')
%bbb_Python_Soap= fbf_GetData('BeagleBone','Python','Soap',detected_error, doPlotPython);
disp('end Python')
bbb_Node_Soap= fbf_GetData('BeagleBone','Node','Soap',detected_error, doPlotNode);
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
%fbf_PrintData(bbb_Java_Soap);
%fbf_PrintData(bbb_Python_Soap);
fbf_PrintData(bbb_Node_Soap);