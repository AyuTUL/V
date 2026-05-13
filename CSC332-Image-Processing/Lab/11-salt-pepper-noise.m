clear all;
close all;
clc;
pkg load image;

img = imread("Input/11-megamind.jpg");
subplot(1,3,1);
imshow(img);
title("Original Image");

grayscaleImage = im2double(rgb2gray(img));
subplot(1,3,2);
imshow(grayscaleImage);
title("Grayscale Image");

noisyImage = imnoise(grayscaleImage, 'salt & pepper', 0.05);

subplot(1,3,3);
imshow(noisyImage);
title("Salt & Pepper Noisy Image");

imwrite(grayscaleImage,"Output/11-salt-pepper-noise/1-grayscale-image.jpg");
imwrite(noisyImage,"Output/11-salt-pepper-noise/2-salt-pepper-image.jpg");
