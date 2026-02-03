clear all;
close all;
clc;

img=imread("Input/01son.png");

subplot(1,2,1);
imshow(img);
title("Original Color Image");

grayscaleImg=rgb2gray(img);
subplot(1,2,2);
imshow(grayscaleImg);
title("Grayscale Image");

imwrite(uint8(grayscaleImg),"Output/01grayscaleImage.png");
