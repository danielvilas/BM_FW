function [ data ] = GetData( platform, lang, protocol, offset, doPlot )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
data=ones(3,5);
memAvg=0;
cpuAvg=0;
outAvg=0;
inAvg=0;
maxMem=0;
maxCpu=0;
for i = 1:5
    [t, m, A, t2, ret, t3, avg, energy] = ReadFileData(platform,lang,protocol,i,offset);
    data(1,i)=avg(1);
    data(2,i)=avg(3);
    data(3,i)=energy;
    if doPlot
        plot(t,m*100,t,A,t2,ret,t3,avg);
        waitforbuttonpress
    end
    [ time,  cpu,  dcpu,  mem, out, in ] = ReadData(platform, lang, protocol,i);
    memAvg=memAvg + sum(mem/size(time,1));
    maxMem=maxMem + max(mem);
    cpuAvg=cpuAvg + sum(cpu)/size(time,1);
    maxCpu=maxCpu + max(cpu);
    %maxCpu=max([maxCpu; cpu]);
    outAvg=outAvg+sum(out);
    inAvg=inAvg+sum(in);
end

memAvg=memAvg/i;
maxMem=maxMem/i;
cpuAvg=cpuAvg/i;
maxCpu=maxCpu/i;
outAvg=outAvg/i;
inAvg=inAvg/i;
preCurrentAvg=sum(data(1,:))/i;
runCurrentAvg=sum(data(2,:))/i;
energyAvg=sum(data(3,:))/i;
time=t3(4)-t3(3);


fprintf("%s-%s-%s stats:\n",platform, lang, protocol);
fprintf("\tMemAvg: %f KB\n",memAvg);
fprintf("\tMemMax: %f KB\n",maxMem);
fprintf("\tCpuAvg: %f %%\n",cpuAvg);
fprintf("\tCpuMax: %f %%\n",maxCpu);
fprintf("\tOut: %f KB\n",outAvg);
fprintf("\tIn: %f KB\n",inAvg);
fprintf("\tPre: %f mAmps\n",preCurrentAvg);
fprintf("\tRun: %f mAmps\n",runCurrentAvg);
fprintf("\tEnergy: %f Jouls\n",energyAvg);
fprintf("\tTime: %f ms\n",time);





