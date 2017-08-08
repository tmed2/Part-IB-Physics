%This script will load, plot, and find gamma for the 'EnergyData.dat'
%file which contains the kinetic energy profile of a LineWorld object.
%Naturally they must be in the same directory.
%The data generated by Lineworld will follow a straight line very well
%provided that no tunneling has occured. If a curve is generated, then 
%tunelling has probably occured, so reduce n, dt, or the number of steps 
%in Lineword (or run the simulation again if the numbers are reliable)
%Also, MatLab seems to like tiny '-' signs, so look carfully at the plot

filename = 'EnergyData.dat';
delimiterIn = ' ';
headerlinesIn = 2;
E = importdata(filename,delimiterIn,headerlinesIn);

v = 0.001; %the closing speed of one wall
L = 0.98; % ~distance between wall surfaces
logX = log(L - v*E.data(:,1));
logE = log(E.data(:,2));
hold on;
title('Natural log of total energy against that of LineWorld Length');
xlabel('ln(x(t))');
ylabel('ln(sysEnergy)');
plot(logX, logE);

%find line of best fit, and put the gradient on the graph.
linCoeffs = polyfit(logX, logE, 1);
xFitting = logX;
yFitting = polyval(linCoeffs, xFitting);
plot(xFitting, yFitting, '-r');
m = num2str(linCoeffs(1));
xpos = ((logX(1) + logX(end))/2);
ypos = ((logE(1) + logE(end))/2);
text(xpos, ypos, strcat('1 - gamma = ', m));
hold off;