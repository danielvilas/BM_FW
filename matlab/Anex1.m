%load all

if exist('rpi_Java_Kafka')==0
  Kafka
end
disp('Kafka OK')

if exist('rpi_Java_Mqtt')==0
  Mqtt
end
disp('Mqtt OK')

if exist('rpi_Java_Rest')==0
  Rest
end
disp('Rest OK')

if exist('rpi_Java_Soap')==0
  Soap
end
disp('Soap OK')

fid = fopen('A1_99_01_AnexI.tex','w');

head= "%% !TeX encoding = UTF-8\n";
head= [head  "%% !TeX spellcheck = en_GB\n"];
head= [head  "%% !TeX root = A1_MethodMeasureEfficenciFogComputing.tex\n"];
head= [head  "\\section*{Annex I - Performance per Protocol}\n"];
head= join(head);

tablehead= "\\begin{table}[h]\n";
tablehead= [tablehead  "	\\caption{%s}\n"];
tablehead=join(tablehead);

tableend="	\\label{tab:%s}\n";
tableend= [tableend  "\\end{table}\n"];
tableend=join(tableend);

fprintf(fid,head);

%fprintf(fid,tablehead,"Raspberry Kafka Comparative");
%fbf_PrintTextTable([rpi_C_Kafka rpi_Java_Kafka rpi_Node_Kafka rpi_Python_Kafka],fid);
%fprintf(fid,tableend,"rpiKafka");
%fprintf(fid,tablehead,"BeagleBone Kafka Comparative");
%fbf_PrintTextTable([bbb_C_Kafka bbb_Java_Kafka bbb_Node_Kafka bbb_Python_Kafka],fid);
%fprintf(fid,tableend,"bbbKafka");

fprintf(fid,tablehead,"Raspberry/BeagleBone Kafka Comparative");
fbf_PrintTextTable([rpi_C_Kafka rpi_Java_Kafka rpi_Node_Kafka rpi_Python_Kafka;bbb_C_Kafka bbb_Java_Kafka bbb_Node_Kafka bbb_Python_Kafka],fid);
fprintf(fid,tableend,"bbbKafka");

fprintf(fid,tablehead,"Raspberry/BeagleBone Mqtt Comparative");
fbf_PrintTextTable([rpi_C_Mqtt rpi_Java_Mqtt rpi_Node_Mqtt rpi_Python_Mqtt;bbb_C_Mqtt bbb_Java_Mqtt bbb_Node_Mqtt bbb_Python_Kafka],fid);
fprintf(fid,tableend,"bbbKafka");

fprintf(fid,tablehead,"Raspberry/BeagleBone Rest Comparative");
fbf_PrintTextTable([rpi_C_Rest rpi_Java_Rest rpi_Node_Rest rpi_Python_Rest;bbb_C_Rest bbb_Java_Rest bbb_Node_Rest bbb_Python_Kafka],fid);
fprintf(fid,tableend,"bbbKafka");

fprintf(fid,tablehead,"Raspberry/BeagleBone Soap Comparative");
fbf_PrintTextTable([rpi_C_Soap rpi_Java_Soap rpi_Node_Soap rpi_Python_Soap;bbb_C_Soap bbb_Java_Soap bbb_Node_Soap bbb_Python_Kafka],fid);
fprintf(fid,tableend,"bbbKafka");

fclose(fid);