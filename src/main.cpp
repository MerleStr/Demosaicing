#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;

void bilinear(Mat img, Mat dst) {

    for (int j = 0; j <= img.rows; j++) {
        for (int c = 0; c <= img.cols; c++) {
            if (j < img.rows && c < img.cols) {

                int r = 0;
                int b = 0;
                int g = 0;

                int r1 = 0;
                int r2 = 0;
                int r3 = 0;
                int r4 = 0;

                int b1 = 0;
                int b2 = 0;
                int b3 = 0;
                int b4 = 0;

                int g1 = 0;
                int g2 = 0;
                int g3 = 0;
                int g4 = 0;

                // Current Pixel is red, Blue and Green are unknown
                if (c % 2 != 0 && j % 2 != 0) {
                    r = (int)img.at<Vec3b>(j, c)[1];

                    if (j == 0) {      
                        g4 = (int)img.at<Vec3b>(j + 1, c)[2];
                        if (c != 0) {
                            b3 = (int)img.at<Vec3b>(j + 1, c - 1)[0];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                        }
                        else {
                            b3 = (int)img.at<Vec3b>(j + 1, c + 1)[0];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                            g = (g3 + g4) / 2;
                        }
                        if (c + 1 < img.cols) {
                            b4 = (int)img.at<Vec3b>(j + 1, c + 1)[0];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                        }
                        else {
                            b4 = b3;
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                            g = (g2 + g4) / 2;
                        }

                        b = (b3 + b4) / 2;

                        if (g == 0) {
                            g = (g2 + g3 + g4) / 3;
                        }
                    } else if (j + 1 >= img.rows) {
                        g1 = (int)img.at<Vec3b>(j - 1, c)[2];
                        if (c != 0) {
                            b1 = (int)img.at<Vec3b>(j - 1, c - 1)[0];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                        }
                        else {
                            b1 = (int)img.at<Vec3b>(j - 1, c + 1)[0];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                            g = (g1 + g3) / 2;
                        }
                        if (c + 1 < img.cols) {
                            b2 = (int)img.at<Vec3b>(j - 1, c + 1)[0];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                        }
                        else {
                            b2 = b1;
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                            g = (g1 + g2) / 2;
                        }

                        b = (b1 + b2) / 2;
                        if (g == 0) {
                            g = (g1 + g2 + g3) / 3;
                        }
                    }
                    else {
                        g1 = (int)img.at<Vec3b>(j - 1, c)[2];
                        g4 = (int)img.at<Vec3b>(j + 1, c)[2];
                        if (c != 0) {
                            b1 = (int)img.at<Vec3b>(j - 1, c - 1)[0];
                            b3 = (int)img.at<Vec3b>(j + 1, c - 1)[0];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                        }
                        else {
                            b2 = (int)img.at<Vec3b>(j - 1, c + 1)[0];
                            b4 = (int)img.at<Vec3b>(j + 1, c + 1)[0];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                            b = (b2 + b4) / 2;
                            g = (g1 + g3 + g4) / 3;
                        }
                        if (c + 1 < img.cols) {
                            b2 = (int)img.at<Vec3b>(j - 1, c + 1)[0];
                            b4 = (int)img.at<Vec3b>(j + 1, c + 1)[0];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                        }
                        else {
                            b1 = (int)img.at<Vec3b>(j - 1, c - 1)[0];
                            b3 = (int)img.at<Vec3b>(j + 1, c - 1)[0];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                            b = (b1 + b3) / 2;
                            g = (g1 + g2 + g4) / 3;
                        }

                        if (b == 0) {
                            b = 0.25 * (b1 + b2 + b3 + b4);
                        }
                        if (g == 0) {
                            g = 0.25 * (g1 + g2 + g3 + g4);
                        }
                    }
                }
                // Current Pixel is Blue, Green and Red are Unknown
                else if (c % 2 == 0 && j % 2 == 0) {
                    b = (int)img.at<Vec3b>(j, c)[0];

                    if (j == 0) {
                        g4 = (int)img.at<Vec3b>(j + 1, c)[2];
                        if (c != 0) {
                            r3 = (int)img.at<Vec3b>(j + 1, c - 1)[1];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                        }
                        else {
                            r3 = (int)img.at<Vec3b>(j + 1, c + 1)[1];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                            g = (g3 + g4) / 2;
                        }
                        if (c + 1 < img.cols) {
                            r4 = (int)img.at<Vec3b>(j + 1, c + 1)[1];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                        }
                        else {
                            r4 = r3;
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                            g = (g2 + g4) / 2;
                        }

                        r = (r3 + r4) / 2;
                        if (g == 0) {
                            g = (g2 + g3 + g4) / 3;
                        }
                    }
                    else if (j + 1 >= img.rows) {
                        g1 = (int)img.at<Vec3b>(j - 1, c)[2];
                        if (c != 0) {
                            r1 = (int)img.at<Vec3b>(j - 1, c - 1)[1];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                        }
                        else {
                            r1 = (int)img.at<Vec3b>(j - 1, c + 1)[1];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                            g = (g3 + g4) / 2;
                        }
                        if (c + 1 < img.cols) {
                            r2 = (int)img.at<Vec3b>(j - 1, c + 1)[1];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                        }
                        else {
                            r2 = r1;
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                            g = (g2 + g4) / 2;
                        }

                        r = (r1 + r2) / 2;

                        if (g == 0) {
                            g = (g2 + g3 + g4) / 3;
                        }
                    }
                    else {
                        g1 = (int)img.at<Vec3b>(j - 1, c)[2];
                        g4 = (int)img.at<Vec3b>(j + 1, c)[2];
                        if (c != 0) {
                            r1 = (int)img.at<Vec3b>(j - 1, c - 1)[1];
                            r3 = (int)img.at<Vec3b>(j + 1, c - 1)[1];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                        }
                        else {
                            r2 = (int)img.at<Vec3b>(j - 1, c + 1)[1];
                            r4 = (int)img.at<Vec3b>(j + 1, c + 1)[1];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                            r = (r2 + r4) / 2;
                            g = (g1 + g3 + g4) / 3;
                        }
                        if (c + 1 < img.cols) {
                            r2 = (int)img.at<Vec3b>(j - 1, c + 1)[1];
                            r4 = (int)img.at<Vec3b>(j + 1, c + 1)[1];
                            g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                        }
                        else {
                            r1 = (int)img.at<Vec3b>(j - 1, c - 1)[1];
                            r3 = (int)img.at<Vec3b>(j + 1, c - 1)[1];
                            g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                            r = (r1 + r3) / 2;
                            g = (g1 + g2 + g4) / 3;
                        }

                        if (r == 0) {
                            r = 0.25 * (r1 + r2 + r3 + r4);
                        }
                        if (g == 0) {
                            g = 0.25 * (g1 + g2 + g3 + g4);
                        }
                    }
                }
                // Current Pixel is Green, Blue and Red is unknown
                else {
                    g = (int)img.at<Vec3b>(j, c)[2];

                    if (j % 2 != 0) {
                        if (c != 0) {
                            r1 = (int)img.at<Vec3b>(j, c - 1)[1];
                        }
                        else {
                            r1 = (int)img.at<Vec3b>(j, c + 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r2 = (int)img.at<Vec3b>(j, c + 1)[1];
                        }
                        else {
                            r2 = r1;
                        }

                        if (j != 0) {
                            b1 = (int)img.at<Vec3b>(j - 1, c)[0];
                        }
                        else {
                            b1 = (int)img.at<Vec3b>(j + 1, c)[0];
                        }
                        if (j + 1 < img.rows) {
                            b2 = (int)img.at<Vec3b>(j + 1, c)[0];
                        }
                        else {
                            b2 = b1;
                        }
                    }
                    else {
                        if (j != 0) {
                            r1 = (int)img.at<Vec3b>(j - 1, c)[1];
                        }
                        else {
                            r1 = (int)img.at<Vec3b>(j + 1, c)[1];
                        }
                        if (j + 1 < img.rows) {
                            r2 = (int)img.at<Vec3b>(j + 1, c)[1];
                        }
                        else {
                            r2 = r1;
                        }

                        if (c != 0) {
                            b1 = (int)img.at<Vec3b>(j, c - 1)[0];
                        }
                        else {
                            b1  = (int)img.at<Vec3b>(j, c + 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b2 = (int)img.at<Vec3b>(j, c + 1)[0];
                        }
                        else {
                            b2 = b1;
                        }
                    }

                    r = 0.5 * (r1 + r2);
                    b = 0.5 * (b1 + b2);
                }

                Vec3b p = Vec3b(r, g, b);

                dst.at<Vec3b>(j, c) = p;
            }
        }
    }

}

int getValue(Mat img, int row, int col, int color) {
    double x = 0.1;

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    if (row > img.rows) {
        row = row - 2;
    }
    if (col > img.cols) {
        col = col - 2;
    }

    a = (int)img.at<Vec3b>(row, col)[color];
    if (col - 2 >= 0) {
        b = (int)img.at<Vec3b>(row, col - 2)[color];
    }
    if (row - 2 >= 0) {
        c = (int)img.at<Vec3b>(row - 2, col)[color];
    }
    if (row - 2 >= 0 && col - 2 >= 0) {
        d = (int)img.at<Vec3b>(row - 2, col - 2)[color];
    }

    return a + 0.5 * x * (b - a + x * (2.0 * a - 5.0 * b + 4.0 * c - d + x * (3.0 * (b - c) + d - a)));
}

void bicubic(Mat img, Mat dst) {
    double y = 0.2;

    for (int j = 0; j <= img.rows; j++) {
        for (int c = 0; c <= img.cols; c++) {
            if (j < img.rows && c < img.cols) {

                int r = 0;
                int b = 0;
                int g = 0;

                int r1 = 0;
                int r2 = 0;
                int r3 = 0;
                int r4 = 0;

                int b1 = 0;
                int b2 = 0;
                int b3 = 0;
                int b4 = 0;

                int g1 = 0;
                int g2 = 0;
                int g3 = 0;
                int g4 = 0;

                if (c % 2 != 0 && j % 2 != 0) {
                    r = (int)img.at<Vec3b>(j, c)[1];

                    if (j != 0) {
                        if (c != 0) {
                            b1 = getValue(img, j - 1, c - 1, 0); // (int)img.at<Vec3b>(j - 1, c - 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b2 = getValue(img, j - 1, c + 1, 0); // (int)img.at<Vec3b>(j - 1, c + 1)[0];
                        }

                        g1 = getValue(img, j - 1, c, 2); // (int)img.at<Vec3b>(j - 1, c)[2];
                    }
                    if (j + 1 < img.rows) {
                        if (c != 0) {
                            b3 = getValue(img, j + 1, c - 1, 0); // (int)img.at<Vec3b>(j + 1, c - 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b4 = getValue(img, j + 1, c + 1, 0); // (int)img.at<Vec3b>(j + 1, c + 1)[0];
                        }

                        g4 = getValue(img, j + 1, c, 2); //(int)img.at<Vec3b>(j + 1, c)[2];
                    }

                    if (c != 0) {
                        g2 = getValue(img, j, c - 1, 2); // (int)img.at<Vec3b>(j, c - 1)[2];
                    }
                    if (c + 1 < img.cols) {
                        g3 = getValue(img, j, c + 1, 2); // (int)img.at<Vec3b>(j, c + 1)[2];
                    }

                    b = b1 + 0.5 * y * (b2 - b1 + y * (2.0 * b1 - 5.0 * b2 + 4.0 * b3 - b4 + y * (3.0 * (b2 - b3) + b4 - b1)));
                    g = g1 + 0.5 * y * (g2 - g1 + y * (2.0 * g1 - 5.0 * g2 + 4.0 * g3 - g4 + y * (3.0 * (g2 - g3) + g4 - g1)));
                }
                else if (c % 2 == 0 && j % 2 == 0) {
                    b = (int)img.at<Vec3b>(j, c)[0];

                    if (j != 0) {
                        if (c != 0) {
                            r1 = getValue(img, j - 1, c - 1, 1); // (int)img.at<Vec3b>(j - 1, c - 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r2 = getValue(img, j - 1, c + 1, 1); // (int)img.at<Vec3b>(j - 1, c + 1)[1];
                        }

                        g1 = getValue(img, j - 1, c, 2); //(int)img.at<Vec3b>(j - 1, c)[2];
                    }
                    if (j + 1 < img.rows) {
                        if (c != 0) {
                            r3 = getValue(img, j + 1, c - 1, 1); // (int)img.at<Vec3b>(j + 1, c - 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r4 = getValue(img, j + 1, c + 1, 1); // (int)img.at<Vec3b>(j + 1, c + 1)[1];
                        }

                        g4 = getValue(img, j + 1, c, 2); // (int)img.at<Vec3b>(j + 1, c)[2];
                    }

                    if (c != 0) {
                        g2 = getValue(img, j, c - 1, 2); // (int)img.at<Vec3b>(j, c - 1)[2];
                    }

                    if (c + 1 < img.cols) {
                        g3 = getValue(img, j, c + 1, 2); // (int)img.at<Vec3b>(j, c + 1)[2];
                    }

                    r = r1 + 0.5 * y * (r2 - r1 + y * (2.0 * r1 - 5.0 * r2 + 4.0 * r3 - r4 + y * (3.0 * (r2 - r3) + r4 - r1)));
                    g = g1 + 0.5 * y * (g2 - g1 + y * (2.0 * g1 - 5.0 * g2 + 4.0 * g3 - g4 + y * (3.0 * (g2 - g3) + g4 - g1)));
                }
                else {
                    g = (int)img.at<Vec3b>(j, c)[2];

                    if (j % 2 != 0) {
                        if (c != 0) {
                            r1 = getValue(img, j, c - 1, 1); //(int)img.at<Vec3b>(j, c - 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r2 = getValue(img, j, c + 1, 1); // (int)img.at<Vec3b>(j, c + 1)[1];
                        }

                        if (j != 0) {
                            b1 = getValue(img, j - 1, c, 0); // (int)img.at<Vec3b>(j - 1, c)[0];
                        }
                        if (j + 1 < img.rows) {
                            b2 = getValue(img, j + 1, c, 0); //(int)img.at<Vec3b>(j + 1, c)[0];
                        }
                    }
                    else {
                        if (j != 0) {
                            r1 = getValue(img, j - 1, c, 1); // (int)img.at<Vec3b>(j - 1, c)[1];
                        }
                        if (j + 1 < img.rows) {
                            r2 = getValue(img, j + 1, c, 1); // (int)img.at<Vec3b>(j + 1, c + 2)[1];
                        }

                        if (c != 0) {
                            b1 = getValue(img, j, c - 1, 0); // (int)img.at<Vec3b>(j, c - 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b2 = getValue(img, j, c + 1, 0); //(int)img.at<Vec3b>(j, c + 1)[0];
                        }
                    }

                    r = r1 + 0.5 * y * (r2 - r1 + y * (2.0 * r1 - 5.0 * r2 + 4.0 * r1 - r2 + y * (3.0 * (r2 - r1) + r2 - r1)));
                    b = b1 + 0.5 * y * (b2 - b1 + y * (2.0 * b1 - 5.0 * b2 + 4.0 * b1 - b2 + y * (3.0 * (b2 - b1) + b2 - b1)));
                }

                Vec3b p = Vec3b(r, g, b);

                dst.at<Vec3b>(j, c) = p;
            }
        }

    }
}


int main(int ac, char** av)
{
    
    std::cout << "Image Path: " << std::endl;
    std::string imgPath; // = av[1];
    std::getline(std::cin, imgPath);

    std::cout << "Image Name: " << std::endl;
    std::string imgName; // = av[2];
    std::getline(std::cin, imgName);

    std::string i = imgPath + "/" + imgName;
    Mat img = imread(i, IMREAD_COLOR);

    if (img.empty())
    {
        std::cout << "Could not read the image: " << i << std::endl;
        return 1;
    }

    int width = img.cols;
    int height = img.rows;

    Mat3b bil;
    Mat3b bic;

    bil = Mat::zeros(height, width, CV_8UC1);
    bic = Mat::zeros(height, width, CV_8UC1);

    bilinear(img, bil);
    bicubic(img, bic);

    std::string safe_Bil = imgPath + "/" + "bil_" + imgName;
    imwrite(safe_Bil, bil);

    std::string safe_Bic = imgPath + "/" + "bic_" + imgName;
    imwrite(safe_Bic, bic);

    return 0;
}