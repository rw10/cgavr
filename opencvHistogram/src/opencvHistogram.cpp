#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/viz.hpp>

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
using namespace cv;

const String keys =
"{Aide h usage ? help  |     | print this message   }"
"{@arg1                |     | Full path to color imag (3 channels)}"
;

int widgetCount;

Mat generateImage(){
    Mat img = Mat(512,512,CV_8UC3);
    RNG r;
    r.fill(img(Rect(0, 0, 256, 256)), RNG::NORMAL, Vec3b(60, 40, 50), Vec3b(10, 5, 20));
    r.fill(img(Rect(256, 0, 256, 256)), RNG::NORMAL, Vec3b(160, 10, 50), Vec3b(20, 5, 10));
    r.fill(img(Rect(0, 256, 256, 256)), RNG::NORMAL, Vec3b(90, 100, 50), Vec3b(10, 20, 20));
    r.fill(img(Rect(256, 256, 256, 256)), RNG::NORMAL, Vec3b(100, 10, 150), Vec3b(10, 5, 40));

    return img;
}

void DrawHistogram3D(viz::Viz3d& window, Mat& image)
{
	double maxRows = 50;
	double maxCols = 50;

	cv::Size s = image.size();
	int rows = s.height;
	int cols = s.width;
	double maxSize = 100.0;

	int rowSolution = ceil(rows / maxRows);
	int colSolution = ceil(cols / maxCols);


    window.removeAllWidgets();
    widgetCount = 0;
    window.showWidget("Axis", viz::WCoordinateSystem(10));

	for (int i = 0; i < rows; i++)
	{
		if (i%rowSolution==0){
			for (int j = 0; j < cols; j++)
			{
				if (j%colSolution==0){
					unsigned char z = image.at<unsigned char>(i, j);

					viz::WCube s(
							Point3d(j,rows-i,0), Point3d(j+colSolution,rows-i+rowSolution,z*maxSize/255.0),
							false,
							viz::Color(z,z,z)
					);

					window.showWidget((std::string("b") + std::to_string(widgetCount++)).data(), s);
				}

			}
		}
		std::cout << "row: " << i  << "/" << rows << std::endl;
	}
}

int main (int argc,char **argv)
{
    CommandLineParser parser(argc, argv, keys);

    String nomFic = parser.get<String>(0);
    Mat img;
    if (nomFic.length() != 0)
    {
        img = imread(nomFic, IMREAD_GRAYSCALE);
        if (img.empty())
        {
            cout << "Image does not exist!";
            return 0;
        }
    }
    else
    {
        cout << "No Image specified!";
    	return 0;
    }

    // show src image
    namedWindow("Image");
    imshow("Image",img);

    waitKey(0);

    // draw histogram in 3d
    viz::Viz3d myWindow("3D Histogram");
    DrawHistogram3D(myWindow, img);

    int code = 0;
    while (code!=27)
    {
    	if (code == 0){
    		//DrawHistogram3D(myWindow, img);
            myWindow.spinOnce();
    	}
    	if (code!=27){
            code= waitKey(30);
        }
    }

    return 0;
}
