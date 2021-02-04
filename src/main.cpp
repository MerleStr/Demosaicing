#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;

void bilinear(Mat img, Mat dst) {

    for (int j = 0; j < img.rows; j++) {
        for (int c = 0; c < img.cols; c++) {
            if (j + 1 < img.rows && c + 1 < img.cols) {
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
                            b1 = (int)img.at<Vec3b>(j - 1, c - 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b2 = (int)img.at<Vec3b>(j - 1, c + 1)[0];
                        }

                        g1 = (int)img.at<Vec3b>(j - 1, c)[2];
                    }
                    if (j + 1 < img.rows) {
                        if (c != 0) {
                            b3 = (int)img.at<Vec3b>(j + 1, c - 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b4 = (int)img.at<Vec3b>(j + 1, c + 1)[0];
                        }

                        g4 = (int)img.at<Vec3b>(j + 1, c)[2];
                    }

                    if (c != 0) {
                        g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                    }
                    if (c + 1 < img.cols) {
                        g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                    }

                    b = 0.25 * (b1 + b2 + b3 + b4);
                    g = 0.25 * (g1 + g2 + g3 + g4);
                }
                else if (c % 2 == 0 && j % 2 == 0) { 
                    b = (int)img.at<Vec3b>(j, c)[0];

                    if (j != 0) {
                        if (c != 0) {
                            r1 = (int)img.at<Vec3b>(j - 1, c - 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r2 = (int)img.at<Vec3b>(j - 1, c + 1)[1];
                        }

                        g1 = (int)img.at<Vec3b>(j - 1, c)[2];
                    }
                    if (j + 1 < img.rows) {
                        if (c != 0) {
                            r3 = (int)img.at<Vec3b>(j + 1, c - 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r4 = (int)img.at<Vec3b>(j + 1, c + 1)[1];
                        }

                        g4 = (int)img.at<Vec3b>(j + 1, c)[2];
                    }

                    if (c != 0) {
                        g2 = (int)img.at<Vec3b>(j, c - 1)[2];
                    }

                    if (c + 1 < img.cols) {
                        g3 = (int)img.at<Vec3b>(j, c + 1)[2];
                    }

                    r = 0.25 * (r1 + r2 + r3 + r4);
                    g = 0.25 * (g1 + g2 + g3 + g4);
                }
                else {       
                    g = (int)img.at<Vec3b>(j, c)[2];

                    if (j % 2 != 0) {
                        if (c != 0) {
                            r1 = (int)img.at<Vec3b>(j, c - 1)[1];
                        }
                        if (c + 1 < img.cols) {
                            r2 = (int)img.at<Vec3b>(j, c + 1)[1];
                        }

                        if (j != 0) {
                            b1 = (int)img.at<Vec3b>(j - 1, c)[0];
                        }
                        if (j + 1 < img.rows) {
                            b2 = (int)img.at<Vec3b>(j + 1, c)[0];
                        }
                    }
                    else {
                        if (j != 0) {
                            r1 = (int)img.at<Vec3b>(j - 1, c)[1];
                        }
                        if (j + 1 < img.rows) {
                            r2 = (int)img.at<Vec3b>(j + 1, c + 2)[1];
                        }

                        if (c != 0) {
                            b1 = (int)img.at<Vec3b>(j, c - 1)[0];
                        }
                        if (c + 1 < img.cols) {
                            b2 = (int)img.at<Vec3b>(j, c + 1)[0];
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


int main(int ac, char** av)
{
    std::string  img_path = samples::findFile("C:/Users/merle/Pictures/Demosaicing/MSR-Demosaicing/Dataset_LINEAR_without_noise/bayer_panasonic/input/386.png");
    //std::string img_path = samples::findFile("C:/Users/merle/Pictures/Demosaicing/c.TIF");

    //Mat img = imread(img_path, IMREAD_GRAYSCALE);
    Mat img = imread(img_path, IMREAD_COLOR);


    if (img.empty())
    {
        std::cout << "Could not read the image: " << img_path << std::endl;
        return 1;
    }

    int width = img.cols;
    int height = img.rows;

    Mat3b dst;

    dst = Mat::zeros(height, width, CV_8UC1);

    bilinear(img, dst);

    imshow("Old Image", img);
    imshow("New Image", dst);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        std::string safe_path = "C:/Users/merle/Pictures/Demosaicing/Test/386_new.png";
        imwrite(safe_path, dst);
    }

    return 0;
}