clear all;
close all;
clc;
pkg load image;

img=imread("Input/2martinLi.jpeg");

subplot(1,3,1);
imshow(img);
title("Original Color Image");

grayscaleImg=rgb2gray(img);
subplot(1,3,2);
imshow(grayscaleImg);
title("Grayscale Image");

negativeImg=255-grayscaleImg;
subplot(1,3,3);
imshow(negativeImg);
title("Negative Image");

imwrite(uint8(negativeImg),"Output/2negativeImage.jpeg");
