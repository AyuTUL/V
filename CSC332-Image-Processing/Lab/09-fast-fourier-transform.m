clear all;
close all;
clc;
pkg load image;

img = im2double(imread("Input/09-wm28.jpg"));

subplot(3,2,1);
imshow(img);
title("Original Image");

fftImage=fft(img);
subplot(3,2,2);
imshow(abs(fftImage));
title("Frequency Spectrum");

fftShifted=fftshift(fftImage);
subplot(3,2,3);
imshow(abs(fftShifted));
title("Centered Spectrum");

logMagnitudeSpectrum =log(1+abs(fftShifted));
subplot(3,2,4);
imshow(logMagnitudeSpectrum );
title("Log Magnitude Spectrum");

fft2Image=fft2(fftImage);
fft2RealPart=real(fft2Image);
subplot(3,2,5);
imshow(fft2RealPart);
title("2D Fast Fourier Transform");

imwrite(abs(fftImage),"Output/09-fast-fourier-transform/1-frequency-spectrum.jpg");
imwrite(abs(fftShifted),"Output/09-fast-fourier-transform/2-centered-spectrum.jpg");
imwrite(logMagnitudeSpectrum,"Output/09-fast-fourier-transform/3-log-magnitude-spectrum.jpg");
imwrite(fft2RealPart,"Output/09-fast-fourier-transform/4-2d-fast-fourier-transform.jpg");
