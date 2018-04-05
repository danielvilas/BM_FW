function [ dataTab, nCols, nRows, nCells ] = fbf_TabulateData( data, cols, rows, cells)
%FBF_TABULATEDATA Summary of this function goes here
%   Detailed explanation goes here

nCols = size(cols,2);
nRows = size(rows,2);
nCells= size(cells,2);

dataTab= repmat(data(1),nCols,nRows,nCells);
for ic=1:nCols
    for ir=1:nRows
        for icc =1:nCells
            cell= fbf_pft_findByAllData(data,cols(ic),rows(ir),cells(icc));
            if isa(cell, 'struct')==0
                error('Not found ');
            end
            dataTab(ir,ic,icc)=cell;
        end
    end
end
end

function [out] =fbf_pft_findByAllData(data, col, row, cell)
n = size(data,2);
for i=1:n
    if ~fbf_pft_isDataOf(data(i),col)
        continue;
    end
    if ~fbf_pft_isDataOf(data(i),row)
        continue;
    end
    if ~fbf_pft_isDataOf(data(i),cell)
        continue;
    end
    out=data(i);
    return;
end
out= -1;
return
end

function [out] = fbf_pft_isDataOf(data, name)
out=0;
if strcmp(data.platform,name)
    out=1;
elseif strcmp(data.lang,name) 
    out=1;
elseif strcmp(data.protocol,name)
    out=1;
end
end