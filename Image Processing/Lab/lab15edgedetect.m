clear all;
close all;
clc;

pkg load image;

% Read image
img = imread('apo.jpg');

% Convert to grayscale if RGB
if size(img,3) == 3
    gray = rgb2gray(img);
else
    gray = img;
end

% Edge detection using Sobel
edges = edge(gray, 'sobel');

% Display images
figure

subplot(1,2,1)
imshow(gray)
title('Original Image')

subplot(1,2,2)
imshow(edges)
title('Edge Detected Image')