disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
rpi_C_Rest= fbf_GetData('Raspberry','C','Rest',detected_error, doPlotC);
disp('end C')
rpi_Java_Rest= fbf_GetData('Raspberry','Java','Rest',detected_error, doPlotJava);
disp('end Java')
rpi_Python_Rest= fbf_GetData('Raspberry','Python','Rest',detected_error, doPlotPython);
disp('end Python')
rpi_Node_Rest= fbf_GetData('Raspberry','Node','Rest',detected_error, doPlotNode);
disp('end Node')


%fbf_PlotMemData('Raspberry','C','Rest');
%PlotData('Raspberry','Java','Rest');
%PlotData('Raspberry','Node','Rest');
%PlotData('Raspberry','Python','Rest');

disp('BBB');

doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;


bbb_C_Rest= fbf_GetData('BeagleBone','C','Rest',detected_error, doPlotC);
disp('end C')
bbb_Java_Rest= fbf_GetData('BeagleBone','Java','Rest',detected_error, doPlotJava);
disp('end Java')
%bbb_Python_Rest= fbf_GetData('BeagleBone','Python','Rest',detected_error, doPlotPython);
disp('end Python')
bbb_Node_Rest= fbf_GetData('BeagleBone','Node','Rest',detected_error, doPlotNode);
disp('end Node')

%PlotData('BeagleBone','C','Rest');
%PlotData('BeagleBone','Java','Rest');
%PlotData('BeagleBone','Node','Rest');
%PlotData('BeagleBone','Python','Rest');


fbf_PrintData(rpi_C_Rest);
fbf_PrintData(rpi_Java_Rest);
fbf_PrintData(rpi_Python_Rest);
fbf_PrintData(rpi_Node_Rest);

fbf_PrintData(bbb_C_Rest);
fbf_PrintData(bbb_Java_Rest);
%fbf_PrintData(bbb_Python_Rest);
fbf_PrintData(bbb_Node_Rest);