%load all

if exist('rpi_Java_Kafka','var')==0
  Kafka
end
disp('Kafka OK')

if exist('rpi_Java_Mqtt','var')==0
  Mqtt
end
disp('Mqtt OK')

if exist('rpi_Java_Rest','var')==0
  Rest
end
disp('Rest OK')

if exist('rpi_Java_Soap','var')==0
  Soap
end
disp('Soap OK')

data=[bbb_C_Kafka bbb_C_Mqtt bbb_C_Rest bbb_C_Soap bbb_Java_Kafka ...
    bbb_Java_Mqtt bbb_Java_Rest bbb_Java_Soap bbb_Node_Kafka ...
    bbb_Node_Mqtt bbb_Node_Rest bbb_Node_Soap bbb_Python_Kafka ...
    bbb_Python_Mqtt bbb_Python_Rest bbb_Python_Soap rpi_C_Kafka ...
    rpi_C_Mqtt rpi_C_Rest rpi_C_Soap rpi_Java_Kafka rpi_Java_Mqtt ...
    rpi_Java_Rest rpi_Java_Soap rpi_Node_Kafka rpi_Node_Mqtt ...
    rpi_Node_Rest rpi_Node_Soap rpi_Python_Kafka rpi_Python_Mqtt ...
    rpi_Python_Rest rpi_Python_Soap];

cols=["Java" 'Node' 'Python' 'C'];
rows=["Kafka" 'Mqtt' 'Rest' 'Soap'];
cells=["Raspberry" 'BeagleBone'];


names  = fbf_GetPrintNamesFormat();
close all;



field='memAvg';
[ fig, b, l, s ] = fbf_PlotFieldBars( field, cols, rows, cells, data, 'maxMem');
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'memAvg.png','png')
close(fig);

field='cpuAvg';
[ fig, b, l, s ] = fbf_PlotFieldBars( field, cols, rows, cells, data, 'maxCpu');
%[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'cpuAvg.png','png')
close(fig);

field='outAvg';
[ fig, b, l, s ] = fbf_PlotFieldBars( field, cols, rows, cells, data, 'inAvg');
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
s.DisplayName='In';
s.Color='black';
saveas(fig,'outAvg.png','png')
close(fig);

field='preCurrentAvg';
[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'preCurrentAvg.png','png')
%close(fig);


field='runCurrentAvg';
[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'runCurrentAvg.png','png')
close(fig);


field='mAmpsHAvg';
[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'mAmpsHAvg.png','png')
close(fig);

field='powerEstimation';
[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'powerEstimation.png','png')
close(fig);


field='cycleTime';
[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
saveas(fig,'cycleTime.png','png')
close(fig);



field='runCurrentAvg';
[ fig, b, l ] = fbf_PlotFieldBars( field, cols, rows, cells, data);
fieldName = names.(field);
gTitle = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
title(gTitle,'interpreter','latex');
pos = get(fig, 'Position');
pos=[pos(1:2) 950 264];
set(fig,'Position',pos);
fig.CurrentAxes.Position=[0.05 0.1 0.925 0.8150 ];
l.Location='eastoutside';
hold on;
h1=refline(0,230);
h1.DisplayName='Raspberry Steady Current';
h1.Color='red';
h2=refline(0,130);
h2.DisplayName='BeagleBone Steady Current';
h2.Color='black';
%saveas(fig,'outAvg.png','png')
%close(fig);