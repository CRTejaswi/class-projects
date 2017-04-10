function bp_sampc(fl,fh,fs,fmax,N,shape)
%function bp_samp(fl,fh,fs,fmax,N,shape)
% =========================================================================
%           Complex Bandpass Sampling Theorem Plotting Function 
% =========================================================================
% fl = frequency in Hz
% fh = spectrum upper frequency in Hz
% fs = sampling frequency in Hz
% fmax = plot over [-fmax,fmax]
% N = number of translates, N positive and N negative
% shape = basic spectral shape: 0-default upslope tri, 1-downslope tri
% =========================================================================
% This function automatically creates a MATLAB plot using a predefined
% spectral shape taken from the function bp_tri_positive().
% Use default shape for only 5 input arguments.
% =========================================================================

if nargin == 5
    shape = 0;
end
% define the plot interval
f = -fmax:fmax/200:fmax;
% plot the bandpass spectrum
plot(f,bp_tri_positive(f,fl,fh,shape),'k');
% overlay positive and negative frequency translates
hold
for n = 1:N
    plot(f,bp_tri_positive(f-n*fs,fl,fh,shape),':r');
    plot(f,bp_tri_positive(f+n*fs,fl,fh,shape),':g');
end
hold
title('Bandpass Sampling Theorem for a Complex Signal: Blk = orig, dotted = translates')
ylabel('Spectrum Magnitude')
xlabel('Frequency in Hz')
function x = bp_tri_positive(f, fl, fh, shape)
% x = bp_tri(f, fl, fh, shape):
x = zeros(size(f));
if shape == 1
    for k=1:length(f)
        if f(k) <= fh
        if f(k) >= fl
            x(k) = (fh-abs(f(k)))/(fh-fl);
        end;
    end;
end
else
    for k=1:length(f)
        if f(k) <= fh
        if f(k) >= fl
            x(k) = (abs(f(k))-fl)/(fh-fl);
end;
end;
end
end