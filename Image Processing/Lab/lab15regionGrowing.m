pkg load image

img = imread('flower.png');
img = rgb2gray(img);

seed_x = 50;   % seed point row
seed_y = 50;   % seed point column
threshold = 10;

[rows, cols] = size(img);
region = zeros(rows, cols);

seed_value = img(seed_x, seed_y);
region(seed_x, seed_y) = 1;

for i = 2:rows-1
    for j = 2:cols-1
        if abs(img(i,j) - seed_value) < threshold
            region(i,j) = 1;
        end
    end
end

subplot(1,2,1)
imshow(img)
title('Original Image')

subplot(1,2,2)
imshow(region)
title('Region Grown Image')
