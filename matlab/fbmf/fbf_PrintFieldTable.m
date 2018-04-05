function [ ] = fbf_PrintFieldTable( field, cols, rows, cells, data, fid)
%FBF_PRINTFIELDTABLE Summary of this function goes here
%   Detailed explanation goes here
field = char(field);
if exist('fid','var')==0
	fid=1;
end
[dataTab, nCols, nRows, nCells ] = fbf_TabulateData( data, cols, rows, cells);

[names, formats] = fbf_GetPrintNamesFormat();

fieldName = names.(field);
fieldFormat =formats.(field);

%tabData
fprintf(fid,"\\begin{tabular}{ | c");
for ic=1:nCols
    fprintf(fid," | c");
end
fprintf(fid," | } \n\\hline\n%s ",fieldName);
for ic=1:nCols
    fprintf(fid," & %s",cols(ic));
end
fprintf(fid," \\\\ \\hline \n");

for ir = 1:nRows
    fprintf(fid,"%s ",rows(ir));
    for icc = 1:nCells
        for ic= 1:nCols
            value = dataTab(ir,ic,icc).(field);
            fprintf(fid,fieldFormat," ",value);
        end
        fprintf(fid,"\\\\ \n");
    end
    fprintf(fid," \\hline \n");
end
fprintf(fid,"\\end{tabular}\n");
end
