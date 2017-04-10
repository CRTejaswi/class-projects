function lp_samp(fb,fs,fmax,N)
%function lp_samp(fb,fs,fmax,N)
% =========================================================================
%                Lowpass Sampling Theorem Plotting Function 
% =========================================================================
% fb = spectrum lowpass bandwidth in Hz
% fs = sampling frequency in Hz
% fmax = plot over [-fmax,fmax]
% N = number of translates, N positive and N negative
% =========================================================================
% This function automatically creates a MATLAB plot using a predefined
% spectral shape taken from the function lp_tri( ).
% =========================================================================

% define the plot interval
f = -fmax:fmax/200:fmax;
% plot the lowpass spectrum in black
plot(f,lp_tri(f,fb),'k');
% overlay positive and negative frequency translates
hold
for n = 1:N
    plot(f,lp_tri(f-n*fs,fb),':r');
    plot(f,lp_tri(f+n*fs,fb),':g');
end
hold
title('Lowpass Sampling Theorem for a Real Signal: black = orig, dotted = translates')
ylabel('Spectrum Magnitude')
xlabel('Frequency in Hz')
function x = lp_tri(f, fb)
% x = lp_tri(f, fb):
x = zeros(size(f));
for k=1:length(f)
    if abs(f(k)) <= fb
        x(k) = 1 - abs(f(k))/fb;
end;
end