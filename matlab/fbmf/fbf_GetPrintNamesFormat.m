function [ names, formats ] = fbf_GetPrintNamesFormat( )
%FBF_GETPRINTNAMESFORMAT Summary of this function goes here
%   Detailed explanation goes here
memAvg='MemAvg(KB)';
maxMem='MemMax(KB)';
cpuAvg='CpuAvg(\%)';
maxCpu='CpuMax(\%)';
outAvg='Out(KB)';
inAvg='In(KB)';
preCurrentAvg='Steady(mA)';
runCurrentAvg='Running(mA)';
energyAvg='Energy(Jouls)';
mAmpsSAvg='Energy(mAs)';
mAmpsHAvg='Energy(mAh)';
time='Time(ms)';
timeStr='Time';
cycleTime='Cycle Time (ms)';
powerEstimation='Power Est(mAh)';

names = struct('memAvg', memAvg,'maxMem',maxMem,'cpuAvg',cpuAvg,'maxCpu',maxCpu, ...
            'outAvg',outAvg,'inAvg',inAvg,'preCurrentAvg',preCurrentAvg,...
            'runCurrentAvg',runCurrentAvg,'energyAvg',energyAvg,...
            'mAmpsSAvg',mAmpsSAvg,'mAmpsHAvg',mAmpsHAvg,'time',time,...
            'timeStr',timeStr,'cycleTime',cycleTime,'powerEstimation',powerEstimation); 
defformat="%s& %f";
formats = struct('memAvg', defformat,'maxMem',defformat,'cpuAvg',defformat,'maxCpu',defformat, ...
            'outAvg',defformat,'inAvg',defformat,'preCurrentAvg',defformat,...
            'runCurrentAvg',defformat,'energyAvg',defformat,...
            'mAmpsSAvg',defformat,'mAmpsHAvg',defformat,'time',"%s& %i",...
            'timeStr',"%s& %s",'cycleTime',defformat,'powerEstimation', defformat); 

end

