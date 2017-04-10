% =========================================================================
%       Main program to implement lowpass & bandpass filters
% =========================================================================
% Use functions:
%   lp_samp = LowPass Filter 
%   bp_samp = BandPass Filter
%   bp_sampc = BandPass Filter (with complex coefficients)
%
% For more details, read "Reference.docx"
% =========================================================================

clc
clear all
%Implement LowPass Filter
figure (1)
%fb=10,fs=25,fmax=100,N=10
lp_samp(10,25,100,10)

%Implement BandPass Filter
figure (2)
%fl=10,fh=20,fs=25,fmax=100,N=10,shape=upslope triangular
bp_samp(10,20,25,100,10,0)
% =========================================================================