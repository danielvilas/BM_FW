disp('Rpi');
doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;

close all;
detected_error=0;
%rpi_C_Mqtt= fbf_GetData('Raspberry','C','Mqtt',detected_error, doPlotC);
disp('end C')
rpi_Java_Mqtt= fbf_GetData('Raspberry','Java','Mqtt',detected_error, doPlotJava);
disp('end Java')
rpi_Python_Mqtt= fbf_GetData('Raspberry','Python','Mqtt',detected_error, doPlotPython);
disp('end Python')
rpi_Node_Mqtt= fbf_GetData('Raspberry','Node','Mqtt',detected_error, doPlotNode);
disp('end Node')


%fbf_PlotMemData('Raspberry','C','Mqtt');
%PlotData('Raspberry','Java','Mqtt');
%PlotData('Raspberry','Node','Mqtt');
%PlotData('Raspberry','Python','Mqtt');

disp('BBB');

doPlotC=false;
doPlotJava=false;
doPlotPython=false;
doPlotNode=false;


%bbb_C_Mqtt= fbf_GetData('BeagleBone','C','Mqtt',detected_error, doPlotC);
disp('end C')
%bbb_Java_Mqtt= fbf_GetData('BeagleBone','Java','KafMqttka',detected_error, doPlotJava);
disp('end Java')
%bbb_Python_Mqtt= fbf_GetData('BeagleBone','Python','Mqtt',detected_error, doPlotPython);
disp('end Python')
%bbb_Node_Mqtt= fbf_GetData('BeagleBone','Node','Mqtt',detected_error, doPlotNode);
disp('end Node')

%PlotData('BeagleBone','C','Mqtt');
%PlotData('BeagleBone','Java','Mqtt');
%PlotData('BeagleBone','Node','Mqtt');
%PlotData('BeagleBone','Python','Mqtt');


%fbf_PrintData(rpi_C_Mqtt);
fbf_PrintData(rpi_Java_Mqtt);
fbf_PrintData(rpi_Python_Mqtt);
fbf_PrintData(rpi_Node_Mqtt);

%fbf_PrintData(bbb_C_Mqtt);
%fbf_PrintData(bbb_Java_Mqtt);
%fbf_PrintData(bbb_Python_Mqtt);
%fbf_PrintData(bbb_Node_Mqtt);