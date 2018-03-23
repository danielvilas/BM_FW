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

tablehead= ["\\begin{table}[h]\n"];
tablehead= [tablehead  "	\\caption{%s}\n"];

tableend=["	\\label{tab:%s}\n"];
tableend= [tableend  "\\end{table}\n"];

fprintf(fid,head);
fprintf(fid,tablehead,"Raspberry Kafka Comparative");
fbf_PrintTextTable([rpi_C_Kafka rpi_Java_Kafka rpi_Node_Kafka rpi_Python_Kafka],fid);
fprintf(fid,tableend,"rpiKafka");
fprintf(fid,tablehead,"BeagleBone Kafka Comparative");
fbf_PrintTextTable([bbb_C_Kafka bbb_Java_Kafka bbb_Node_Kafka bbb_Python_Kafka],fid);
fprintf(fid,tableend,"bbbKafka");

fprintf(fid,tablehead,"Raspberry/BeagleBone Kafka Comparative");
fbf_PrintTextTable([rpi_C_Kafka rpi_Java_Kafka rpi_Node_Kafka rpi_Python_Kafka;bbb_C_Kafka bbb_Java_Kafka bbb_Node_Kafka bbb_Python_Kafka],fid);
fprintf(fid,tableend,"bbbKafka");


fclose(fid);