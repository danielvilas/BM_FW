
d=[];
subplot(3,2,1)
[t,ch1, ch2]= readFile('4_331');
mCh1=sum(ch1/length(ch1));
mCh2=sum(ch2/length(ch2));
t2=[0 max(t)];
plot(t,ch1,t,ch2,t2,[mCh1 mCh1], t2, [mCh2 mCh2]);
title('3.3v RP')
d=[d ; 3.31 ./ [mCh1 mCh2]];
    

subplot(3,2,2)
[t,ch1, ch2]= readFile('3_329');
mCh1=sum(ch1/length(ch1));
mCh2=sum(ch2/length(ch2));
t2=[0 max(t)];
plot(t,ch1,t,ch2,t2,[mCh1 mCh1], t2, [mCh2 mCh2]);
title('3.3v Rpi')
d=[d ; 3.29 ./ [mCh1 mCh2]];

subplot(3,2,3)
[t,ch1, ch2]= readFile('1_460');
mCh1=sum(ch1/length(ch1));
mCh2=sum(ch2/length(ch2));
t2=[0 max(t)];
plot(t,ch1,t,ch2,t2,[mCh1 mCh1], t2, [mCh2 mCh2]);
title('Ch1 -> 4.60')
d=[d ; 4.60 ./ [mCh1 mCh2]];

subplot(3,2,4)
[t,ch1, ch2]= readFile('2_459');
mCh1=sum(ch1/length(ch1));
mCh2=sum(ch2/length(ch2));
t2=[0 max(t)];
plot(t,ch1,t,ch2,t2,[mCh1 mCh1], t2, [mCh2 mCh2]);
title('Ch2 -> 4.59')
%d=[d ; 4.59 ./ [mCh1 mCh2]];

subplot(3,2,5)
[t,ch1, ch2]= readFile('1_2_465_029');
mCh1=sum(ch1/length(ch1));
mCh2=sum(ch2/length(ch2));
t2=[0 max(t)];
plot(t,ch1,t,ch2,t2,[mCh1 mCh1], t2, [mCh2 mCh2]);
title('Ch1 & Ch2 -> 4.65 - 0.029')
%d=[d ; [4.65/mCh1 (4.65-0.029)/mCh2]];

subplot(3,2,6)
[t,ch1, ch2]= readFile('5_000');
mCh1=sum(ch1/length(ch1));
mCh2=sum(ch2/length(ch2));
t2=[0 max(t)];
%plot(t,ch1,t,ch2,t2,[mCh1 mCh1], t2, [mCh2 mCh2]);
title('0v')


function [t,ch1, ch2]= readFile(file)
file= ['recorded_data_new/calibration/In' file '.txt'];
M=csvread(file,0,0);
t=M(:,1);
ch1=M(:,2);%*4.9/4.2; %from Rp code
ch2=M(:,3);%*4.9/4.2; %from Rp code
t=t-t(1); %0 offset
end