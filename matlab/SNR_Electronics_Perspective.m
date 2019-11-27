% Signal to noise for nominal 1020 nm wavelength and testing 1030 nm
% wavelength
clear all; close all; clc
numSamples = 3;
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
Power_d = Power_a*mirrorref;

% Calculate photodiode current
R = [0.4,0.33];  % Responsivity, A/W
I_D = R.*Power_d;

% Calculate feedback resistance;
Margin = .8; %20% saturation margin
V_Ref = 1.25; %V
R_fb = (V_Ref*Margin)./I_D; %Ohm
V_sig = R_fb.*I_D; %1V

% Calculate shot noise (?)
photon_rate = Power_d./Ep; % photons/s
shot_rate = sqrt(photon_rate); % photons/s
shot_power = shot_rate.*Ep; % W
I_shot = shot_power.*R; % A
VN_shot= I_shot.*R_fb; % V

% Calculate Dark noise
I_dark = 10e-12; % A
VN_dark = I_dark.*R_fb; % V

% Quantization Noise
bits = 16;
LSB = V_Ref/2^bits; % Volts
VN_quan = LSB/sqrt(12); % Saw wave RMS - assumes constant increase or decrease of signal

% Power Supply Noise
VnoisePS = 100e-6; % V
ratio = 10^(-110/20);
VN_PS = ratio*VnoisePS;

% Transimpedance Noise (TBR)
VF_trans = 2.8e-9; %V/sqrt(Hz)
R_Shunt = 3.63e11;
Bandwidth = 104; %Hz - nyquest frequency with 208Hz sample rate
VN_trans = VF_trans.*(1 + R_fb./R_Shunt).*sqrt(Bandwidth);

% Signal to Noise Ratio
SNR = (sqrt(numSamples)).* V_sig./sqrt(VN_shot.^2 + VN_dark.^2 + VN_quan.^2 + VN_PS.^2 + VN_trans.^2)





