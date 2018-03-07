function [ data ] = GetData( platform, lang, protocol, offset, doPlot )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
data=ones(3,5);
for i = 1:5
    [t, m, A, t2, ret, t3, avg, energy] = ReadFileData(platform,lang,protocol,i,offset);
    data(1,i)=avg(1);
    data(2,i)=avg(3);
    data(3,i)=energy;
    if doPlot
        plot(t,m*100,t,A,t2,ret,t3,avg);
        waitforbuttonpress
    end

end