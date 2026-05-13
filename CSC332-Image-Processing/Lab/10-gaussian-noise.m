clear all;
close all;
clc;
pkg load image;

img = imread("Input/10-rowlet.png");
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

imwrite(grayscaleImage,"Output/10-gaussian-noise/1-grayscale-image.png");
imwrite(noisyImage,"Output/10-gaussian-noise/2-gaussian-noisy-image.png");
