clear all;
close all;
clc;
pkg load image;

img = imread("Input/11megamind.jpg");

if size(img,3) == 3
    grayscaleImage = rgb2gray(img);
else
    grayscaleImage = img;
end

grayscaleImage = im2double(grayscaleImage);

level = graythresh(grayscaleImage);
binaryImage = im2bw(grayscaleImage, level);

structuringElement = strel('square',3);

erodedImage = imerode(binaryImage, structuringElement);

subplot(1,3,1);
imshow(img);
title("Original Image");

subplot(1,3,2);
imshow(binaryImage);
title("Binary Image");

subplot(1,3,3);
imshow(erodedImage);
title("Eroded Image");

imwrite(binaryImage, "Output/13morphologicalErosionOperation/1binaryImage.jpg");
imwrite(erodedImage, "Output/13morphologicalErosionOperation/2erodedImage.jpg");