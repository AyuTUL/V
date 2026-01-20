clear all;
close all;
clc;
pkg load image;

img = imread("Input/5squidward.jpg");

bit0 = double(bitget(img,1));
bit1 = double(bitget(img,2));
bit2 = double(bitget(img,3));
bit3 = double(bitget(img,4));
bit4 = double(bitget(img,5));
bit5 = double(bitget(img,6));
bit6 = double(bitget(img,7));
bit7 = double(bitget(img,8));

subplot(3,3,1);
imshow(img);
title("Original Image");

subplot(3,3,2);
imshow(bit0);
title('Bit Plane 0');

subplot(3,3,3);
imshow(bit1);
title('Bit Plane 1');

subplot(3,3,4);
imshow(bit2);
title('Bit Plane 2');

subplot(3,3,5);
imshow(bit3);
title('Bit Plane 3');

subplot(3,3,6);
imshow(bit4);
title('Bit Plane 4');

subplot(3,3,7);
imshow(bit5);
title('Bit Plane 5');

subplot(3,3,8);
imshow(bit6);
title('Bit Plane 6');

subplot(3,3,9);
imshow(bit7);
title('Bit Plane 7');

imwrite(bit0,"Output/5bitPlaneSlicing/Plane0Image.png");
imwrite(bit1,"Output/5bitPlaneSlicing/Plane1Image.png");
imwrite(bit2,"Output/5bitPlaneSlicing/Plane2Image.png");
imwrite(bit3,"Output/5bitPlaneSlicing/Plane3Image.png");
imwrite(bit4,"Output/5bitPlaneSlicing/Plane4Image.png");
imwrite(bit5,"Output/5bitPlaneSlicing/Plane5Image.png");
imwrite(bit6,"Output/5bitPlaneSlicing/Plane6Image.png");
imwrite(bit7,"Output/5bitPlaneSlicing/Plane7Image.png");
