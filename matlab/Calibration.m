file='330';
desiredVoltage = 0.330;
[ch1, ch2]= readFile(file);
calib_o=[858993459 858993459];
r1=process(ch1,1,calib_o);
r2=process(ch2,2,calib_o);

m1=sum(r1)/length(r1);
m2=sum(r2)/length(r2);
calib_n=[858993459 858993459];
calib_n(1)=calib_o(1)*desiredVoltage/m1;
calib_n(2)=calib_o(2)*desiredVoltage/m2;
rn1=process(ch1,1,calib_n);
rn2=process(ch2,2,calib_n);

rt1=r1*calib_n(1)/calib_o(1);
rt2=r2*calib_n(2)/calib_o(2);

correccion = sum(r2-r1)/length(rt1)

rf1=r1*(1/0.6-0.5);
rf2=r2*(1/0.6-0.5)-correccion;

factor=[calib_n(1)/calib_o(1) calib_n(2)/calib_o(2)]

function [res] = process(chData,ch, calib)
dc_offs=[153 250];
ADC_BITS=14;
FULL_SCALE_NORM=20;

calib_cnts = chData - dc_offs(ch);
calibScale=calib(ch)*100/(2^32);
adc_max_v=1;

res=calib_cnts * adc_max_v / (2 ^ (ADC_BITS - 1));
res=res*calibScale/(FULL_SCALE_NORM/adc_max_v);
end

function [ch1, ch2]= readFile(file)
fid = fopen(join(['recorded_data/Calibration/calibration_' file]));

l=fgetl(fid);  % read a line
ch1=[];
ch2=[];
while ischar(l)
    ch1=[ch1;sscanf(l(1:7),'%d')];
    ch2=[ch2;sscanf(l(8:15),'%d')];
    l=fgetl(fid); 
end
fclose(fid);
clear fid;
end