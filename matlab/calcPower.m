clear

sunP = 2e-6;
PDRESP = .35;
V_ref = 1.25;
ADCII = 50e-12;

PDI = PDRESP * sunP;
PDV = 5;
PDP = PDI*PDV;

FBR = V_ref*.8/(PDI);
FBI = PDI;
FBP = FBI^2*FBR;

OAQI = 3e-3;
OAQV = 10;
OAOI = PDI + ADCII;
OAOV = V_ref*.8;
OAP = OAQI*OAQV + OAOI*OAOV;

AP = PDP + FBP + OAP;

APSQI = 14e-3;
APSV = 12;

APSP = AP + APSQI*APSV;

ADCI = 5e-3;
ADCV = 3.3;
ADCP = ADCI*ADCV;

uCV = 3.3;
uCI = .1;
uCP = uCV*uCI;

FLSV = 3.3;
FLSI = 35e-3;
FLSP = FLSV*FLSI;

FBSV = 3.3;
FBSI = 50e-6;
FBSP = FBSV*FBSI;

DP = FBSP + 2*FLSP+uCP + ADCP;

DPSeta = .95; %(@.6W)

DPSP = DP/DPSeta;

Power = DPSP + APSP

strarray = ["","","","","","","",""];
disparray = [OAP,uCP,PDP,2*FLSP,ADCP,FBP+FBSP,DP*.05,APSQI*APSV];
for i = 1:length(disparray)
    strarray(i) = strcat(num2str(disparray(i),2),"W");
end

disparray = disparray ./ sum(disparray);
labels = ["op-amp","microcontroller","photodiode","flash memory","ADC","feedback resistor","digital power supply","analog power supply"];

pie(disparray,disparray,strarray);
legend(labels);






