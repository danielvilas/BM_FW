function [ data_out] = fbf_FillPowerEstimation( data, cycles, stdPeriod )
%FBF_FILLPOWERESTIMATION Fills the estimation fields
%   Calculate the cycle time and the energy used in an hour of exectuion
%   input the struct returned by getDataS, the number of cycles, and the
%   period in seconds

data.cycleTime = data.time/cycles;
%ECycle=EProcess + EWait;
%EProcess (mAs) = CycleTime(s) * CurrentRunning
%EWait (mAs) = (stdPeriod - CycleTime) * Current Wait
eProcess= data.runCurrentAvg*data.cycleTime/1000;
eWait= data.preCurrentAvg*(stdPeriod - data.cycleTime/1000);
eCycle= eProcess + eWait;

%EHour(mAh) = ECycle(mAh)*3600/stdPeriod;
data.powerEstimation=eCycle/3600*3600/stdPeriod;
data_out=data;
end

