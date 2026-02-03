clear all;
close all;
clc;
pkg load image;

img = imread("Input/08ltg.png");

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

medianFilter9x9=medfilt2(noisyImg,[9,9]);
subplot(3,2,5);
imshow(medianFilter9x9);
title("9x9 Median Filter Image");

imwrite(grayscaleImg,"Output/08medianFilter/1grayscaleImg.png");
imwrite(noisyImg,"Output/08medianFilter/2salt&PepperImage.png");
imwrite(medianFilter3x3,"Output/08medianFilter/3medianFilter3x3.png");
imwrite(medianFilter9x9,"Output/08medianFilter/4medianFilter9x9.png");