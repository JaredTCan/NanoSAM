% Signal to noise for nominal 1020 nm wavelength and testing 1030 nm
% wavelength
clear all; close all; clc
h = 6.626e-34;    % Planck's constant, kg-m^2/s
c = 3e8;          % Speed of light in vacuum, m/s
l = [1020,1030];  % wavelength vector, nm
Ep = h*c./l*10^9; % Energy per photon, J
ap_arcmin = 1;    % Aperture, arcmin
solardisk_avg_arcmin = 31.99; % solar disk, arcmin
fraction =(ap_arcmin/solardisk_avg_arcmin)^2;
Phi = [709.75,698]*10^(-3); % W/(m^2*nm)
BW = 40; % bandwidth, nm %CHECK
Aap = 1e-4; % Aperture area, m^2
Power = Phi*BW*Aap;
Power_a = fraction*Power;
mirrorref = .9;
photon_rate = mirrorref*Power_a./Ep; 

R = [0.4,0.33];  % Responsivity, A/W
e = 1.60218e-19;  % Elementary charge, C
QE = R.*Ep/e;     % Quantum efficiency
f = 208;      % Sampling rate, Hz
Ts = 1/f;    % Sampling time, s
photons = photon_rate*Ts;   
photoelectrons = photons.*QE;  % Signal from photodiode

% Calculate Dark noise
Idark = 10e-12/(1.6022e-19); % counts/s
Ndark = sqrt(Idark*Ts)/sqrt(4);      % Dark current noise term

% Quantization Noise
bits = 16;
ADC_margin = 0.20;  % 20% ADC margin
LSB = (1+ADC_margin).*photoelectrons./2^bits;
Nquan = LSB/(sqrt(12)*sqrt(4));

% Transimpedence noise
Inoise_imp = 27e-12; %A/sqrt(Hz)
fsig = 25;
Inoise = Inoise_imp*sqrt(fsig)/e; % Transimpedence noise current, counts/s
Ntran = (Inoise*Ts)/sqrt(4);          % Transimpedence noise term

% Power Supply Noise
VnoisePS = 100; % uV
ratio = 10^(-110/20);
Vnoise = ratio*VnoisePS*10^(-6);
Rfeed = 1./(photon_rate.*QE.*e); % ohms
InoisePS = Vnoise./Rfeed*(1/e);  % counts/s
NPS = InoisePS*Ts/sqrt(4);

% Signal to noise
SNR = photoelectrons./sqrt(Nquan.^2 + Ndark.^2 + photoelectrons + Ntran.^2 + NPS.^2)







