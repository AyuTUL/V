clear all;
close all;
clc;
pkg load image;

img = imread("Input/6golisopod.jpg");

subplot(4,2,1);
imshow(img);
title("Original Image");

grayscaleImg = rgb2gray(img);
subplot(4,2,5);
imshow(grayscaleImg);
title("Grayscale Image");

enhance1Img = imadjust(grayscaleImg,[0.3 0.7],[]);
subplot(4,2,3);
imshow(enhance1Img);
title("Enhanced Image 1");

enhance2Img = imadjust(img,[0.2 0.3 0; 0.6 0.7 1],[]);
subplot(4,2,4);
imshow(enhance2Img);
title("Enhanced Image 2");

subplot(4,2,7);
imhist(grayscaleImg);
title("Histogram of Grayscale Image");

histogramEqualizedGrayscaleImg=histeq(grayscaleImg);
subplot(4,2,6);
imshow(histogramEqualizedGrayscaleImg);
title("Equalized Image");

subplot(4,2,8);
imhist(histogramEqualizedGrayscaleImg);
title("Histogram of Equalized Image");

imwrite(enhance1Img,"Output/6histogramEqualization/1enchancedImage.png");
imwrite(enhance2Img,"Output/6histogramEqualization/2enchancedImage.png");
imwrite(histogramEqualizedGrayscaleImg,"Output/6histogramEqualization/equalizedImage.png");

print("Output/6histogramEqualization/histogramGrayscaleImage.png","-dpng");
print("Output/6histogramEqualization/histogramEqualizedImage.png","-dpng");
