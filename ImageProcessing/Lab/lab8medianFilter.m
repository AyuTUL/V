%fix blur
clear all;
close all;
clc;
pkg load image;

img = imread("Input/8ltg.png");

subplot(3,2,1);
imshow(img);
title("Original Image");

grayscaleImg=rgb2gray(img);
subplot(3,2,2);
imshow(grayscaleImg);
title("Grayscale Image");

noisyImg=im2double(imnoise(grayscaleImg,'salt & pepper',0.15));
subplot(3,2,3);
imshow(noisyImg);
title("Salt & Pepper Noise Image");

medianFilter3x3=medfilt2(noisyImg,[3,3]);
subplot(3,2,4);
imshow(medianFilter3x3);
title("3x3 Median Filter Image");

medianFilter10x10=medfilt2(noisyImg,[10,10]);
subplot(3,2,5);
imshow(medianFilter10x10);
title("10x10 Median Filter Image");

imwrite(grayscaleImg,"Output/8medianFilter/1grayscaleImg.png");
imwrite(noisyImg,"Output/8medianFilter/2salt&PepperImage.png");
imwrite(medianFilter3x3,"Output/8medianFilter/3medianFilter3x3.png");
imwrite(medianFilter10x10,"Output/8medianFilter/4medianFilter10x10.png");