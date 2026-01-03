clear all;
close all;
clc;

img=imread("Input/1son.png");

subplot(1,2,1);
imshow(img);
title("Original Color Image");

grayscaleImg=rgb2gray(img);
subplot(1,2,2);
imshow(grayscaleImg);
title("Grayscale Image");

imwrite(uint8(grayscaleImg),"Output/1grayscaleImage.png");
