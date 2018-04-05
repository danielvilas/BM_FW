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

fid = fopen('A1_99_01_AnexI.tex','w');

head= "%% !TeX encoding = UTF-8\n";
head= [head  "%% !TeX spellcheck = en_GB\n"];
head= [head  "%% !TeX root = A1_MethodMeasureEfficenciFogComputing.tex\n"];
head= [head  "\\section*{Annex I - Interesting Data}\n"];
head= join(head);

tablehead= "\\begin{table}[h]\n";
tablehead= [tablehead  "	\\caption{%s}\n"];
tablehead=join(tablehead);

tableend="	\\label{tab:%s}\n";
tableend= [tableend  "\\end{table}\n"];
tableend=join(tableend);

figure=join(["\\begin{figure}[H]\n" ...
	"\t\\centering\n" ...
	"\t\\includegraphics[width=\\textwidth]{images/%s}\n" ...
	"\t\\caption{%s}\n" ...
	"\t\\label{fig:%s}\n" ...
    "\\end{figure}\n"]);

fprintf(fid,head);

names  = fbf_GetPrintNamesFormat();
%for i=1:size(fnames)
%    fieldName= names.(fnames{i});
%    title = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
%    fprintf(fid,tablehead,title);
%    fbf_PrintFieldTable(fnames{i},["C" 'Java' 'Node' 'Python'],["Kafka" 'Mqtt' 'Rest' 'Soap'],["Raspberry" 'BeagleBone'],data,fid);
%    fprintf(fid,tableend,fnames{i});
%end

%            'outAvg',outAvg,'inAvg',inAvg,'preCurrentAvg',preCurrentAvg,...
%            'runCurrentAvg',runCurrentAvg,'energyAvg',energyAvg,...
%            'mAmpsSAvg',mAmpsSAvg,'mAmpsHAvg',mAmpsHAvg,'time',time,...
%            'timeStr',timeStr,'cycleTime',time,'powerEstimation',powerEstimationHour;

printTable('memAvg',names,fid, tablehead, tableend,data);
printTable('maxMem',names,fid, tablehead, tableend,data);
fprintf(fid,figure,"memAvg","Memory Consumption","memAvg");
fprintf(fid,"\n\\newpage\n\n");

printTable('outAvg',names,fid, tablehead, tableend,data);
printTable('inAvg',names,fid, tablehead, tableend,data);
fprintf(fid,figure,"outAvg","Network Consumption","outAvg");
fprintf(fid,"\n\\newpage\n\n");

printTable('cpuAvg',names,fid, tablehead, tableend,data);
printTable('maxCpu',names,fid, tablehead, tableend,data);
fprintf(fid,figure,"cpuAvg","Cpu Consumption","cpuAvg");
fprintf(fid,"\n\\newpage\n\n");

printTable('preCurrentAvg',names,fid, tablehead, tableend,data);
printTable('runCurrentAvg',names,fid, tablehead, tableend,data);
fprintf(fid,figure,"preCurrentAvg","Steady Current","preCurrentAvg");
fprintf(fid,figure,"runCurrentAvg","Run Current","runCurrentAvg");
fprintf(fid,"\n\\newpage\n\n");

printTable('mAmpsHAvg',names,fid, tablehead, tableend,data);
printTable('powerEstimation',names,fid, tablehead, tableend,data);
fprintf(fid,figure,"mAmpsHAvg","Comsumpted Power during the test","mAmpsHAvg");
fprintf(fid,figure,"powerEstimation","Estimated Power for a running hour (1 message every 8 seconds)","powerEstimation");
fprintf(fid,"\n\\newpage\n\n");

printTable('timeStr',names,fid, tablehead, tableend,data);
printTable('cycleTime',names,fid, tablehead, tableend,data);
fprintf(fid,figure,"cycleTime","One Cycle time","cycleTime");
fprintf(fid,"\n\\newpage\n\n");

fclose(fid);



function [] = printTable(field,names,fid, tablehead, tableend,data)
fieldName= names.(field);
title = sprintf("Raspberry/BeagleBone %s Comparative", fieldName);
fprintf(fid,tablehead,title);
fbf_PrintFieldTable(field,["C" 'Java' 'Node' 'Python'],["Kafka" 'Mqtt' 'Rest' 'Soap'],["Raspberry" 'BeagleBone'],data,fid);
fprintf(fid,tableend,field);
end