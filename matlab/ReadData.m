function [ time, cpu, dcpu, mem, oct_out, oct_in ] = ReadData( platform, lang, protocol, exec )
%READDATA Summary of this function goes here
%   Detailed explanation goes here

file = sprintf('recorded_data/%s/%s/%s/%s_%s_MEM_%i.txt',platform,lang,protocol,upper(lang),upper(protocol),exec);
fprintf('load: %s\n', file);

all=dlmread(file,';',1,0);
time = all(:,1);% currentTs, ms of system clock
time =time -time(1); % move to 0

tTime= all(:,2); % total_time, total ticks passed from start
cpu = all(:,3)+all(:,4); % cpu, user_time + sys_time, ticks used by the app from start
%ticks in tTime and cpu are accumulative

%Ticks betwen samples 
dcpu = cpu -[cpu(1); cpu(1:size(cpu)-1)];%dcpu(i)=cpu(i)-cpu(i-1)
dTime = tTime -[tTime(1); tTime(1:size(tTime)-1)]; %dTime(i) = tTime(i)-tTime(i-1)

cpu = (cpu ./ tTime) *100;
dcpu=(dcpu ./ dTime) *100;
if isnan(cpu(1))
    cpu(1)=0;
    dcpu(1)=0;
end

mem = all(:,5)/1024; %in Kb

%Network in Kb
oct_out=all(:,7)/1024;%total (accumlated) octets sent
oct_in=all(:,6)/1024;%total (accumlated) octets receivced

%Octets sent per samples ret_x(i)=x(i)-x(i-1)
oct_in=oct_in - [oct_in(1); oct_in(1:size(tTime)-1)];
oct_out=oct_out - [oct_out(1); oct_out(1:size(tTime)-1)];
end

