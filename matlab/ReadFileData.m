function [ t, m, A, t2, ret, t3, avg, energy ] = ReadFileData( platform, lang, protocol, exec, offset);
%READFILEMATH Summary of this function goes here
%   Detailed explanation goes here
file = sprintf('recorded_data/%s/%s/%s/%s_%s_%i.txt',platform,lang,protocol,upper(lang),upper(protocol),exec);
fprintf('load: %s\n', file);
M=csvread(file,0,0);
t=M(:,1);
C1=M(:,2)*(1/0.6-0.5);%*4.9/4.2; %from Rp code
C2=M(:,3)*(1/0.6-0.5);%*4.9/4.2; %from Rp code
%A=M(:,4);
m=M(:,5);

A=(C1-C2)/0.1*1000+offset; %To MilliAmps
Amps=A/1000; %To Amps

t=t-t(1); %0 offset
max=size(t,1);
state = m(1);

avg=0;
cnt=0;
t2=[t(1)];
ret=[A(1)];

energy=0;
energyData=[0];

for i = 1:max
    nState=m(i);
    if nState == state
        avg= avg + A(i);
        cnt=cnt+1;
        if isnan(avg)
         disp('nan')
        end
        if i>1
            dt=(t(i)-t(i-1))/1000; %t is in milliseconds
            energy= energy + (Amps(i)+Amps(i-1))/2*(dt)*C2(i);%energy in Jouls
        end
    else
        t2=[t2 t(i)];
        tmp =avg/cnt;
        if isnan(tmp)
            disp('NaN')
        end
        ret=[ret tmp ];
        avg=A(i);
        cnt=1;
        if i>1
            energyData=[energyData energy ];
            energy=0;
        end
    end
    state=nState;
end
t2=[t2 t(i)];
ret=[ret avg/cnt];
ret(1)=ret(2);

max=size(ret,2);
avg=sum(ret(3:max-1))/max;

t3=[t(1) t2(2) t2(2) t2(max-1) t2(max-1) t2(max)];
avg=[ret(1) ret(1) avg avg ret(max) ret(max)];


energyData=[energyData energy ];
energy=sum(energyData(3:max-1));
end

