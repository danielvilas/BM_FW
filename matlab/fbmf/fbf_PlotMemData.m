function [ output_args ] = fbf_PlotMemData( platform, lang, protocol )
%FBF_PLOTDATA FogBenchmarkFramework Plots Memory File
%   Reads the power data file generated by the Linux Process Monitor and
%   plots all
figure('Name',sprintf("%s-%s-%s",platform, lang, protocol));
for i = 1:5 
    [ time,  cpu,  dcpu,  mem, out, in ] = fbf_ReadMemData(platform, lang, protocol,i);
    time=time/1000;
    
    subplot(4,1,1);
    plot(time,mem);
    hold on;
    axis tight;
    
    subplot(4,1,2);
    plot(time,dcpu);
    hold on;
    axis tight;
    subplot(4,1,3);
    plot(time,out);
    hold on;
    axis tight;  
    subplot(4,1,4);
    plot(time,in,'displayname',sprintf('C %i', i));
    hold on;
    axis tight;
end
subplot(4,1,1);
xlabel('Time (s)');
ylabel('Mem in KB');
subplot(4,1,2);
xlabel('Time (s)');
ylabel('%CPU per Period');
subplot(4,1,3);
xlabel('Time (s)');
ylabel('Octets Out');
subplot(4,1,4);
xlabel('Time (s)');
ylabel('Octets in');
legend('show');

end
