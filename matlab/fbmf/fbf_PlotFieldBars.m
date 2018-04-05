function [ fig, b, l, s ] = fbf_PlotFieldBars( field, cols, rows, cells, data, maxField )
%FBF_PLOTFIELDBARS Summary of this function goes here
%   Detailed explanation goes here

[dataTab, nCols, nRows, nCells ] = fbf_TabulateData( data, cols, rows, cells);

[names, formats] = fbf_GetPrintNamesFormat();

fieldName = names.(field);
fieldFormat =formats.(field);

barLabel={1:nCols*nCells};
barData=zeros(nRows,nCols*nCells);
maxData=zeros(nRows,nCols*nCells);

maxDataExist=exist('maxField','var');


for ic=1:nCols
    for icc=1:nCells
        colindex= (ic-1)*nCells+icc;
        barLabel{colindex}=char(sprintf("%s-%s",char(cols(ic)),char(cells(icc)))); 
        for ir=1:nRows
            barData(ir,colindex)=dataTab(ir,ic,icc).(field);
            if maxDataExist
                maxData(ir,colindex)=dataTab(ir,ic,icc).(maxField);
            end
        end
    end
end
fig=figure();
b=bar(barData);
ylabel(fieldName,'interpreter','latex')
l=legend(barLabel);
xticklabels(rows);

if maxDataExist
    hold on;
    xs=[];
    ys=[];
    for ib=1:length(b)
        xs=[xs (b(ib).XData + b(ib).XOffset)];
        ys=[ys maxData(:,ib)'];    
    end
    yneg=zeros(1,length(ys));
    ypos=zeros(1,length(ys));
    xneg=repmat(0.3/length(b),1,length(ys));
    xpos=repmat(0.3/length(b),1,length(ys));
    
    s = errorbar(xs,ys,xneg,xpos,'horizontal','LineStyle','none', 'Color','r','DisplayName','Max');
    %legend(b);
end

end

