clear all;
close all;
clc;
pkg load image;

img = imread("Input/10rowlet.png");
subplot(1,3,1);
imshow(img);
title("Original Image");

grayscaleImage = im2double(rgb2gray(img));
subplot(1,3,2);
imshow(grayscaleImage);
title("Grayscale Image");

noisyImage = imnoise(grayscaleImage, 'gaussian', 0, 0.01);

subplot(1,3,3);
imshow(noisyImage);
title("Gaussian Noisy Image");

imwrite(grayscaleImage,"Output/10gaussianNoise/1grayscaleImage.png");
imwrite(noisyImage,"Output/10gaussianNoise/2gaussianNoisyImage.png");