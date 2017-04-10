% =========================================================================
%                            Sampling Theorem
% =========================================================================
% This script plots four outputs of the same sinusoidal input for four
% values of the sampling frequency.
% =========================================================================

clc; clear all; close all; 
% Specifications
Fc = 1; Fs1 = 100*Fc; Fs2 = 1.2*Fc; Fs3 = 2*Fc; Fs4 = 10*Fc;
t1 = 0:1/Fs1:10; t2 = 0:1/Fs2:10; t3 = 0:1/Fs3:10; t4 = 0:1/Fs4:10; % 10Sec

% Signals
s1 = cos(2*pi*Fc*t1); % Original signal sampled at very high rate (100*Fc)
s2 = cos(2*pi*Fc*t2); % Original signal sampled at SR < 2*Fc (SR = Fc)
s3 = cos(2*pi*Fc*t3); % Original signal sampled at SR = 2*Fc
s4 = cos(2*pi*Fc*t4); % Original signal sampled at SR > 2*Fc (SR = 10*Fc)

% Plot these signals
subplot(411); plot(t1,s1); title('For SR=100*Fc');
subplot(412); plot(t1,s1,'r',t2,s2,'b*-'); title('For SR < 2*Fc');
subplot(413); plot(t1,s1,'r',t3,s3,'b*-'); title('For SR = 2*Fc');
subplot(414); plot(t1,s1,'r',t4,s4,'b*-'); title('For SR > 2*Fc');
% =========================================================================
