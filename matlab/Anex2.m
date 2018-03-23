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

fid = fopen('A1_99_02_AnexII.tex','w');

head= "%% !TeX encoding = UTF-8\n";
head= [head  "%% !TeX spellcheck = en_GB\n"];
head= [head  "%% !TeX root = A1_MethodMeasureEfficenciFogComputing.tex\n"];
head= [head  "\\section*{Annex II - Performance per Language}\n"];

tablehead= ["\\begin{table}[h]\n"];
tablehead= [tablehead  "	\\caption{%s}\n"];

tableend=["	\\label{tab:%s}\n"];
tableend= [tableend  "\\end{table}\n"];

fprintf(fid,head);

fprintf(fid,tablehead,"Raspberry Java Comparative");
fbf_PrintTextTable([rpi_Java_Kafka rpi_Java_Mqtt rpi_Java_Rest rpi_Java_Soap],fid);
fprintf(fid,tableend,"rpiJava");


fprintf(fid,tablehead,"Raspberry Node Comparative");
fbf_PrintTextTable([rpi_Node_Kafka rpi_Node_Mqtt rpi_Node_Rest rpi_Node_Soap],fid);
fprintf(fid,tableend,"rpiNode");

fprintf(fid,tablehead,"Raspberry Python Comparative");
fbf_PrintTextTable([rpi_Python_Kafka rpi_Python_Mqtt rpi_Python_Rest],fid);
fprintf(fid,tableend,"rpiPython");


fclose(fid);