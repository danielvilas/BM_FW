function [] = fbf_PrintTextTable( data, titleFormat, output, myFields )
%FBF_PRINTTEXTTABLE FogBenchmarkFramework LatexTable
%   prints the data generated by fbf_GetData();

if exist('titleFormat','var')==0
	titleFormat={'platform' 'lang' 'protocol'};
end

if exist('output','var')==0
	output=1;
end

if exist('fields','var')==0
	myFields=["memAvg";'maxMem';'cpuAvg';'maxCpu'; ...
            'outAvg';'inAvg';'preCurrentAvg';...
            'runCurrentAvg';'energyAvg';...
            'mAmpsSAvg';'mAmpsHAvg';'time';'timeStr';...
            'cycleTime';'powerEstimation'];
end

if isa(data, 'struct')==1
	data=[data];
end

maxC = size(data,2);
maxD = size(data,1);

begin='\begin{tabular}{ | c';
title{maxD}=[];
[names, formats] = fbf_GetPrintNamesFormat();			
fs=size(myFields,1);

dataStr{fs,maxD}=[];
			
for i = 1 : maxC
    begin=sprintf("%s | c",begin);
	for j = 1: maxD
		cData = data(j,i);
        strTitle = cData.(titleFormat{1});
        for it=2:length(titleFormat)
            strTitle=sprintf("%s-%s",strTitle,cData.(titleFormat{it}));
        end
		title{j}=sprintf("%s&%s",title{j},strTitle); 
    
		for k = 1: fs
			str1=dataStr{k,j};
            field=char(myFields(k,:));
			value=cData.(field);
			format = formats.(field);
			str2=sprintf(format,str1,value);
			dataStr{k,j}=str2;
		end
	end
	
end

fprintf(output,"%s | } \n \\hline ",begin);

for i = 1 : maxD
	fprintf(output,"\n  %s \\\\",title{i});
end
fprintf(output," \\hline \n");

for i = 1 : fs
    field=char(myFields(i,:));
	name = names.(field);
	fprintf(output,"%s %s \\\\ ",name ,dataStr{i,1});
	for j = 2 : maxD
		fprintf(output,"\n %s \\\\ ",dataStr{i,j});
	end
	fprintf(output," \\hline \n");
	
end

fprintf(output,"\\end{tabular}\n");
end

