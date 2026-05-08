clear all;
close all;
clc;
pkg load image;

img = imread("Input/15-pigeon.jpg");
grayscaleImage = rgb2gray(img);

seed_x = 50;
seed_y = 50;
threshold = 10;

[rows, cols] = size(grayscaleImage);
region = zeros(rows, cols);

seed_value = grayscaleImage(seed_x, seed_y);
region(seed_x, seed_y) = 1;

for i = 2:rows-1;
    for j = 2:cols-1;
        if abs(grayscaleImage(i,j) - seed_value) < threshold;
            region(i,j) = 1;
        end
    end
end

subplot(1,3,1);
imshow(img);
title('Original Image');

subplot(1,3,2);
imshow(grayscaleImage);
title('Grayscale Image');

subplot(1,3,3);
imshow(region);
title('Region Grown Image');

imwrite(region, "Output/15-region-grown-image.jpg");
