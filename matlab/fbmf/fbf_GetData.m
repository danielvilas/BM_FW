function [ data ] = fbf_GetData( platform, lang, protocol, offset, doPlot )
%FBF_GETDATA FogBenchmarkFramework Get Data
%   Read the files and builds the infor for the specified platform,
%   language and protocol
data=ones(4,5);
memAvg=0;
cpuAvg=0;
outAvg=0;
inAvg=0;
maxMem=0;
maxCpu=0;
for i = 1:5
    [t, m, A, t2, ret, t3, avg, energy, mAmpsS] = fbf_ReadPowerData(platform,lang,protocol,i,offset);
    data(1,i)=avg(1);
    data(2,i)=avg(3);
    data(3,i)=energy;
    data(4,i)=mAmpsS;
    if doPlot
        plot(t,m*100,t,A,t2,ret,t3,avg);
        waitforbuttonpress
    end
    [ time,  cpu,  dcpu,  mem, out, in ] = fbf_ReadMemData(platform, lang, protocol,i);
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
mAmpsSAvg=sum(data(4,:))/i;
time=t3(4)-t3(3);

millis = mod(time, 1000);
t = fix(time/1000);
seconds = mod(t,60);
minutes=fix(t/60);

timeStr = sprintf("%im %is %ims",minutes,seconds,millis);

data = struct('platform',platform,'lang',lang,'protocol',protocol,'memAvg', ... 
                memAvg,'maxMem',maxMem,'cpuAvg',cpuAvg,'maxCpu',maxCpu, ...
            'outAvg',outAvg,'inAvg',inAvg,'preCurrentAvg',preCurrentAvg,...
            'runCurrentAvg',runCurrentAvg,'energyAvg',energyAvg,...
            'mAmpsSAvg',mAmpsSAvg,'mAmpsHAvg',mAmpsSAvg/3600,'time',time, 'timeStr',timeStr);

end

