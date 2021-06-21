#ifndef TAEYOUNGCV_H
#define TAEYOUNGCV_H

#include "kfc.h"
#include <QDebug>
#include <math.h>
#include <vector>
#include <stack>
#include <fstream>
#include <queue>
#include "eigen-3.3.8/Eigen/Dense"

using namespace std;

#define Fore_Ground 255
#define Back_Ground 0
#define __EdgePeakThresh 10

#define ToDegree(radian) ((radian) * (180.0f / _PI))
#define ToRadian(degree) ((degree) * (_PI/ 180.0f))


// edge 관련 정보이다.
struct EdgeData{
    double dx;
    double dy;
    double magn;
    int    dir;     // 8개의 방향이 존재할 수 있다. 0,1,2,3 중 하나로 표현
    unsigned char val;  // for optical flow
};

// SIFT magnitude orientation 정보이다.
struct KeyPointData{
    double magn;
    int dir;    // 0 ~ 35 까지 방향을 나타냄
    int x;
    int y;
};

// Keypoint + 그 때 sigma 값을 저장하기 위한 구조체이다.
struct KeypointAndSigma{
    int x;
    int y;
    int sigmaIdx;   // 가우시안 scale 이미지가 모여있는 벡터에서 Index로 접근하기 위해서
};

struct SIFT{
    int x;
    int y;
    int _descriptor[2][2][8];
};

typedef     vector<vector<EdgeData>*>  _EdgeImg;        //edge 정보를 담은 이미지 데이터이다.
typedef     vector<pair<int, int>>     _POINTS;         //좌표 정보를 담은 데이터이다.
typedef     vector<KImageDouble>       _ScaleSpace;     // Scale space 이미지 정보가 담긴 데이터다.
typedef     vector<KImageGray>         _Images;         // GrayScale 이미지 정보가 담긴 데이터다.
typedef     vector<_ScaleSpace>        _OctaveSpace;    // 옥타브별로 Scale space 이미지 정보가 담긴 데이터다.
typedef     vector<KeyPointData>       _KeyPointVec;    // key point 정보를 담은 벡터이다.
typedef     vector<KeypointAndSigma>   _KeypointInfo;
typedef     vector<SIFT>               _SIFTVec;        // Sift 구조체 정보를 담은 벡터이다.
typedef     vector<vector<double>>      _JMAT;
typedef     vector<double>              _JCOL;


// For CV08
template<typename T> class JMatrix{
public:

    vector<vector<T>>  AddMatrix(const vector<vector<T>> &a, const vector<vector<T>> &b){
        if(a.empty() || b.empty())  exit(0);
        if(a.size() != b.size() || a[0].size() != b[0].size()) exit(1);

        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(a[0].size(), 0.);
        resultMatrix.assign(a.size(), tmp);

        for(int nRow=0; nRow < a.size(); nRow++){
            for(int nCol=0; nCol < b[0].size(); nCol++){

                resultMatrix[nRow][nCol] = a[nRow][nCol] + b[nRow][nCol];
            }
        }

        return resultMatrix;
    }

    vector<vector<T>>  MinusMatrix(const vector<vector<T>> &a, const vector<vector<T>> &b){
        if(a.empty() || b.empty())  exit(0);
        if(a.size() != b.size() || a[0].size() != b[0].size()) exit(1);

        //행과 열 할당
        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(a[0].size(), 0.);
        resultMatrix.assign(a.size(), tmp);

        for(int nRow=0; nRow < a.size(); nRow++){
            for(int nCol=0; nCol < b[0].size(); nCol++){

                resultMatrix[nRow][nCol] = a[nRow][nCol] - b[nRow][nCol];
            }
        }

        return resultMatrix;
    }

    vector<vector<T>>  MultiMatrix(const vector<vector<T>> &a, const vector<vector<T>> &b){
        if(a.empty() || b.empty())  exit(0);
        if(a.size() != b.size() || a[0].size() != b[0].size()) exit(1);

        //행과 열 할당
        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(a[0].size(), 0.);
        resultMatrix.assign(a.size(), tmp);

        for(int nRow=0; nRow < a.size(); nRow++){
            for(int nCol=0; nCol < b[0].size(); nCol++){

                resultMatrix[nRow][nCol] = a[nRow][nCol] * b[nRow][nCol];
            }
        }

        return resultMatrix;
    }

    vector<vector<T>>  DivideMatrix(const vector<vector<T>> &a, const vector<vector<T>> &b){
        if(a.empty() || b.empty())  exit(0);
        if(a.size() != b.size() || a[0].size() != b[0].size()) exit(1);

        //행과 열 할당
        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(a[0].size(), 0.);
        resultMatrix.assign(a.size(), tmp);

        for(int nRow=0; nRow < a.size(); nRow++){
            for(int nCol=0; nCol < b[0].size(); nCol++){

                resultMatrix[nRow][nCol] = a[nRow][nCol] / b[nRow][nCol];
            }
        }

        return resultMatrix;
    }

    vector<vector<T>>  DotProduct(const vector<vector<T>> &a, const vector<vector<T>> &b){
        if(a.empty() || b.empty())  exit(0);
        if(a[0].size() != b.size()) exit(1);

        //행과 열 할당
        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(b[0].size(), 0.);
        resultMatrix.assign(a.size(), tmp);

        for(int nRow=0; nRow < a.size(); nRow++){
            for(int nCol=0; nCol < b[0].size(); nCol++){
                T tmp = 0;
                for(int mult = 0;  mult < b.size(); mult++){
                    tmp += a[nRow][mult] * b[mult][nCol];
                }

                resultMatrix[nRow][nCol] = tmp;
            }
        }

        return resultMatrix;
    }

    vector<vector<T>>  TransposeMatrix(const vector<vector<T>> &a){
        if(a.empty())  exit(0);


        //행과 열 할당
        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(a.size(), 0.);
        resultMatrix.assign(a[0].size(), tmp);

        for(int nRow=0; nRow < a.size(); nRow++){
            for(int nCol=0; nCol < a[0].size(); nCol++){

                resultMatrix[nCol][nRow] = a[nRow][nCol];
            }
        }

        return resultMatrix;
    }

    vector<vector<T>>  Inverse2Matrix(const vector<vector<T>> &a){
        if(a.empty())  exit(0);
        if(a.size() !=2 || a[0].size() !=2) exit(1);

        //행과 열 할당
        vector<vector<T> > resultMatrix; vector<double> tmp;
        tmp.assign(a.size(), 0.);
        resultMatrix.assign(a[0].size(), tmp);

        double det = a[0][0] * a[1][1] -a[0][1]* a[1][0]; // ad-bc

        if(det != 0){
            resultMatrix[0][0] = 1. / det * a[1][1];
            resultMatrix[0][1] = -1. / det * a[0][1];
            resultMatrix[1][0] = -1. / det * a[1][0];
            resultMatrix[1][1] = 1. / det * a[0][0];
        }

        return resultMatrix;
    }
};

// Main class
class taeyoungCV
{

private:
    _EdgeImg        edgeData;   // edge 정보를 담은 이미지 데이터이다.
    _POINTS         keyPoints;
    _KeypointInfo   KeypointInfoVec;

    JMatrix<double> jMatrix;
    KImageGray      resultIgImg;
    KImageColor     resultIcImg;


    // 우측부터 아래로 탐색
    int     eightNeighborRow[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int     eightNeighborCol[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    double  gaussianVoting[11][11];
    double  Patch[11][11];
    double  gaussianVoting5[5][5];

public:
    // 생성자
    taeyoungCV(double sigma=0.3);

    // CV01
    KImageColor get_sepiatone_image(KImageColor &src, double hue, double sat);
    KImageGray get_value_image(KImageColor &src);
    KImageGray get_saturation_image(KImageColor &src);
    KImageGray get_hue_image(KImageColor &src);

    //CV02
    static void get_Binarization_image(KImageGray &src, KImageGray &dst);
    static void get_Labeling_image(KImageGray &src, KImageColor &dst);
    static void get_dilation_image(KImageGray &src, KImageGray &dst, int kernel_size);
    static void get_erosion_image(KImageGray &src, KImageGray &dst, int kernel_size);

    //CV03
    static void histogram_equalization(KImageGray &src, KImageGray &dst);
    static void histogram_equalization(KImageColor &src, KImageColor &dst);
    static void histogram_matching(KImageGray &src, KImageGray &target);
    static void histogram_matching(KImageColor &src, KImageColor &target);

    //CV04
    static void getGaussianNoise(KImageGray &src, KImageGray &dst, double var);
    static void getGaussianNoise(KImageColor &src, KImageColor &dst, double var);
    static void getImpulseNoise(KImageGray &src, KImageGray &dst, double probability);
    static void getImpulseNoise(KImageColor &src, KImageColor &dst, double probability);
    static void gaussianFilter(KImageGray &src, KImageGray &dst, double sigma);
    static void gaussianFilter(KImageColor &src, KImageColor &dst, double sigma);
    static void medianFilter(KImageGray &src, KImageGray &dst, double kernalSize);
    static void medianFilter(KImageColor &src, KImageColor &dst, double kernalSize);
    static void boxFilter(KImageGray &src, KImageGray &dst, int kSize);
    static void boxFilter(KImageColor &src, KImageColor &dst, int kSize);

    //CV05
    // static 함수로 사용하려 했으나 edgeData가 static 변수로 선언이 되면 문제가 생겨서...ㅠㅠ
    void FDG(KImageGray &src, KImageGray &dst, double sigma);
    void cannyEdge(KImageGray &src, KImageGray &dst, int th1, int th2, double sigma);

    //CV06
    void circleHoughTransform(KImageGray &src, KImageColor &dst,int radius,int threshold);
    void generalizedHoughTransform(KImageGray &src, KImageColor &dst,string dir,int threshold);

    //CV07
    void gaussianFilter(KImageGray &src, KImageDouble &dst, double sigma);
    _ScaleSpace getGaussianScaleImage(KImageGray &src, double sigma);
    _ScaleSpace getDogScaleImage(_ScaleSpace & src);
    _OctaveSpace getOctaveSpace(KImageGray &src, double sigma);
    _OctaveSpace getDOG_OctaveSpace(KImageGray &src, double sigma);
    KImageGray getMergeOctaveSpace(_OctaveSpace &src);
    KImageColor getVisualizeKeyPointDetection(KImageGray &src, _OctaveSpace &octave, double sigma);
    _KeypointInfo getKeyPointDetection(_OctaveSpace &octave);
    _KeyPointVec getKeyPointOrientation(_KeypointInfo &keypointsInfo, _ScaleSpace &scaleImage);
    KImageColor getVisualizePointOrientation(_KeyPointVec &keypointVec, KImageGray &src);
    _SIFTVec getSIFTdescriptor(_KeypointInfo &keypointsInfo, _ScaleSpace &scaleImage);
    KImageColor getFeatureMatching(KImageGray &Img1, _SIFTVec &siftVec1, KImageGray &Img2, _SIFTVec &siftVec2);

    //CV08
    _EdgeImg    OpticalFlow(KImageGray& igImg1, KImageGray& igImg2, int iter = 100);
    vector<vector<double>>  GetValMatrix(const _EdgeImg& matrix);
    KImageGray  GetResultIgImg(){return resultIgImg;}
    KImageColor GetResultIcImg(){return resultIcImg;}

};

// For CV08
class ImgPyramid{
private:
    KImageGray _igImg;
    int _rowSize;
    int _colSize;
    vector<_EdgeImg> pyImg;


public:

    ImgPyramid(){};
    ImgPyramid(KImageGray & igImg) : _igImg(igImg){_rowSize = _igImg.Row(); _colSize = _igImg.Col();}

    void Create(int num);
    vector<_EdgeImg>* getPyImg(){return &pyImg;}

};

#endif // TAEYOUNGCV_H
