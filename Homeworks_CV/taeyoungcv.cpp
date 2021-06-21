#include "taeyoungcv.h"

taeyoungCV::taeyoungCV(double sigma)
{
    // guassianVoting initialization - size 5
    for(int nRow = -2; nRow <3; nRow++){
        for(int nCol= -2; nCol < 3; nCol++){
            gaussianVoting5[nRow+2][nCol+2] = 1 / (_2PI * pow(sigma, 2)) * exp(-0.5 * ( pow(nRow,2) + pow(nCol,2) / pow(sigma, 2)));
        }
    }

    // guassianVoting initialization
    for(int nRow = -5; nRow <6; nRow++){
        for(int nCol= -5; nCol < 6; nCol++){
            gaussianVoting[nRow+5][nCol+5] = 1 / (_2PI * pow(sigma, 2)) * exp(-0.5 * ( pow(nRow,2) + pow(nCol,2) / pow(sigma, 2)));
        }
    }

    double max = 0.0;
    double min = 1000.0;

    // Patch initialization with Gaussian with Sigma 1.6
    for(int nRow = -5; nRow <6; nRow++){
        for(int nCol= -5; nCol < 6; nCol++){
            Patch[nRow+5][nCol+5] = 1 / (_2PI * pow(1.6, 2)) * exp(-0.5 * ( pow(nRow,2) + pow(nCol,2) / pow(1.6, 2)));

            if(max < Patch[nRow+5][nCol+5]){
                max = Patch[nRow+5][nCol+5];
            }

            if(min > Patch[nRow+5][nCol+5]){
                min = Patch[nRow+5][nCol+5];
            }
        }
    }

    // Scaling 0~1
    for(int nRow = -5; nRow <6; nRow++){
        for(int nCol= -5; nCol < 6; nCol++){
            Patch[nRow+5][nCol+5] = (Patch[nRow+5][nCol+5] - min) / (max-min);
        }
    }

    double sum = 0.0;

    for(int nRow = -5; nRow <6; nRow++){
        for(int nCol= -5; nCol < 6; nCol++){
            sum += Patch[nRow+5][nCol+5];
        }
    }

}

// Input : Image, hue value, saturaion value
// Output : Sepia Tone Transform image
// 이미지와 hue값 saturation 값을 받으면 sepia tone으로 변환해주는 함수
KImageColor taeyoungCV::get_sepiatone_image(KImageColor &src, double hue, double sat)
{
    KImageColor tmp;
    tmp = src;
    KImageGray value(tmp.Row(),tmp.Col());

    //Value 값 뽑아내기
    for(unsigned int i = 0; i < tmp.Row();i++){
        for(unsigned int j = 0 ; j < tmp.Col(); j++){
            double dMax;
            dMax  = _MAX(_MAX(tmp[i][j].r,tmp[i][j].g),tmp[i][j].b);
            value[i][j] = dMax;
        }
    }

    // hsv to rgb 출처 : https://www.rapidtables.com/convert/color/hsv-to-rgb.html

    for(unsigned int a = 0; a < tmp.Row();a++){
        for(unsigned int b = 0 ; b < tmp.Col(); b++){
            double v = value[a][b] / 255.0;
            double c = sat * v;
            double m = v - c;
            double hue_div_ = hue/60;
            double x = c*(1 - abs(fmod(hue_div_,2.0) - 1));
            double _r,_g,_b;

            if((hue >= 0) && (hue < 60)){
               _r = c;
               _g = x;
               _b = 0;

            }
            else if((hue >= 60) && (hue < 120)){
                _r = x;
                _g = c;
                _b = 0;
            }
            else if((hue >= 120) && (hue < 180)){
                _r = 0;
                _g = c;
                _b = x;
            }
            else if((hue >= 180) && (hue < 240)){
                _r = 0;
                _g = x;
                _b = c;
            }
            else if((hue >= 240) && (hue < 300)){
                _r = x;
                _g = 0;
                _b = c;
            }
            else if ((hue >= 300) && (hue < 360)){
                _r = c;
                _g = 0;
                _b = x;
            }

            tmp[a][b].r = (_r+m)*255.0;
            tmp[a][b].g = (_g+m)*255.0;
            tmp[a][b].b = (_b+m)*255.0;
        }
    }

    return tmp;
}

// Input : Image
// Output : Value image (1 channel)
// Input 이미지의 Value값을 반환해주는 함수
KImageGray taeyoungCV::get_value_image(KImageColor &src)
{
    KImageColor tmp = src;
    KImageGray value(tmp.Row(),tmp.Col());

    //Value 값 뽑아내기
    for(unsigned int i = 0; i < tmp.Row();i++){
        for(unsigned int j = 0 ; j < tmp.Col(); j++){
            double dMax;
            dMax  = _MAX(_MAX(tmp[i][j].r,tmp[i][j].g),tmp[i][j].b);
            value[i][j] = dMax;
        }
    }

    return value;

}

// Input : Image
// Output : Visualize saturation image (1 channel)
// 이미지를 받으면 saturation의 값을 반환해주는 함수
KImageGray taeyoungCV::get_saturation_image(KImageColor &src)
{
    KImageColor tmp = src;
    KImageGray sat(tmp.Row(),tmp.Col());


    //Saturation 값 뽑아내기
    for(unsigned int i = 0; i < tmp.Row();i++){
        for(unsigned int j = 0 ; j < tmp.Col(); j++){
            double dMax,dMin,dSat;
            dMax  = _MAX(_MAX(tmp[i][j].r,tmp[i][j].g),tmp[i][j].b);
            dMin  = _MIN(_MIN(tmp[i][j].r,tmp[i][j].b),tmp[i][j].g);
            dSat = (dMax - dMin) / dMax;
            dSat = dSat * 255.0;
            sat[i][j] = dSat;
        }
    }

    return sat;
}

// Input : Image
// Output : Visualize hue image (1 channel)
// 이미지를 받으면 hue의 값을 반환해주는 함수
KImageGray taeyoungCV::get_hue_image(KImageColor &src)
{
    KImageColor tmp = src;
    KImageGray hue(tmp.Row(), tmp.Col());

    // Hue 값 계산하기
    for(unsigned int i = 0; i< tmp.Row(); i++)
        for(unsigned int j = 0; j< tmp.Col();j++){
            double dMax,dMin,delta,hue_pix;

            dMax = _MAX(_MAX(tmp[i][j].r,tmp[i][j].g),tmp[i][j].b);
            dMin = _MIN(_MIN(tmp[i][j].r,tmp[i][j].g),tmp[i][j].b);
            delta = dMax - dMin;

            if(dMax == tmp[i][j].r){
                 hue_pix = tmp[i][j].g - tmp[i][j].b;
                 hue_pix = fmod(hue_pix/delta,6.0);
                 hue_pix *= 60.0;
            }
            else if(dMax == tmp[i][j].g){
                hue_pix = tmp[i][j].b - tmp[i][j].r;
                hue_pix /= delta;
                hue_pix *= 60.0;
                hue_pix += 120.0;
            }
            else {
                hue_pix = tmp[i][j].r - tmp[i][j].g;
                hue_pix /= delta;
                hue_pix *= 60.0;
                hue_pix += 240.0;
            }

        hue_pix /= 360.0;
        hue_pix *= 255.0;

        hue[i][j] = hue_pix;
        }

    return hue;
}

// Input : Gray scale Image
// Output (dst) : Binarization Image
// Otsu algorithm에 의해 이진화를 시켜주는 함수
void taeyoungCV::get_Binarization_image(KImageGray &src, KImageGray &dst)
{
    // Histogramming
    int n = 0;
    int hist[256] = {0,};
    for(unsigned int i=0; i<src.Row(); i++)
        for(unsigned int j=0; j<src.Col(); j++)
        {
            hist[src[i][j]] = hist[src[i][j]] + 1;  // number of pixel
            n += 1;
        }

    double      q1[256],Myu1[256],Myu2[256],vP[256];
    double		dMyu 	= 0.0;
    int			nThresh = 0;
    double		dMax 	= 0.0, dSigmaB[256];

    // 1. Initialization
    // P(i)의 배열 구하기
    for(int i = 0; i<256;i++){
        vP[i] = (double)hist[i] / (double)src.Size();
    }

    // Myu 및 Myu2[0]구하기
    Myu2[0]     = 0.0;
    for(int j = 0; j<256;j++){
        Myu2[0] += j*vP[j] / (1.0-vP[0]);
        dMyu += (j*vP[j])/(1.0-vP[0]);
    }

    q1[0]   	= (double)hist[0];
    Myu1[0] 	= 0.0;

    // 2. Recursion
    for(int t = 0; t < 255; t++){

        q1[t+1] = q1[t] + vP[t+1];

        // q2[t+1] == 0일 때 예외처리
        if((1.0 - q1[t+1]) == 0){
            Myu2[t+1]= 0.0;
            continue;
        }
        // q1[t+1] == 0일때 예외처리
        if(q1[t+1]==0.0)
        {
            Myu1[t+1] = 0.0;
            continue;
        }


        Myu1[t+1] = (q1[t] * Myu1[t] + (double)(t+1)*vP[t+1])/q1[t+1];
        Myu2[t+1] = (dMyu - q1[t+1]*Myu1[t+1])/(1 - q1[t+1]);

        dSigmaB[t] = q1[t] * (1.0-q1[t]) * pow((Myu1[t]-Myu2[t]),2);

    }

    // 3. Select t maximizing dSigmaB
    for(int t = 0; t < 255; t++){

        if(dMax < dSigmaB[t]){
            dMax = dSigmaB[t];
            nThresh = t;
        }

    }

    // 4. Applying to Result image

    dst = src;

    for(unsigned int i=0; i<dst.Row(); i++)
        for(unsigned int j=0; j<dst.Col(); j++)
        {
            if(dst[i][j] > nThresh )
                dst[i][j] = Fore_Ground;

            else
                dst[i][j] = Back_Ground;
        }

}

// Input : Gray Image
// Output (dst) : 8 neighbor labeling Image
// Labeling을 수행하는 함수
void taeyoungCV::get_Labeling_image(KImageGray &src, KImageColor &dst)
{
    KImageGray tmp = src;
    KImageColor final(src.Row(),src.Col());

    // 교수님이 주신 라이브러리 (kfc)를 이용하여 opening 연산 적용
    tmp = tmp.BinaryErode(1);
    tmp = tmp.BinaryDilate(1);

    int nRow = src.Row(), nCol = src.Col();
    unsigned int uCur, uUp, uLeft, uDia;
    unsigned int wUpColor, wLeftColor, wDiaColor;
    unsigned int nLabel[nRow][nCol];
    unsigned int nColor = 1;


   // nLabel 초기화
    for (int r = 0; r < nRow; r++) {
            for (int c = 0; c < nCol; c++) {
                nLabel[r][c] = -1;
            }
        }

    //labeling 시작
    for (int i = 0; i < nRow; i++) {
            for (int j = 0; j < nCol; j++) {
                uCur = tmp[i][j];
                if (Fore_Ground && uCur == 0) {
                    nLabel[i][j] = 0;
                    continue;
                }//픽셀이 그라백운드 색이면 continue
                else if (Back_Ground && uCur) {
                    nLabel[i][j] = 0;
                    continue;
                }
                if (i == 0 || j == 0) { // side 쪽 새로운 label 부여
                    nLabel[i][j] = nColor++;
                }
                else {
                    uDia = tmp[i - 1][j - 1];
                    uUp = tmp[i - 1][j];   //위 픽셀의 밝기값(1 or 0)
                    uLeft = tmp[i][j - 1]; //왼쪽 픽셀의 밝기값(1 or 0)
                    wDiaColor = nLabel[i - 1][j - 1];
                    wUpColor = nLabel[i - 1][j]; //위 픽셀 컬러
                    wLeftColor = nLabel[i][j - 1]; //왼쪽 픽셀 컬러

                    if ((uCur != uUp || wUpColor == 0) && (uCur != uLeft || wLeftColor == 0) && (uCur != uDia || wDiaColor == 0)) {
                        //주위에서 첫 흰픽셀일 때
                        nLabel[i][j] = nColor++;
                    }
                    else if (uCur == uUp && (uCur != uLeft || wLeftColor == 0) && (uCur != uDia || wDiaColor == 0)) {
                        //위 픽셀이 흰색
                        if (wUpColor == -1)
                            nLabel[i - 1][j] = nColor++;
                        nLabel[i][j] = wUpColor;
                    }
                    else if ((uCur != uUp || wUpColor == 0) && uCur == uLeft && (uCur != uDia || wDiaColor == 0)) {
                        //왼쪽 픽셀이 흰색
                        if (wLeftColor == -1)
                            nLabel[i][j - 1] = nColor++;
                        nLabel[i][j] = wLeftColor;
                    }
                    else if ((uCur != uUp || wUpColor == 0) && (uCur != uLeft || wLeftColor == 0) && uCur == uDia) {
                        //대각 픽셀이 흰색
                        if (wDiaColor == -1)
                            nLabel[i - 1][j - 1] = nColor++;
                        nLabel[i][j] = wDiaColor;
                    }
                    else if ((uCur != uUp || wUpColor == 0) && uCur == uLeft && uCur == uDia) {
                        //왼쪽 픽셀이 흰색
                        nLabel[i][j] = wLeftColor;
                        if (wDiaColor != wLeftColor) {
                            // 지금까지 봤던 픽셀들 다시 update
                            for (int a = 0; a < i + 1; a++) {
                                for (int b = 0; b < j + 1; b++) {
                                    if (nLabel[a][b] == wDiaColor) {
                                        nLabel[a][b] = wLeftColor;
                                    }
                                }
                            }
                        }
                    }
                    else if (uCur == uUp && (uCur != uLeft || wLeftColor == 0) && uCur == uDia) {
                        //왼쪽 픽셀이 흰색
                        nLabel[i][j] = wUpColor;
                        if (wDiaColor != wUpColor) {
                            // 지금까지 봤던 픽셀들 다시 update
                            for (int a = 0; a < i + 1; a++) {
                                for (int b = 0; b < j + 1; b++) {
                                    if (nLabel[a][b] == wDiaColor) {
                                        nLabel[a][b] = wUpColor;
                                    }
                                }
                            }
                        }
                    }
                    else if (uCur == uUp && uCur == uLeft && (uCur != uDia || wDiaColor == 0)) {
                        //왼쪽 픽셀이 흰색
                        nLabel[i][j] = wUpColor;
                        if (wUpColor != wLeftColor) {
                            // 지금까지 봤던 픽셀들 다시 update
                            for (int a = 0; a < i + 1; a++) {
                                for (int b = 0; b < j + 1; b++) {
                                    if (nLabel[a][b] == wLeftColor) {
                                        nLabel[a][b] = wUpColor;
                                    }
                                }
                            }
                        }
                    }
                    else if ((uCur == uUp) && (uCur == uLeft) && (uCur == uDia)) {
                        nLabel[i][j] = wUpColor;
                        if (wUpColor != wLeftColor) {
                            // 지금까지 봤던 픽셀들 다시 update
                            for (int a = 0; a < i + 1; a++) {
                                for (int b = 0; b < j + 1; b++) {
                                    if (nLabel[a][b] == wLeftColor) {
                                        nLabel[a][b] = wUpColor;
                                    }
                                }
                            }
                        }
                        if (wDiaColor != wUpColor) {
                            // 지금까지 봤던 픽셀들 다시 update
                            for (int a = 0; a < i + 1; a++) {
                                for (int b = 0; b < j + 1; b++) {
                                    if (nLabel[a][b] == wDiaColor) {
                                        nLabel[a][b] = wUpColor;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    // 라벨링 된 데이터를 이용하여 색깔 visualize
    for(int i=0; i<nRow; i++){
           for(int j=0; j<nCol; j++){
               if (nLabel[i][j]>0){
                   final[i][j].r = (nLabel[i][j])%256;
                   final[i][j].g = (nLabel[i][j]*5)%256;
                   final[i][j].b = (nLabel[i][j]*7)%256;
               }
               else {
                   final[i][j].r = 0;
                   final[i][j].g = 0;
                   final[i][j].b = 0;
               }
             }
           }

    // dst에 대입 후 반환
    dst = final;
}


// Input : Binarization Image
// Output (dst) : Dilation Image
// 이진화 된 영상을 Dilation을 수행하는 함수
void taeyoungCV::get_dilation_image(KImageGray &src, KImageGray &dst, int kernel_size)
{
    KImageGray tmp = src;
    KImageGray result = src;

    int half_kernel = kernel_size / 2;

    // kernal 크기에 맞게 검사
    for(unsigned int i = half_kernel; i<src.Row()-half_kernel; i++)
        for(unsigned int j = half_kernel; j<src.Col()-half_kernel; j++){

            if(tmp[i][j]==Back_Ground){       // 픽셀의 값이 검은색 일 때

                // kernal의 크기만큼 for문을 돌면서 검사
                for(int a = 0; a<=half_kernel;a++){
                    // 하나라도 foreground가 존재하면
                    if(tmp[i-a][j-a] || tmp[i][j-a] || tmp[i+a][j-a] || tmp[i-a][j]
                       || tmp[i+a][j] || tmp[i-a][j+a] || tmp[i][j+a] || tmp[i+a][j+a]){
                        result[i][j] = Fore_Ground; // result 값을 바꿔준다.
                    }
                }
            }
        }

    dst = result;
}

// Input : Binarization Image
// Output (dst) : Erosion Image
// 이진화 된 영상을 Dilation을 수행하는 함수
void taeyoungCV::get_erosion_image(KImageGray &src, KImageGray &dst, int kernel_size)
{
    KImageGray tmp = src;
    KImageGray result = src;

    int half_kernel = kernel_size / 2;

    // kernal 크기에 맞게 검사
    for(unsigned int i = half_kernel; i<src.Row()-half_kernel; i++)
        for(unsigned int j = half_kernel; j<src.Col()-half_kernel; j++){

            if(tmp[i][j]==Fore_Ground){       // 픽셀의 값이 흰색 일 때

                // kernal의 크기만큼 for문을 돌면서 검사
                for(int a = 0; a<=half_kernel;a++){
                    // kernal 안의 pixel이 모두 foreground가 존재하면
                    if(tmp[i-a][j-a] && tmp[i][j-a] && tmp[i+a][j-a] && tmp[i-a][j]
                       && tmp[i+a][j] && tmp[i-a][j+a] && tmp[i][j+a] && tmp[i+a][j+a]){
                        result[i][j] = Fore_Ground; // result 값을 그대로 유지.
                    }
                    else
                        result[i][j] = Back_Ground; // 아니면 Back ground로 변경
                }
            }
        }

    dst = result;
}


// Input : Gray Image
// Output (dst) : Histogram equalization Image
// 히스토그램 평활화를 진행하는 함수
void taeyoungCV::histogram_equalization(KImageGray &src, KImageGray &dst)
{
    // dst와 src가 같은지 검사 - 다를시 복사
    if(dst.Row() != src.Row())
        if(dst.Col() != src.Col())
            dst = src;

    //histograming according to intensities
    KHisto Histogram(src);

    //accumulated histogram
    double*  dpHisto = Histogram.Address();
    for(int i=1, ic=Histogram.Size()-1; ic; ic--, i++)
        dpHisto[i] += dpHisto[i-1];

    //Histogram Equalization
    for(int i=0, ic=Histogram.Size(); ic; ic--, i++)
        dpHisto[i] = dpHisto[i] / (double)(src.Size());

    //transform the original image
    for(int ic=src.Row(),i=0; ic; ic--,i++)
        for(int jc=src.Col(),j=0; jc; jc--,j++)
            dst[i][j] = (unsigned char)(dpHisto[src[i][j]]*255.0 + 0.5);
}

// Input : Color Image
// Output (dst) : Histogram equalization Image
// 히스토그램 평활화를 진행하는 함수
void taeyoungCV::histogram_equalization(KImageColor &src, KImageColor &dst)
{
    // dst와 src가 같은지 검사 - 다를시 복사
    if(dst.Row() != src.Row())
        if(dst.Col() != src.Col())
            dst = src;


    KImageGray colorImg[3]; // r,g,b 각각 쪼개는 함수

    for(int i=0; i<3; i++){
        colorImg[i].Create(src.Row(), src.Col());
    }

    // src r,g,b를 각각 대입, 초기화
    for(int nRow=0; nRow < src.Row(); nRow++){
        for(int nCol=0; nCol < src.Col(); nCol++){
            colorImg[0][nRow][nCol] = src[nRow][nCol].r;
            colorImg[1][nRow][nCol] = src[nRow][nCol].g;
            colorImg[2][nRow][nCol] = src[nRow][nCol].b;
        }
    }

    // 각각 histogram_equalization 수행
    for(int i=0; i<3; i++){
        histogram_equalization(colorImg[i],colorImg[i]);
    }

    // dst에 값 대입
    for(int nRow=0; nRow < src.Row(); nRow++){
        for(int nCol=0; nCol < src.Col(); nCol++){
            dst[nRow][nCol].r = colorImg[0][nRow][nCol];
            dst[nRow][nCol].g = colorImg[1][nRow][nCol];
            dst[nRow][nCol].b = colorImg[2][nRow][nCol];
        }
    }
}

// Input : Gray Image
// Output (dst) : Histogram Matching Image
// 히스토그램 매칭을 진행하는 함수
void taeyoungCV::histogram_matching(KImageGray &src, KImageGray &target)
{
    // histogram 구하기
    KHisto hOri, hDst;
    hOri.Histogram(src); hDst.Histogram(target);

    //accumulatied histgram
    double* ahOri = hOri.Address();
    for(int i=1; i<hOri.Dim(); i++) ahOri[i] += ahOri[i-1];

    double* ahDst = hDst.Address();
    for(int i=1; i<hDst.Dim(); i++) ahDst[i] += ahDst[i-1];

    //histogram equalization
    for(int i=0; i<hOri.Dim(); i++)
    ahOri[i] = ahOri[i]/(double)(src.Size());

    for(int i=0; i<hDst.Dim(); i++)
    ahDst[i] = ahDst[i]/(double)(src.Size());


    int     argmin = 0;
    double  argValue = 1.;

    for(int i=0; i<hOri.Dim(); i++){
        argValue = 1.;

        // 목표 Histogram의 CDF를 증가시켜가며, 기존의 Histogram의 CDF와 값이 가장 근접한 것을 채택한다.
        for(int j=0; j<hDst.Dim(); j++){
            if (argValue > abs(ahOri[i] - ahDst[j])){
                argValue = abs(ahOri[i] - ahDst[j]);
                argmin = j;
            }
        }
        ahOri[i] = argmin;
    }

    //transform the original image
    for(int nRow=0; nRow < src.Row(); nRow++){
        for(int nCol=0; nCol < src.Col(); nCol++){
            src[nRow][nCol] = ahOri[src[nRow][nCol]];
        }
    }

}

// Input : Color Image
// Output (dst) : Histogram Matching Image
// 히스토그램 매칭을 진행하는 함수
void taeyoungCV::histogram_matching(KImageColor &src, KImageColor &target)
{
    KImageGray tmpOri[3], tmpDst[3];

        for(int i=0; i<3; i++){
            tmpOri[i].Create(src.Row(), src.Col());
            tmpDst[i].Create(target.Row(), target.Col());
        }

        for(int nRow=0; nRow < src.Row(); nRow++){
            for(int nCol=0; nCol < src.Col(); nCol++){
                tmpOri[0][nRow][nCol] = src[nRow][nCol].r;
                tmpOri[1][nRow][nCol] = src[nRow][nCol].g;
                tmpOri[2][nRow][nCol] = src[nRow][nCol].b;
            }
        }

        for(int nRow=0; nRow < target.Row(); nRow++){
            for(int nCol=0; nCol < target.Col(); nCol++){
                tmpDst[0][nRow][nCol] = target[nRow][nCol].r;
                tmpDst[1][nRow][nCol] = target[nRow][nCol].g;
                tmpDst[2][nRow][nCol] = target[nRow][nCol].b;
            }
        }

        for(int i=0; i<3; i++){
            histogram_matching(tmpOri[i], tmpDst[i]);
        }

        for(int nRow=0; nRow < src.Row(); nRow++){
            for(int nCol=0; nCol < src.Col(); nCol++){
                src[nRow][nCol].r = tmpOri[0][nRow][nCol];
                src[nRow][nCol].g = tmpOri[1][nRow][nCol];
                src[nRow][nCol].b = tmpOri[2][nRow][nCol];
            }
        }
}

// Input : gray image, var value
// Output (dst) : Gaussian noise gray image
// 가우시안 노이즈를 만들어주는 함수
void taeyoungCV::getGaussianNoise(KImageGray &src, KImageGray &dst, double var)
{

    dst = src;  // src와 dst의 이미지의 크기를 같도록 만든다.
    double mean = 0.0;
    var = pow(var,2);

    // 평균은 0, 분산은 var에 의해서 Gaussian 생성
    KGaussian gaussian;
    gaussian.Create(mean,var);
    gaussian.OnRandom(src.Size());

    int pixelValue = 0;
    int noise = 0;

    for(int i = 0; i< src.Row();i++)
        for(int j = 0; j< src.Col();j++){
            pixelValue = src[i][j];
            noise = gaussian.Generate();

            // 새로운 노이즈 첨가된 pixel을 dst에 대입
            if(pixelValue + noise > 255){dst[i][j] = 255;}
            else if(pixelValue + noise < 0){dst[i][j] = 0;}
            else {
                dst[i][j] = pixelValue + noise;
            }

        }
}

// Input : color image, var value
// Output (dst) : Gaussian noise color image
// 가우시안 노이즈를 만들어주는 함수
void taeyoungCV::getGaussianNoise(KImageColor &src, KImageColor &dst, double var)
{
    // Color Image를 분리하여 각각 1 channel로 바꿔준다.
    KImageGray tmpSrc[3], tmpDst[3];

    dst = src;  // dst와 src를 같도록 만들어준다.

    // row,col을 이용하여 초기화
    for(int i =0; i<3; i++){
        tmpSrc[i].Create(src.Row(),src.Col());
        tmpDst[i].Create(dst.Row(),dst.Col());
    }

    // 각 pixel별로 대입
    for(int i =0; i<src.Row();i++){
        for(int j = 0; j<src.Col();j++){
            tmpSrc[0][i][j] = src[i][j].r;
            tmpSrc[1][i][j] = src[i][j].g;
            tmpSrc[2][i][j] = src[i][j].b;
        }
    }

    // 각 채널별로 가우시안 노이즈 생성
    for(int i =0; i<3; i++){
        getGaussianNoise(tmpSrc[i],tmpDst[i],var);
    }

    // 각 채널을 합쳐서 가우시안 노이즈 3채널 이미지 만들기
    for(int i =0; i<src.Row();i++){
        for(int j=0; j<src.Col();j++){
            dst[i][j].r = tmpDst[0][i][j];
            dst[i][j].g = tmpDst[1][i][j];
            dst[i][j].b = tmpDst[2][i][j];
        }
    }

}

// Input : gray image, probability value
// Output (dst) : Salt and pepper noise gray image
// Salt and pepper 노이즈를 만들어주는 함수
void taeyoungCV::getImpulseNoise(KImageGray &src, KImageGray &dst, double probability)
{
     dst = src;  // src와 dst의 이미지의 크기를 같도록 만든다.

     KRandom *rand = new KRandom(src.Row()*src.Col());  // 난수 생성

     for(int i = 0; i < src.Row();i++){
        for(int j = 0; j < src.Col(); j++){
            double dRan = rand->Generate();

            // dRan 숫자가 probability 안으로 들어올 경우
            if(dRan < probability){
                if(dRan < probability / 2.){dst[i][j] = 0;} // 반은 0으로 만든다.
                else {dst[i][j] = 255;} // 반은 255로 만든다.
            }
            else {
                dst[i][j] = src[i][j];
            }
        }
     }

     delete rand;

}

// Input : color image, probability value
// Output (dst) : Salt and pepper noise color image
// Salt and pepper 노이즈를 만들어주는 함수
void taeyoungCV::getImpulseNoise(KImageColor &src, KImageColor &dst, double probability)
{
    KCOLOR32 black(0,0,0);
    KCOLOR32 white(255,255,255);

    dst = src;  // src와 dst의 이미지의 크기를 같도록 만든다.

    KRandom *rand = new KRandom(src.Row()*src.Col());

    for(int i = 0; i < src.Row();i++){
       for(int j = 0; j < src.Col(); j++){
           double dRan = rand->Generate();  // 난수 생성

           // dRan 숫자가 probability 안으로 들어올 경우
           if(dRan < probability){
               if(dRan < probability / 2.){dst[i][j] = black;} // 반은 검은색으로 만든다.
               else {dst[i][j] = white;} // 반은 흰색으로 만든다.
           }
           else {
               dst[i][j] = src[i][j];
           }
       }
    }

    delete rand;

}

// Input : gray image, sigma value
// Output (dst) : gaussian filtering gray image
// 가우시안 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::gaussianFilter(KImageGray &src, KImageGray &dst, double sigma)
{
    dst = src;  // src와 dst의 이미지의 크기를 같도록 만든다.
    sigma = sqrt(sigma);

    //create the conv. mask
    int nHalf = (int)(3.0*sigma+0.3);
    // 1차원 커널 만들어서 두번 사용함(속도가 훨씬 빠르다)
    double* dGMask = new double[nHalf*2 + 1];

    double dScale = 0;
    double dConst = 1. / (2. * _PI * pow(sigma, 2));

    for(int i = -nHalf; i<=nHalf; i++){
        dGMask[i+nHalf] = dConst * exp( -(i*i) / (2*pow(sigma, 2) ) );
        dScale += dGMask[i+nHalf];
    }

    // Scaling
    for(int i = -nHalf; i<=nHalf; i++){
        dGMask[i+nHalf] /= dScale;
    }

    // Convolution
    // Col(x축) convolution 연산
    for(int i = nHalf;i < src.Row()-nHalf;i++){
        for(int j = nHalf; j < src.Col()-nHalf;j++){
            double pixVal = 0.0;
            for(int n = -nHalf; n <= nHalf; n++){
                pixVal += src[i][j + n] * dGMask[n + nHalf];
            }
            dst[i][j] = (unsigned char)pixVal;
        }
    }

    // Row(y축) convolution 연산
    for(int i = nHalf; i<src.Row()-nHalf;i++){
        for(int j = nHalf; j<src.Col()-nHalf;j++){
            double pixVal = 0.0;
            for(int n = -nHalf; n <= nHalf; n++){
                pixVal += src[i + n][j] * dGMask[n + nHalf];
            }
            dst[i][j] = (unsigned char)pixVal;
        }
    }

    delete[] dGMask;

}

// Input : color image, sigma value
// Output (dst) : gaussian filtering color image
// 가우시안 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::gaussianFilter(KImageColor &src, KImageColor &dst, double sigma)
{

    dst = src;  // dst와 src를 같도록 만들어준다.

    // Color Image를 분리하여 각각 1 channel로 바꿔준다.
    KImageGray tmpSrc[3], tmpDst[3];

    // row,col을 이용하여 초기화
    for(int i =0; i<3; i++){
        tmpSrc[i].Create(src.Row(),src.Col());
        tmpDst[i].Create(dst.Row(),dst.Col());
    }

    // 각 pixel별로 대입
    for(int i =0; i<src.Row();i++){
        for(int j = 0; j<src.Col();j++){
            tmpSrc[0][i][j] = src[i][j].r;
            tmpSrc[1][i][j] = src[i][j].g;
            tmpSrc[2][i][j] = src[i][j].b;
        }
    }

    // 각 채널별로 가우시안 필터 적용
    for(int i =0; i<3; i++){
        gaussianFilter(tmpSrc[i],tmpDst[i],sigma);
    }

    // 각 채널을 합쳐서 가우시안 필터 3채널 이미지 만들기
    for(int i =0; i<src.Row();i++){
        for(int j=0; j<src.Col();j++){
            dst[i][j].r = tmpDst[0][i][j];
            dst[i][j].g = tmpDst[1][i][j];
            dst[i][j].b = tmpDst[2][i][j];
        }
    }
}

// Input : gray image, kernal size
// Output (dst) : median filtering gray image
// 미디언 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::medianFilter(KImageGray &src, KImageGray &dst, double kernalSize)
{
    int kHalf = kernalSize / 2;
    int *mKernal = new int[(int)(kernalSize * kernalSize)];

    for(int i = kHalf; i < src.Row()-kHalf; i++){
        for(int j = kHalf; j < src.Col()-kHalf; j++){
            // 1. 커널에 픽셀 값을 저장한다.
            for(int i_k = -kHalf; i_k <= kHalf; i_k++){
                for(int j_k = -kHalf; j_k <= kHalf; j_k++){
                        mKernal[(i_k + kHalf)*(int)kernalSize +(j_k + kHalf)] = src[i + i_k][j + j_k];
                    }
            }


            // 2. 비교를 통하여 중간값 찾기
            // 오름차순으로 정렬하기
            for(int firstIdx = 0; firstIdx < kernalSize*kernalSize-1 ; firstIdx++){
                for(int secondIdx = firstIdx+1; secondIdx<kernalSize*kernalSize; secondIdx++){
                    if(mKernal[firstIdx] > mKernal[secondIdx]){
                        int tmp = mKernal[firstIdx];
                        mKernal[firstIdx] = mKernal[secondIdx];
                        mKernal[secondIdx] = tmp;
                    }
                }
            }

            // 3. 중간 값을 pixel 값으로 update
            dst[i][j] = mKernal[(int)floor(pow(kernalSize,2) / 2)];
        }
    }

    delete[] mKernal;
}

// Input : color image, kernal size
// Output (dst) : median filtering color image
// 미디언 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::medianFilter(KImageColor &src, KImageColor &dst, double kernalSize)
{
    dst = src;  // dst와 src를 같도록 만들어준다.

    // Color Image를 분리하여 각각 1 channel로 바꿔준다.
    KImageGray tmpSrc[3], tmpDst[3];

    // row,col을 이용하여 초기화
    for(int i =0; i<3; i++){
        tmpSrc[i].Create(src.Row(),src.Col());
        tmpDst[i].Create(dst.Row(),dst.Col());
    }

    // 각 pixel별로 대입
    for(int i =0; i<src.Row();i++){
        for(int j = 0; j<src.Col();j++){
            tmpSrc[0][i][j] = src[i][j].r;
            tmpSrc[1][i][j] = src[i][j].g;
            tmpSrc[2][i][j] = src[i][j].b;
        }
    }

    // 각 채널별로 미디언 필터 적용
    for(int i =0; i<3; i++){
        medianFilter(tmpSrc[i],tmpDst[i],kernalSize);
    }

    // 각 채널을 합쳐서 미디언 필터 3채널 이미지 만들기
    for(int i =0; i<src.Row();i++){
        for(int j=0; j<src.Col();j++){
            dst[i][j].r = tmpDst[0][i][j];
            dst[i][j].g = tmpDst[1][i][j];
            dst[i][j].b = tmpDst[2][i][j];
        }
    }
}

// Input : gray image, sigma value
// Output (dst) : median filtering gray image
// 미디언 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::boxFilter(KImageGray &src, KImageGray &dst, int kSize)
{
    int kHalf = kSize / 2;

    for(int i=kHalf; i< src.Row()-kHalf;i++){
        for(int j=kHalf; j< src.Col()-kHalf;j++){
            int sumPixel = 0;
            // 1. 커널에 픽셀 값을 모두 더하면서 저장한다.
            for(int i_k = -kHalf; i_k <= kHalf; i_k++){
                for(int j_k = -kHalf; j_k <= kHalf; j_k++){
                        sumPixel += src[i + i_k][j + j_k];
                    }
            }

            // 2. 픽셀 값들을 평균을 낸다.
            dst[i][j] = sumPixel / (kSize*kSize);

        }
    }

}

// Input : color image, sigma value
// Output (dst) : median filtering color image
// 미디언 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::boxFilter(KImageColor &src, KImageColor &dst, int kSize)
{
    dst = src;  // dst와 src를 같도록 만들어준다.

    // Color Image를 분리하여 각각 1 channel로 바꿔준다.
    KImageGray tmpSrc[3], tmpDst[3];

    // row,col을 이용하여 초기화
    for(int i =0; i<3; i++){
        tmpSrc[i].Create(src.Row(),src.Col());
        tmpDst[i].Create(dst.Row(),dst.Col());
    }

    // 각 pixel별로 대입
    for(int i =0; i<src.Row();i++){
        for(int j = 0; j<src.Col();j++){
            tmpSrc[0][i][j] = src[i][j].r;
            tmpSrc[1][i][j] = src[i][j].g;
            tmpSrc[2][i][j] = src[i][j].b;
        }
    }

    // 각 채널별로 박스 필터 적용
    for(int i =0; i<3; i++){
        boxFilter(tmpSrc[i],tmpDst[i],kSize);
    }

    // 각 채널을 합쳐서 박스 필터 3채널 이미지 만들기
    for(int i =0; i<src.Row();i++){
        for(int j=0; j<src.Col();j++){
            dst[i][j].r = tmpDst[0][i][j];
            dst[i][j].g = tmpDst[1][i][j];
            dst[i][j].b = tmpDst[2][i][j];
        }
    }
}

// Input : 흑백 이미지, Gaussian filtering sigma값
// Output (dst) : FDG output image
// FDG 알고리즘 적용 이미지
void taeyoungCV::FDG(KImageGray &src, KImageGray &dst, double sigma)
{

    dst = src;                  // dst와 src를 같도록 만들어준다.

    // 이전에 미분한 데이터가 있었다면 삭제
    if(!edgeData.empty()){
        for(int i=0; i< edgeData.size(); i++){
            delete edgeData[i];
        }

        edgeData.clear();
    }

    // 미분데이터를 담을 edgeData 초기화
    vector<EdgeData> *colEdge;  // edge 데이터의 열 성분들

    for(int i=0; i < src.Row(); i++){
        colEdge = new vector<EdgeData>(src.Col());  // pointer를 사용하였기에 이렇게 초기화
        edgeData.push_back(colEdge);
    }

////////////////////////////// FDG 시작///////////////////////////////

    int kHalf = 3*sigma + 0.3;

    // 2차원 커널 만들기
    double **GMaskX;    // x 방향 Gradient 계산
    double **GMaskY;    // y 방향 Gradient 계산

    // 커널 초기화
    GMaskX = new double*[kHalf*2 + 1];
    for(int nRow = 0; nRow< 2*kHalf + 1; nRow++){
        GMaskX[nRow] = new double[kHalf*2 + 1];
    }

    GMaskY = new double*[kHalf*2 + 1];
    for(int nRow = 0; nRow< 2*kHalf + 1; nRow++){
        GMaskY[nRow] = new double[kHalf*2 + 1];
    }

    double dScale = 0;
    double dConst = 1. / (2. * _PI * pow(sigma, 4) );
    double dTmp;

    for(int nRow = -kHalf; nRow<=kHalf; nRow++){
        dTmp = -nRow * exp(-(nRow*nRow)/(2. * pow(sigma, 2)));

        for(int nCol = -kHalf; nCol<=kHalf; nCol++){
            GMaskY[nRow+kHalf][nCol+kHalf] = dConst * dTmp * exp( -(nCol*nCol) / (2*pow(sigma, 2)));
            GMaskX[nCol+kHalf][nRow+kHalf] = GMaskY[nRow+kHalf][nCol+kHalf];

            if(nRow < 0) dScale += GMaskY[nRow+kHalf][nCol+kHalf];
        }
    }

    // Scaling
    for(int nRow = -kHalf; nRow<=kHalf; nRow++){
        for(int nCol = -kHalf; nCol<=kHalf; nCol++){
            GMaskX[nRow+kHalf][nCol+kHalf] /= -dScale;  // convolution 연산에서 대칭이동 하는 것
            GMaskY[nRow+kHalf][nCol+kHalf] /= -dScale;
        }
    }

    // Gradient 계산
    for(int nRow = kHalf; nRow < src.Row()-kHalf; nRow++){
        for(int nCol = kHalf; nCol < src.Col()-kHalf; nCol++){
            double tmpX = 0., tmpY = 0.;

            // 커널의 크기만큼 돌면서 계산
            // Convolution - 커널 * src 이미지
            for(int nKRow = -kHalf; nKRow<=kHalf; nKRow++){
                for(int nKCol = -kHalf; nKCol<=kHalf; nKCol++){
                    tmpX += GMaskX[nKRow+kHalf][nKCol+kHalf] * src[nRow+nKRow][nCol+nKCol];
                    tmpY += GMaskY[nKRow+kHalf][nKCol+kHalf] * src[nRow+nKRow][nCol+nKCol];
                }
            }

            // 결과 이미지에 값 대입
            dst[nRow][nCol] = abs(tmpX) + abs(tmpY);

            // edgeData에 값 대입
            edgeData[nRow]->at(nCol).magn  = abs(tmpX)+abs(tmpY);
            edgeData[nRow]->at(nCol).dx    = abs(tmpX) / sqrt(tmpX*tmpX + tmpY*tmpY);
            edgeData[nRow]->at(nCol).dy    = abs(tmpY) / sqrt(tmpX*tmpX + tmpY*tmpY);
            edgeData[nRow]->at(nCol).dir   = (unsigned char)((((int)(atan2(tmpY, tmpX) * (180.0/M_PI)/22.5)+1)>>1) & 0x00000003);
        }
    }


    // 데이터 삭제
    for(int i = 0; i< 2*kHalf + 1; i++){
        delete []GMaskX[i];
        delete []GMaskY[i];
    }

    delete []GMaskX;
    delete []GMaskY;
}


// Input : FDG 이미지, threshold1, threshold2, Gaussian filtering sigma값
// Output (dst) : Canny edge result image
// 캐니 엣지 알고리즘 적용 이미지
void taeyoungCV::cannyEdge(KImageGray &src, KImageGray &dst, int th1, int th2, double sigma)
{
    KImageGray FDGImage;

    // dst 초기화
    dst = KImageGray(src.Row(),src.Col());
    for(int i =0; i<src.Row(); i++){
        for(int j = 0; j < src.Col(); j++){
            dst[i][j] = 0;
        }
    }

    // 1. FDG algorithm
    FDG(src,FDGImage,sigma);

    // 2. Non-Maxima Suppression
    int nDx[4] = {+1, +1, 0, -1};
    int nDy[4] = { 0, +1, +1, +1};

    for(int Row = 1; Row < src.Row() -1; Row++){
        for(int Col = 1; Col < src.Col() -1; Col++){
            int tmpdir = edgeData[Row]->at(Col).dir;

            // 현재 Gradient가 가장 크다면
            // tmpdir으로 양 옆을 조사
            if((edgeData[Row]->at(Col).magn > edgeData[Row + nDy[tmpdir]]->at(Col + nDx[tmpdir]).magn) &&
               (edgeData[Row]->at(Col).magn > edgeData[Row - nDy[tmpdir]]->at(Col - nDx[tmpdir]).magn)){

                // Threshold 2보다 큰 Magnitude를 가진 edge는 확실한 edge로 판별
                if(edgeData[Row]->at(Col).magn > th2){
                    dst[Row][Col] = Fore_Ground;
                }

                // Threshold 1보다 작은 Magnitude를 가진 edge는 확실히 edge가 아닌걸로 판별
                else if(edgeData[Row]->at(Col).magn < th1){
                    dst[Row][Col] = Back_Ground;
                }
            }

            // 주변 Gradient보다 크지 않다면
            else{
                edgeData[Row]->at(Col).magn = 0;
            }
        }
    }

    // 3. Hysteresis Thresholding

    stack<pair<int,int>> pointStack;    // 주변 검사를 계속 해야함으로 Stack을 사용

    for(int Row = 0; Row < dst.Row(); Row++){
        for(int Col = 0; Col < dst.Col(); Col++){

            // 확실한 edge라면 stack을 사용해서 주변을 탐색해 t1과 t2사이의 값을 찾아내 연결해준다.
            if(dst[Row][Col] == Fore_Ground){
                pointStack.push(make_pair(Row,Col));

                while(!pointStack.empty()){
                    //qDebug() << "pointStack start";
                    // 확실한 edge의 Col과 Row를 선언
                    int tmpRow = pointStack.top().first;
                    int tmpCol = pointStack.top().second;

                    // 그리고 pointStack pop
                    pointStack.pop();

                    // 확실한 edge 주변의 중간 값을 엣지로써 추가시켜준다.
                    for(int i = 0; i<8; i++){
                        // 모서리를 벗어나면 패스
                        if(tmpRow + eightNeighborRow[i] == -1 || tmpRow + eightNeighborRow[i]== dst.Row() ||
                                tmpCol + eightNeighborCol[i] == -1 || tmpCol + eightNeighborCol[i] == dst.Col()){
                            continue;
                        }

                        // 중간 edge가 threshold 2보다 크고 확실한 edge와 연결되어 있다면
                        if((edgeData[tmpRow + eightNeighborRow[i]]->at(tmpCol + eightNeighborCol[i]).magn > th2) && (dst[Row][Col] != Fore_Ground)){
                            // 중간 edge를 확실한 edge로 update
                            dst[tmpRow + eightNeighborRow[i]][tmpCol + eightNeighborCol[i]] = Fore_Ground;
                            // 중간 edge 주위를 다시 조사하기 위하여 stack에 추가
                            pointStack.push(make_pair(tmpRow + eightNeighborRow[i], tmpCol + eightNeighborCol[i]));

                        }
                    }
                }
            }
        }
    }

}

// 반지름을 알 때 Hough Transform
// Input : Gray image, Result를 표시할 Image, 반지름, Threshold
// Output (dst) : Hough Transform을 표시한 Result Image(dst), Point의 모음(Hough Transform 결과)
void taeyoungCV::circleHoughTransform(KImageGray &src, KImageColor &dst, int radius, int threshold)
{
    KImageGray edgedst;
    // canny edge를 이용하여 edge Image 검출
    // Threshold는 임의적으로 정해줌
    cannyEdge(src,edgedst,1,10,1.5);
    KImageDouble dstImg(src.Row(), src.Col());

    int tmpCol = 0, tmpRow = 0;

    for(int nRow=0; nRow< edgedst.Row(); nRow++){
        for(int nCol=0; nCol< edgedst.Col(); nCol++){

            // edge 일때,
            if(edgedst[nRow][nCol] == Fore_Ground){

                // 기울기로 거리를 구한다. (+) 방향 //
                tmpCol = nCol + (edgeData[nRow]->at(nCol).dx * (double)radius);
                tmpRow = nRow + (edgeData[nRow]->at(nCol).dy * (double)radius);

                // 이미지 범위를 벗어나면 무시한다.
                if(tmpCol < 0 || tmpRow < 0 || tmpCol >= src.Col() || tmpRow >= src.Row()){
                    continue;
                }

                for(int i=-5;i<6;i++){
                    for(int j=-5; j<6; j++){

                        // 이미지 범위를 벗어나면 무시한다.
                        if(tmpCol+j < 0 || tmpRow+i < 0 || tmpCol+j >= src.Col() || tmpRow+i >= src.Row()){
                            continue;
                        }

                        dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                        dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                        dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                    }
                }

                tmpCol = 0, tmpRow = 0;

                // 기울기로 거리를 구한다. (-) 방향 //
                tmpCol = nCol - (edgeData[nRow]->at(nCol).dx * (double)radius);
                tmpRow = nRow - (edgeData[nRow]->at(nCol).dy * (double)radius);

                // 이미지 범위를 벗어나면 무시한다.
                if(tmpCol < 0 || tmpRow < 0 || tmpCol >= src.Col() || tmpRow >= src.Row()){
                    continue;
                }

                for(int i=-5;i<5;i++){
                    for(int j=-5; j<6; j++){

                        // 이미지 범위를 벗어나면 무시한다.
                        if(tmpCol+j < 0 || tmpRow+i < 0 || tmpCol+j >= src.Col() || tmpRow+i >= src.Row()){
                            continue;
                        }

                        dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                        dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                        dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                    }
                }
            }
        }
    }

    // Points 선언
    _POINTS points;

    KImageGray dstGray;

    dstGray = dstImg.ToGray(_USER_SCALING);
    dst = dstGray.GrayToRGB();


    // Non-Maxima Suppression
    for(int nRow=1; nRow<dstGray.Row()-1; nRow++){
        for(int nCol=1; nCol<dstGray.Col()-1; nCol++){
            if(dstGray[nRow][nCol] >= threshold){

                bool isMax = true;

                for(int i = 0; i < 8 ; i++){
                    if(dstGray[nRow][nCol] < dstGray[nRow + eightNeighborRow[i]][nCol + eightNeighborCol[i]]){
                        isMax = false;
                        break;
                    }
                }

                if(isMax)  points.push_back(make_pair(nRow, nCol));
            }
        }
    }

    // 검출된 좌표를 초록색 점으로 바꿔준다.
    for(int i=0; i < points.size(); i++){
        tmpRow = points[i].first;
        tmpCol = points[i].second;

        dst[tmpRow][tmpCol].r = 0;
        dst[tmpRow][tmpCol].g = 255;
        dst[tmpRow][tmpCol].b = 0;
    }
}

// Templete이 존재할 때 Generanlized Hough Transform
// Input : Gray image, Templete txt file directory, Threshold
// Output (dst) : Hough Transform을 표시한 Result Image(dst), Point의 모음(Hough Transform 결과)
void taeyoungCV::generalizedHoughTransform(KImageGray &src, KImageColor &dst, string dir, int threshold)
{
    vector<pair<int,int>> points;
    vector<pair<double,double>> mTable[4];
    KImageDouble dstImg(src.Row(), src.Col());

    // 파일 읽는 부분
    ifstream fin;
    fin.open(dir);

    int nRow, nCol;
    long    centerRow=0, centerCol=0;

    while(! fin.eof()){
        fin >> nRow >> nCol;
        points.push_back(make_pair(nRow, nCol));
    }
    if(fin.is_open())    fin.close();

    // 중심점 계산
   for(int i=0; i<points.size(); i++){
       centerRow += points[i].first;
       centerCol += points[i].second;
   }

   centerRow /= points.size();
   centerCol /= points.size();


   /////////// table 생성 ///////////
   double nTmp;
   int nDir;   //edge 방향
   double nDist, nAng;

   for(int j=1, jj=points.size()-2; jj; j++,jj--) {

       //에지 방향 설정 - 양 옆 점의 기울기로 부터 에지 방향 계산
       nTmp = _DEGREE( atan2((float)(points[j+1].first - points[j-1].first),
                                       (float)(points[j+1].second - points[j-1].second) + 1e-8));
       nTmp += 90.0; //에지 방향(0~360)
       nDir = ((((int)(abs(nTmp)/22.5)+1)>>1) & 0x00000003); //에지 방향(0~3)
       //중심과의 거리
       nDist = sqrt(_SQR(centerCol - points[j].second) + _SQR(centerRow - points[j].first));

       //중심과 이루는 각도
       nAng = _DEGREE(atan2(points[j].first - centerRow, points[j].second - centerCol + 1e-8));

       //형상 테이블에 추가
       mTable[nDir].push_back(make_pair(nDist, nAng));
   }
   /////////// table 생성 ///////////

   /////////// edge 추출 ///////////
   KImageGray edgeImg;
   cannyEdge(src,edgeImg,1,10,1.5);

   int tmpCol, tmpRow;
   int degreeFactor = 4;

   for(int nRow=0; nRow<edgeImg.Row(); nRow++){
       for(int nCol=0; nCol<edgeImg.Col(); nCol++){

           // edge 일때,
           if(edgeImg[nRow][nCol] == 255){

               for(int nTheta = 0; nTheta < degreeFactor; nTheta++){
                   // 같은 방향의 table을 찾고,
                   //int tmpDir = edgeData[nRow]->at(nCol).dir;
                   int tmpDir = (unsigned char)((((int)( (atan2(edgeData[nRow]->at(nCol).dy, edgeData[nRow]->at(nCol).dx)
                                                          * (180.0/M_PI) - 360/ degreeFactor * nTheta) /22.5)+1)>>1) & 0x00000003);

                   // 그 안의 데이터를 모두 넣는다.
                   for(int i=0; i< mTable[tmpDir].size(); i++){

                       for(double nScale = 1.; nScale <= 1.; nScale += 0.05){
                           // 기울기로 거리를 구한다.
                           tmpCol = nCol + nScale * mTable[tmpDir][i].first * cos(_RADIAN(mTable[tmpDir][i].second + 360/ degreeFactor * nTheta));
                           tmpRow = nRow + nScale * mTable[tmpDir][i].first * sin(_RADIAN(mTable[tmpDir][i].second + 360/ degreeFactor * nTheta));

                           // 이미지 범위를 벗어나면 무시한다.
                           if(tmpCol < 0 || tmpRow < 0 || tmpCol >= src.Col() || tmpRow >= src.Row()){
                               continue;
                           }

                           //votes to avoid edge noises - 노이즈로 인해 제대로 추적을 못할 수 있다. 주변의 값에도 voting을 해준다.
                           for(int i=-5; i<6; i++){
                               for(int j=-5; j<6; j++){

                                   // 이미지 범위를 벗어나면 무시한다.
                                   if(tmpCol+j < 0 || tmpRow+i < 0 || tmpCol+j >= src.Col() || tmpRow+i >= src.Row()){
                                       continue;
                                   }

                                   dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                                   dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                                   dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                               }
                           }

                           // 기울기로 거리를 구한다.
                           tmpCol = nCol - nScale * mTable[tmpDir][i].first * cos(_RADIAN(mTable[tmpDir][i].second + 360/ degreeFactor * nTheta));
                           tmpRow = nRow - nScale * mTable[tmpDir][i].first * sin(_RADIAN(mTable[tmpDir][i].second + 360/ degreeFactor * nTheta));

                           // 이미지 범위를 벗어나면 무시한다.
                           if(tmpCol < 0 || tmpRow < 0 || tmpCol >= src.Col() || tmpRow >= src.Row()){
                               continue;
                           }

                           //votes to avoid edge noises - 노이즈로 인해 제대로 추적을 못할 수 있다. 주변의 값에도 voting을 해준다.
                           for(int i=-5; i<6; i++){
                               for(int j=-5; j<6; j++){

                                   // 이미지 범위를 벗어나면 무시한다.
                                   if(tmpCol+j < 0 || tmpRow+i < 0 || tmpCol+j >= src.Col() || tmpRow+i >= src.Row()){
                                       continue;
                                   }

                                   dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                                   dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];
                                   dstImg[tmpRow+i][tmpCol+j] += gaussianVoting[i+5][j+5];

                               }
                           }
                       }
                   }
               }

           }
       }
   }
   /////////// edge 추출 ///////////


   points.clear();
   //qDebug() <<points.size();


   // Points 선언
   _POINTS p;

   KImageGray dstGray;

   dstGray = dstImg.ToGray(_USER_SCALING);
   dst = dstGray.GrayToRGB();

   // Non-Maxima Suppression
   for(int nRow=1; nRow<dstGray.Row()-1; nRow++){
       for(int nCol=1; nCol<dstGray.Col()-1; nCol++){
           if(dstGray[nRow][nCol] >= threshold){

               bool isMax = true;

               for(int i = 0; i < 8 ; i++){
                   if(dstGray[nRow][nCol] < dstGray[nRow + eightNeighborRow[i]][nCol + eightNeighborCol[i]]){
                       isMax = false;
                       break;
                   }
               }

               if(isMax)  p.push_back(make_pair(nRow, nCol));
           }
       }
   }

   // 검출된 좌표를 보라색 점으로 바꿔준다.
   for(int i=0; i < p.size(); i++){
       tmpRow = p[i].first;
       tmpCol = p[i].second;

       dst[tmpRow][tmpCol].r = 255;
       dst[tmpRow][tmpCol].g = 0;
       dst[tmpRow][tmpCol].b = 255;
   }

}

// Input : Source Image, 가우시안 이미지를 만드는데 필요한 sigma
// Ouput : 가우시안 Scale Image 정보가 담긴 KImageDouble형 이미지들의 벡터
// 원본 이미지에서 가우시안 scale의 이미지를 만들어 주는 함수
_ScaleSpace taeyoungCV::getGaussianScaleImage(KImageGray &src, double sigma)
{
    _ScaleSpace result;

    int n = 6; // S = 3일때, 가장 좋은 keypoint를 찾을 수 있음

    for(int i =0;i < n;i++){
        double exp = (double)i / 3.0;
        double scaleFactor = pow(2.0,exp);
        KImageDouble gaussianResult;
        gaussianFilter(src,gaussianResult, (scaleFactor * sigma)); // gaussian Filter를 적용한 이미지 생성
        result.push_back(gaussianResult);               // Image 모음에 push back
    }

    return result;
}

// Input : gray image, sigma value
// Output (dst) : gaussian filtering double image
// 가우시안 필터링이 적용된 이미지를 만들어주는 함수
void taeyoungCV::gaussianFilter(KImageGray &src, KImageDouble &dst, double sigma)
{
    dst.Create(src.Row(),src.Col());  // src와 dst의 이미지의 크기를 같도록 만든다.

    sigma = sqrt(sigma);

    //create the conv. mask
    int nHalf = (int)(3.0*sigma+0.3);
    // 1차원 커널 만들어서 두번 사용함(속도가 훨씬 빠르다)
    double* dGMask = new double[nHalf*2 + 1];

    double dScale = 0;
    double dConst = 1. / (2. * _PI * pow(sigma, 2));

    for(int i = -nHalf; i<=nHalf; i++){
        dGMask[i+nHalf] = dConst * exp( -(i*i) / (2*pow(sigma, 2) ) );
        dScale += dGMask[i+nHalf];
    }

    // Scaling
    for(int i = -nHalf; i<=nHalf; i++){
        dGMask[i+nHalf] /= dScale;
    }

    // Convolution
    // Col(x축) convolution 연산
    for(int i = nHalf;i < src.Row()-nHalf;i++){
        for(int j = nHalf; j < src.Col()-nHalf;j++){
            double pixVal = 0.0;
            for(int n = -nHalf; n <= nHalf; n++){
                pixVal += src[i][j + n] * dGMask[n + nHalf];
            }
            dst[i][j] = pixVal;
        }
    }

    // Row(y축) convolution 연산
    for(int i = nHalf; i<src.Row()-nHalf;i++){
        for(int j = nHalf; j<src.Col()-nHalf;j++){
            double pixVal = 0.0;
            for(int n = -nHalf; n <= nHalf; n++){
                pixVal += src[i + n][j] * dGMask[n + nHalf];
            }
            dst[i][j] = pixVal;
        }
    }

    delete[] dGMask;
}

// Input : gray image, sigma value
// Output : Octave space 별로 Scale space KImageDouble 이미지를 담아줌 (vector 형을 return)
// Gray image를 Input으로 넣으면 4개의 Octave space에 대해서 각각 Scale space를 구하고 vector에 담는다.
_OctaveSpace taeyoungCV::getOctaveSpace(KImageGray &src, double sigma)
{
    KImageGray tmpGray = src;
    int nOctaveLayers = 4;
    _OctaveSpace result;

    // Octave Scale 만큼 돌면서 Scale space 별로 Octave space에 저장
    for(int i = 0; i<nOctaveLayers; i++){
        _ScaleSpace currentScaleSpace;
        // 현재 scale space image 생성
        currentScaleSpace = getGaussianScaleImage(tmpGray,sigma);

        result.push_back(currentScaleSpace); // 현재 scalespace를 Octave space에 저장
        tmpGray = tmpGray.HalfSize();   // 반으로 줄임
    }

    return result;
}

// Input : gray image, sigma value
// Output : Octave space 별로 DOG space KImageDouble 이미지를 담아줌 (vector 형을 return)
// Gray image를 Input으로 넣으면 4개의 Octave space에 대해서 각각 Scale space를 구하고 vector에 담는다.
_OctaveSpace taeyoungCV::getDOG_OctaveSpace(KImageGray &src, double sigma)
{
    KImageGray tmpGray = src;
    int nOctaveLayers = 4;
    _OctaveSpace result;

    // Octave Scale 만큼 돌면서 Scale space 별로 Octave space에 저장
    for(int i = 0; i<nOctaveLayers; i++){
        _ScaleSpace currentScaleSpace;  // 현재 scale space image 생성
        _ScaleSpace currentDogSpace;    // 현재 DOG space image 생성

        currentScaleSpace = getGaussianScaleImage(tmpGray,sigma);
        currentDogSpace = getDogScaleImage(currentScaleSpace);

        result.push_back(currentDogSpace); // 현재 DOGspace를 Octave space에 저장

        tmpGray = tmpGray.HalfSize();   // 반으로 줄임
    }

    return result;
}

// Input : Octave space 별로 Scale space KImageDouble 이미지
// Output : KImageGray 이미지 (모든 scale 별 이미지를 띄우기 위함)
// Octave space 별로 담겨 있는 벡터를 가지고 와서 화면을 띄우기 위한 하나의 KImageGray로 만들어줌
KImageGray taeyoungCV::getMergeOctaveSpace(_OctaveSpace &octave)
{
    int octave_size = octave.size();
    // octave 중에 가장 크기가 큰 Scale space를 선택하고 그중 첫번째 이미지의 Row 값
    int merged_row = octave[0][0].Row() * 3;
    // octave 중에 가장 크기가 큰 Scale space를 선택하고 그중 첫번째 이미지의 Col 값
    int merged_col = octave[0][0].Col() * octave_size;

    // 모니터 해상도에 맞추기 위함
    if(merged_col >= 1920){
        merged_col = 1920;
    }

    // 최종 결과를 담을 KImageGray 값
    KImageGray merged_octave_img(merged_row, merged_col);

    int sumOfPrevRow = 0;
    for(int octaveLayer = 0; octaveLayer < octave_size; octaveLayer++){
         // octave 별로 세로로 이어 붙인다
        vector<KImageDouble> img_vec = octave[octaveLayer];

        int img_vec_size = img_vec.size();
        int each_row = img_vec[octaveLayer].Row();    // scale space 이미지 크기가 모두 같으므로 그냥 첫번째꺼 가져옴.
        int each_col = img_vec[octaveLayer].Col();
        int poor_col = 0;

        for(int img = 0; img<img_vec_size; img++){
            // 한 octave 내의 이미지를 가로로 이어 붙인다.
            KImageGray scaleSpaceImg = img_vec[img].ToGray(_USER_SCALING);

            // 모든 scale space 이미지를 순서대로 병합
            for(int i = 0; i < each_row; i++){
                for(int j = 0; j <each_col; j++){
                    merged_octave_img[i + sumOfPrevRow][j + (img-poor_col) * each_col] = scaleSpaceImg[i][j];
                }
            }

            // 다음에 이어 붙일 이미지가 존재하지만 모니터의 가로 길이가 부족할 때 한 칸 아래로 내림
            if(each_col -1 + ((img - poor_col) + 1) * each_col > merged_col && img + 1 < img_vec_size){
                sumOfPrevRow += each_row;
                poor_col = img + 1;
            }
        }

        sumOfPrevRow += each_row;
    }

    return merged_octave_img;
}

// Input : Gray Image, Dog scale Octave, sigma
// Output : Visulaize를 위한 3채널 Color image
// Dog space에서 scale-space extrema를 적용
KImageColor taeyoungCV::getVisualizeKeyPointDetection(KImageGray &src, _OctaveSpace &octave, double sigma)
{
    KImageColor keypoint_detection_img = src.GrayToRGB();   // gray image를 color로 변환
    keyPoints.clear();  // 전에 남아있던 것을 처리 하기 위함

    for (int octaveNum = 0; octaveNum < octave.size(); octaveNum++) {
           _ScaleSpace img_vect = octave[octaveNum];

           // Scale space Extrema Detection
           int img_que_size = img_vect.size();
           int row = img_vect.front().Row();
           int col = img_vect.front().Col();

           int maxima_compare = 0;

           KImageDouble lower_img, current_img, upper_img;
           lower_img = img_vect[maxima_compare++];
           current_img = img_vect[maxima_compare++];

           // Image normalization [0, 1]
           for (int i = 0; i < row; i++) {
               for (int j = 0; j < col; j++) {
                   lower_img[i][j] /= 255.0;
                   current_img[i][j] /= 255.0;
               }
           }

           for (; maxima_compare <= img_que_size-1 ; maxima_compare++) {
               upper_img = img_vect[maxima_compare];

               // Image normalization [0, 1]
               for (int i = 0; i < row; i++) {
                   for (int j = 0; j < col; j++) {
                       upper_img[i][j] /= 255.0;
                   }
               }

               for (int i = 6; i < row - 6; i++) {
                   for (int j = 6; j < col - 6; j++) {
                       double v = current_img[i][j];

                       // Keypoint Filtering : DoG smaller than 0.03
                       if (v < 0.03) {
                           continue;
                       }

                       // 아래 neighbor 중에 현재 픽셀 값보다 큰 값이 존재하면
                       if (lower_img[i - 1][j - 1] >= v || lower_img[i - 1][j] >= v || lower_img[i - 1][j + 1] >= v ||
                           lower_img[i][j - 1] >= v     || lower_img[i][j] >= v     || lower_img[i][j + 1] >= v ||
                           lower_img[i + 1][j - 1] >= v || lower_img[i + 1][j] >= v || lower_img[i + 1][j + 1] >= v) {
                           continue;
                       }
                       // neighbor 중에 현재 픽셀 값보다 큰 값이 존재하면
                       else if (current_img[i - 1][j - 1] >= v || current_img[i - 1][j] >= v || current_img[i - 1][j + 1] >= v ||
                                current_img[i][j - 1] >= v     ||                               current_img[i][j + 1] >= v ||
                                current_img[i + 1][j - 1] >= v || current_img[i + 1][j] >= v || current_img[i + 1][j + 1] >= v) {
                           continue;
                       }
                       // 위 neighbor 중에 현재 픽셀 값보다 큰 값이 존재하면
                       else if(upper_img[i - 1][j - 1] >= v || upper_img[i - 1][j] >= v || upper_img[i - 1][j + 1] >= v ||
                               upper_img[i][j - 1] >= v     || upper_img[i][j] >= v     || upper_img[i][j + 1] >= v ||
                               upper_img[i + 1][j - 1] >= v || upper_img[i + 1][j] >= v || upper_img[i + 1][j + 1] >= v) {
                           continue;
                       }

                       // Reject points with strong edge response in one direction only
                       double b = pow(__EdgePeakThresh + 1, 2) / __EdgePeakThresh;
                       double d_xx = current_img[i][j + 1] + current_img[i][j - 1] - 2 * v;
                       double d_yy = current_img[i + 1][j] + current_img[i - 1][j] - 2 * v;
                       double d_xy = ((current_img[i + 1][j + 1] - current_img[i + 1][j - 1]) - (current_img[i - 1][j + 1] - current_img[i - 1][j - 1])) / 4.0;
                       double tr_h = d_xx + d_yy;
                       double det_h = d_xx * d_yy - d_xy * d_xy;
                       double a = tr_h * tr_h / det_h;
                       if (a < b) {
                           continue;
                       }

                       // Draw Keypoints on origin image
                       int origin_i = i * (octaveNum + 1);
                       int origin_j = j * (octaveNum + 1);
                       for (int k = 1; k <= 3; k++) {
                           keypoint_detection_img[origin_i - k][origin_j].r = 255;
                           keypoint_detection_img[origin_i - k][origin_j].g = 255;
                           keypoint_detection_img[origin_i - k][origin_j].b = 0;

                           keypoint_detection_img[origin_i][origin_j - k].r = 255;
                           keypoint_detection_img[origin_i][origin_j - k].g = 255;
                           keypoint_detection_img[origin_i][origin_j - k].b = 0;

                           keypoint_detection_img[origin_i][origin_j].r = 255;
                           keypoint_detection_img[origin_i][origin_j].g = 255;
                           keypoint_detection_img[origin_i][origin_j].b = 0;

                           keypoint_detection_img[origin_i][origin_j + k].r = 255;
                           keypoint_detection_img[origin_i][origin_j + k].g = 255;
                           keypoint_detection_img[origin_i][origin_j + k].b = 0;

                           keypoint_detection_img[origin_i + k][origin_j].r = 255;
                           keypoint_detection_img[origin_i + k][origin_j].g = 255;
                           keypoint_detection_img[origin_i + k][origin_j].b = 0;
                       }
                   }
               }

               lower_img = current_img;
               current_img = upper_img;
           }
       }

    return keypoint_detection_img;

}

// Input : Gray Image, Dog scale Octave, sigma
// Output : Key point Info가 저장된 벡터
// Dog space에서 scale-space extrema를 적용
// getKeyPointDetecion과 동일한 구조 but output이 Keypoint Info Vector
_KeypointInfo taeyoungCV::getKeyPointDetection(_OctaveSpace &octave)
{
    KeypointInfoVec.empty();   // 처음에 초기화를 시켜준다.

    // 옥타브를 for문으로 돌면서 검사
    for (int octaveNum = 0; octaveNum < octave.size(); octaveNum++) {

           _ScaleSpace img_vect = octave[octaveNum];    // 하나의 스케일 이미지 벡터

           // Scale space Extrema Detection
           int img_que_size = img_vect.size();
           int row = img_vect.front().Row();
           int col = img_vect.front().Col();

           int maxima_compare = 0;

           KImageDouble lower_img, current_img, upper_img;
           lower_img = img_vect[maxima_compare++];
           current_img = img_vect[maxima_compare++];

           // Image normalization [0, 1]
           for (int i = 0; i < row; i++) {
               for (int j = 0; j < col; j++) {
                   lower_img[i][j] /= 255.0;    // 이미지 Min max normalization을 하는게 더 좋을듯
                   current_img[i][j] /= 255.0;
               }
           }

           for (; maxima_compare <= img_que_size-1 ; maxima_compare++) {

               upper_img = img_vect[maxima_compare];     // 가져오는 3개의 이미지 중 위에 이미지 초기화

               // Image normalization [0, 1]
               for (int i = 0; i < row; i++) {
                   for (int j = 0; j < col; j++) {
                       upper_img[i][j] /= 255.0;
                   }
               }

               // key point 검사 start - 나중에 필터의 크기를 생각해서 5부터 시작
               for (int i = 6; i < row - 6; i++) {
                   for (int j = 6; j < col - 6 ; j++) {
                       double v = current_img[i][j];

                       // Keypoint Filtering : DoG smaller than 0.01    // 조절하면서 적절한 값 찾아야 함.
                       if (v < 0.03) {
                           continue;
                       }

                       // 아래 neighbor 중에 현재 픽셀 값보다 큰 값이 존재하면
                       if (lower_img[i - 1][j - 1] >= v || lower_img[i - 1][j] >= v || lower_img[i - 1][j + 1] >= v ||
                           lower_img[i][j - 1] >= v     || lower_img[i][j] >= v     || lower_img[i][j + 1] >= v ||
                           lower_img[i + 1][j - 1] >= v || lower_img[i + 1][j] >= v || lower_img[i + 1][j + 1] >= v) {
                           continue;
                       }
                       // neighbor 중에 현재 픽셀 값보다 큰 값이 존재하면
                       else if (current_img[i - 1][j - 1] >= v || current_img[i - 1][j] >= v || current_img[i - 1][j + 1] >= v ||
                                current_img[i][j - 1] >= v     ||                               current_img[i][j + 1] >= v ||
                                current_img[i + 1][j - 1] >= v || current_img[i + 1][j] >= v || current_img[i + 1][j + 1] >= v) {
                           continue;
                       }
                       // 위 neighbor 중에 현재 픽셀 값보다 큰 값이 존재하면
                       else if(upper_img[i - 1][j - 1] >= v || upper_img[i - 1][j] >= v || upper_img[i - 1][j + 1] >= v ||
                               upper_img[i][j - 1] >= v     || upper_img[i][j] >= v     || upper_img[i][j + 1] >= v ||
                               upper_img[i + 1][j - 1] >= v || upper_img[i + 1][j] >= v || upper_img[i + 1][j + 1] >= v) {
                           continue;
                       }

                       // Reject points with strong edge response in one direction only
                       double b = pow(__EdgePeakThresh + 1, 2) / __EdgePeakThresh;
                       double d_xx = current_img[i][j + 1] + current_img[i][j - 1] - 2 * v;
                       double d_yy = current_img[i + 1][j] + current_img[i - 1][j] - 2 * v;
                       double d_xy = ((current_img[i + 1][j + 1] - current_img[i + 1][j - 1]) - (current_img[i - 1][j + 1] - current_img[i - 1][j - 1])) / 4.0;
                       double tr_h = d_xx + d_yy;
                       double det_h = d_xx * d_yy - d_xy * d_xy;
                       double a = tr_h * tr_h / det_h;
                       if (a < b) {
                           continue;
                       }

                       // Save Keypoints info
                       int keypoint_x = j * (octaveNum + 1);
                       int keypoint_y = i * (octaveNum + 1);
                       int sigmaIdx = maxima_compare -1;

                       KeypointAndSigma keypointInfo;
                       keypointInfo.x = keypoint_x;
                       keypointInfo.y = keypoint_y;
                       keypointInfo.sigmaIdx = sigmaIdx;

                       KeypointInfoVec.push_back(keypointInfo);
                   }
               }

               lower_img = current_img;
               current_img = upper_img;
           }
       }

    return KeypointInfoVec;
}

// Input : 가우시안 Scale Image 정보가 담긴 KImageDouble형 이미지들의 벡터
// Output : Scale space 별로 DOG space KImageDouble 이미지를 담아줌 (vector 형을 return)
// 가우시안 Scale Image 정보가 담긴 KImageDouble형 이미지들의 벡터를 Input으로 넣으면
// 각각 DOG space를 구하고 vector에 담는다.
_ScaleSpace taeyoungCV::getDogScaleImage(_ScaleSpace &src)
{
    int ScaleSize = src.size(); // scale space의 갯수 - 6
    _ScaleSpace result;    // 결과 값을 저장하기 위해서

    // Scale 별로 for문을 돈다.
    for(int ScaleNum = 0; ScaleNum < ScaleSize; ScaleNum++){
        int nextScaleNum = ScaleNum+1;
        // +1 증가했을 때 벡터 사이즈를 안 넘기 위해서
        if(nextScaleNum == ScaleSize ){
            continue;
        }

        KImageDouble currentScaleImg = src[ScaleNum];
        KImageDouble nextScaleImg = src[nextScaleNum];
        KImageDouble currentDogImg(currentScaleImg.Row(),currentScaleImg.Col());    // Dog 값 저장을 위해서

        // pixel 하나씩 돌 때마다, 스케일이 큰 이미지에서 작은 이미지의 차이를 구해준다.

        for(int nRow = 0; nRow < currentScaleImg.Row(); nRow++){
            for(int nCol = 0; nCol < currentScaleImg.Col();nCol++){
                currentDogImg[nRow][nCol] = (nextScaleImg[nRow][nCol] - currentScaleImg[nRow][nCol]) * 10;
                // 10을 곱해준 이유는 값의 차이가 너무 없기 때문에 나중에 keypoint detection시 scale이 작아 처리하기 어렵기 때문이다..
            }
        }

        result.push_back(currentDogImg);
    }

    return result;
}

// Input : Keypoint와 Sigma값 정보가 들어있는 KeypointsInfo, 가우시안 스케일 이미지모음이 있는 벡터(scalespace)
// Output :Keypoint magnitude와 theta 정보가 들어있는 key point vector
// keypoint를 하나씩 꺼내서 magnitude와 theta를 계산하고 output으로 Keypoint 정보가 들어있는 벡터를 반환
_KeyPointVec taeyoungCV::getKeyPointOrientation(_KeypointInfo &keypointsInfo, _ScaleSpace &scaleImage)
{
    _KeyPointVec resultPointVec;

    // for문을 돌면서 keypoint를 하나씩 꺼낸다.
    for(int keyPointIdx = 0; keyPointIdx < keypointsInfo.size(); keyPointIdx++){
        // 각각 Sigma scale Image를 가져오기 위해서
        for(int Idx = 1; Idx <= 3; Idx++){

            int point_x = keypointsInfo[keyPointIdx].x;
            int point_y = keypointsInfo[keyPointIdx].y;
            int point_sigma = keypointsInfo[keyPointIdx].sigmaIdx;

            // 가져온 sigma index만족할 때
            if(Idx == point_sigma){

                KeyPointData pointData;
                KImageDouble sigmaImg = scaleImage[Idx];

                double bucketsOrientation[36] = {0.,};

                // 커널 사이즈만큼 for문을 돌기
                for(int i = -5; i <= 5; i++){
                    for(int j = -5; j <= 5; j++){

                        double Dxx = sigmaImg[point_y+i][point_x+j+1] - sigmaImg[point_y+i][point_x+j-1];
                        double Dyy = sigmaImg[point_y+i+1][point_x+j] - sigmaImg[point_y+i-1][point_x+j];

                        double theta = ToDegree(atan2(Dyy,Dxx)) + 180.0;        // 0 ~ 360 degree
                        double magnitude = sqrt(pow(Dxx,2.0) + pow(Dyy,2.0));
                        double weightMagnitude = magnitude * Patch[i+5][j+5];
                        int bucketIdx = (int)(theta/10.0);                      // Bucket Index 0 ~ 35

                        bucketsOrientation[bucketIdx] += weightMagnitude;   // 버켓에 담는다.
                    }
                }

                // Bucket 중에 가장 Magnitude가 높은 것을 찾는다.
                double findMax = 0.0;   // Max 값이 곧 최대 Magnitude
                int findIdx = 0;        // Index 값이 곧 orientation
                for(int i = 0; i < 36; i++){
                    if(bucketsOrientation[i] > findMax){
                        findIdx = i;
                        findMax = bucketsOrientation[i];
                    }
                }

                // Point data 초기화
                pointData.x = point_x;
                pointData.y = point_y;
                pointData.dir = findIdx;
                pointData.magn = findMax;

                // Vector에 넣어주기
                resultPointVec.push_back(pointData);
            }
        }
    }

    return resultPointVec;
}

// Input : Keypoint 정보가 담겨 있는 벡터와 원본 Gray이미지
// Output : KImageColor 결과 이미지
// Keypoint 주위에 반지름이 Magnitude고 direction 방향으로 직선을 찍어서 Visualize 해주는 함수
KImageColor taeyoungCV::getVisualizePointOrientation(_KeyPointVec &keypointVec, KImageGray &src)
{
    KImageColor resultImg = src.GrayToRGB();    // 결과 이미지 저장을 위한 변수 생성
    qDebug() << "keypoint size : " << keypointVec.size();

    // for문을 돌면서 keypoint 하나씩 꺼내오기
    for(int keypointIdx = 0; keypointIdx < keypointVec.size(); keypointIdx++){
        KeyPointData tmpKeyPointData = keypointVec[keypointIdx];
        int point_x = tmpKeyPointData.x;
        int point_y = tmpKeyPointData.y;
        double mag = tmpKeyPointData.magn;
        int dir = tmpKeyPointData.dir * 10.0;    // dir 값이 0 ~35 사이로 되어있기 때문에 0 ~ 350으로 맞춰주기 위해서

        // Magnitude 값 조절 - Magnitude 값이 너무 커서 픽셀 값을 넘어가는 부분이 다반사...
        double custom = 4 ,radius;  // custom은 그냥 threshold로 생각하면 된다.

        int tmp = (int)(mag / custom);
        if(tmp < 2 ){
            radius = 5;
        }
        else if(tmp < 5){
            radius = 8;
        }
        else if(tmp < 10){
            radius = 11;
        }
        else{
            radius = 14;
        }

        // 반지름이 Magnitude를 가지는 원 그리기
        for(int angle = 0; angle <= 360; angle++){
            double theta = ToRadian(angle);     // 각도를 라디안으로 바꿈
            double circle_X = (double)point_x - (double)(radius * sin(theta));      // 원의 표면을 찍기 위한 x 좌표
            double circle_Y = (double)point_y - (double)(radius * cos(theta));      // 원의 표면을 찍기 위한 y 좌표

            // 이미지 안에 존재하면 표시
            if((circle_X > 0)&&(circle_Y > 0)&&(circle_X < resultImg.Col())&&(circle_Y < resultImg.Row())){
                // Random 값을 부여하고 pixel 값을 색칠
                resultImg[(int)circle_Y][(int)circle_X].r = (int)mag % 256;
                resultImg[(int)circle_Y][(int)circle_X].g = (int)(mag * 2) % 256;
                resultImg[(int)circle_Y][(int)circle_X].b = (int)(mag * 3) % 256;
            }
        }

        // dir 방향으로 Line 그리기
         for(int range = 0; range <= radius; range++){
            double theta = ToRadian(dir);       // 각도를 라디안으로 바꿈
            double line_X = (double)point_x - (double)(range * sin(theta));      // 직선의 표면을 찍기 위한 x 좌표
            double line_Y = (double)point_y - (double)(range * cos(theta));      // 직선의 표면을 찍기 위한 y 좌표

            // 이미지 안에 존재하면 표시
            if((line_X > 0)&&(line_Y > 0)&&(line_X < resultImg.Col())&&(line_Y < resultImg.Row())){
                // Random 값을 부여하고 pixel 값을 색칠
                resultImg[(int)line_Y][(int)line_X].r = (int)mag % 256;
                resultImg[(int)line_Y][(int)line_X].g = (int)(mag * 2) % 256;
                resultImg[(int)line_Y][(int)line_X].b = (int)(mag * 3) % 256;
            }
        }
    }
    return resultImg;
}

// Input : Keypoint와 sigma값이 담겨 있는 KeypointInfo, Scale별 이미지가 담겨 있는 ScaleSpace
// Output : Descriptor 정보가 담겨 있는 SIFT 구조체 벡터
// Descriptor를 찾는 함수
_SIFTVec taeyoungCV::getSIFTdescriptor(_KeypointInfo &keypointsInfo, _ScaleSpace &scaleImage)
{
    _SIFTVec resultSIFTVec;

    // for문을 돌면서 keypoint를 하나씩 꺼낸다.
    for(int keyPointIdx = 0; keyPointIdx < keypointsInfo.size(); keyPointIdx++){
        // 각각 Sigma scale Image를 가져오기 위해서
        for(int Idx = 1; Idx <= 3; Idx++){

            int point_x = keypointsInfo[keyPointIdx].x;
            int point_y = keypointsInfo[keyPointIdx].y;
            int point_sigma = keypointsInfo[keyPointIdx].sigmaIdx;

            // 가져온 sigma index만족할 때
            if(Idx == point_sigma){

                KImageDouble sigmaImg = scaleImage[Idx];    // Scale에 맞는 이미지
                int descriptor[2][2][8] = {{{0}}};    // SIFT descriptor

                // Point의 주 방향 구하기
                double Dxx_center = sigmaImg[point_y][point_x+1] - sigmaImg[point_y][point_x-1];
                double Dyy_center = sigmaImg[point_y+1][point_x] - sigmaImg[point_y-1][point_x];
                double theta_center = ToDegree(atan2(Dyy_center,Dxx_center)) + 180.0;   // 0 ~ 360 degree
                int centerDir = (int)(theta_center/45.0);         // Center Direction  0 ~ 7

                // 왼쪽 상단에 있는 (4x4) 커널
                for(int i = -4; i <= -1; i++){
                    for(int j = -4; j <= -1; j++){
                        double Dxx = sigmaImg[point_y+i][point_x+j+1] - sigmaImg[point_y+i][point_x+j-1];
                        double Dyy = sigmaImg[point_y+i+1][point_x+j] - sigmaImg[point_y+i-1][point_x+j];
                        double theta = ToDegree(atan2(Dyy,Dxx)) + 180.0;        // 0 ~ 360 degree
                        int descriptorIdx = (int)(theta/45.0);                  // Descriptor Index 0 ~ 7

                        // 주 방향을 빼준다.
                        descriptorIdx -= centerDir;

                        // 혹시 음수가 나올 경우를 대비
                        if(descriptorIdx < 0){
                            descriptorIdx += 8;
                        }

                        // 혹시 범위가 8을 넘어갈 경우를 대비
                        descriptorIdx %= 8;

                        descriptor[0][0][descriptorIdx]++;
                    }
                }

                // 오른쪽 상단에 있는 (4x4) 커널
                for(int i = -4; i <= -1; i++){
                    for(int j = 1; j <= 4; j++){
                        double Dxx = sigmaImg[point_y+i][point_x+j+1] - sigmaImg[point_y+i][point_x+j-1];
                        double Dyy = sigmaImg[point_y+i+1][point_x+j] - sigmaImg[point_y+i-1][point_x+j];
                        double theta = ToDegree(atan2(Dyy,Dxx)) + 180.0;        // 0 ~ 360 degree
                        int descriptorIdx = (int)(theta/45.0);                  // Descriptor Index 0 ~ 7

                        // 주 방향을 빼준다.
                        descriptorIdx -= centerDir;

                        // 혹시 음수가 나올 경우를 대비
                        if(descriptorIdx < 0){
                            descriptorIdx += 8;
                        }

                        // 혹시 범위가 8을 넘어갈 경우를 대비
                        descriptorIdx %= 8;

                        descriptor[0][1][descriptorIdx]++;
                    }
                }

                // 왼쪽 하단에 있는 (4x4) 커널
                for(int i = 1; i <= 4; i++){
                    for(int j = -4; j <= -1; j++){
                        double Dxx = sigmaImg[point_y+i][point_x+j+1] - sigmaImg[point_y+i][point_x+j-1];
                        double Dyy = sigmaImg[point_y+i+1][point_x+j] - sigmaImg[point_y+i-1][point_x+j];
                        double theta = ToDegree(atan2(Dyy,Dxx)) + 180.0;        // 0 ~ 360 degree
                        int descriptorIdx = (int)(theta/45.0);                  // Descriptor Index 0 ~ 7

                        // 주 방향을 빼준다.
                        descriptorIdx -= centerDir;

                        // 혹시 음수가 나올 경우를 대비
                        if(descriptorIdx < 0){
                            descriptorIdx += 8;
                        }

                        // 혹시 범위가 8을 넘어갈 경우를 대비
                        descriptorIdx %= 8;

                        descriptor[1][0][descriptorIdx]++;
                    }
                }

                // 오른쪽 하단에 있는 (4x4) 커널
                for(int i = 1; i <= 4; i++){
                    for(int j = 1; j <= 4; j++){
                        double Dxx = sigmaImg[point_y+i][point_x+j+1] - sigmaImg[point_y+i][point_x+j-1];
                        double Dyy = sigmaImg[point_y+i+1][point_x+j] - sigmaImg[point_y+i-1][point_x+j];
                        double theta = ToDegree(atan2(Dyy,Dxx)) + 180.0;        // 0 ~ 360 degree
                        int descriptorIdx = (int)(theta/45.0);                  // Descriptor Index 0 ~ 7

                        // 주 방향을 빼준다.
                        descriptorIdx -= centerDir;

                        // 혹시 음수가 나올 경우를 대비
                        if(descriptorIdx < 0){
                            descriptorIdx += 8;
                        }

                        // 혹시 범위가 8을 넘어갈 경우를 대비
                        descriptorIdx %= 8;

                        descriptor[1][1][descriptorIdx]++;
                    }
                }

                // 최종적으로 Descriptor를 구했다면 SIFT 구조체에 넣어주고 Vector에 담기
                SIFT sift_Feature;
                sift_Feature.x = point_x;
                sift_Feature.y = point_y;
                memcpy(sift_Feature._descriptor,descriptor,sizeof(descriptor));

                resultSIFTVec.push_back(sift_Feature);
            }

        }
    }

    return resultSIFTVec;
}

// Input : 이미지1, 이미지1의 SIFT descriptor 벡터, 이미지2, 이미지2의 SIFT descriptor 벡터
// Output : Feature matching 된 결과 이미지
// Descriptor를 활용하여 feature matching을 진행하는 함수
KImageColor taeyoungCV::getFeatureMatching(KImageGray &Img1, _SIFTVec &siftVec1, KImageGray &Img2, _SIFTVec &siftVec2)
{
    // Result Image 초기화
    int resultImgCol = _MAX(Img1.Col(),Img2.Col());
    int resultImgRow = Img1.Row() + Img2.Row();

    KImageColor icTmp1 = Img1.GrayToRGB();
    KImageColor icTmp2 = Img2.GrayToRGB();
    KImageColor resultImg;
    resultImg.Create(resultImgRow,resultImgCol);

    for(int i = 0; i < (int)Img1.Row(); i++){
        for(int j = 0; j < (int)Img1.Col(); j++){
            resultImg[i][j] = icTmp1[i][j];
        }

    }
    for(int i = 0; i < (int)Img2.Row(); i++){
        for(int j = 0; j < (int)Img2.Col(); j++){
            resultImg[i+Img1.Row()][j] = icTmp2[i][j];
        }

    }


    // SIFT vector를 모두 for문을 이용하여 비교
    // MSE(Mean Squared Error) function을 이용하여 최소가 되는 매칭점을 찾는다.
    int MatchThreshHold = 100;
    int sY = -1;
    int *match_arr = new int[siftVec1.size()];
    double MS= MatchThreshHold;
    double dError = 0.0;


    for(int sift1Idx = 0; sift1Idx < siftVec1.size(); sift1Idx++){
        for(int sift2Idx = 0; sift2Idx < siftVec2.size(); sift2Idx++){
            // 8 방향에 대한 histogram 값을 모두 파악하기 위해서
            for(int dir = 0; dir < 8; dir++){
                dError += pow(siftVec1[sift1Idx]._descriptor[0][0][dir] - siftVec2[sift2Idx]._descriptor[0][0][dir],2);
                dError += pow(siftVec1[sift1Idx]._descriptor[0][1][dir] - siftVec2[sift2Idx]._descriptor[0][1][dir],2);
                dError += pow(siftVec1[sift1Idx]._descriptor[1][0][dir] - siftVec2[sift2Idx]._descriptor[1][0][dir],2);
                dError += pow(siftVec1[sift1Idx]._descriptor[1][1][dir] - siftVec2[sift2Idx]._descriptor[1][1][dir],2);

            }

            // error가 최소가 되는 Index를 찾기 위한 비교
            if(dError < MS){
                MS = dError;
                sY = sift2Idx;
            }


            dError = 0.0;
        }

        // 만약 모든 점을 비교했는데 Threshold보다 클 경우 Matching 점이 없다고 판단
        if(MS > MatchThreshHold){
            sY = -1;
        }

        // match_arr에 대입
        match_arr[sift1Idx] = sY;
        MS = MatchThreshHold;
    }

    double theta_rad, dX_circle,dY_circle,pX,pY,pX_s,pY_s;
    int iX_circle,iY_circle;
    double radius = 5;

    for(int sift1Idx = 0; sift1Idx < siftVec1.size(); sift1Idx++){
        // 매칭된 점이 있다면
        if(match_arr[sift1Idx] != -1){
            pX = siftVec1[sift1Idx].x;
            pY = siftVec1[sift1Idx].y;

            //draw origin feature
            for(int angle = 0; angle <= 360; angle+= 1){

                    theta_rad = (double)ToRadian(angle);

                    dX_circle = (double)pX - (double)(radius * sin(theta_rad));
                    dY_circle = (double)pY - (double)(radius * cos(theta_rad));

                    iX_circle = (int)dX_circle; iY_circle = (int)dY_circle;

                    if(iX_circle > 0 && iY_circle > 0 && iX_circle < (int)resultImg.Col() && iY_circle < (int)resultImg.Row()){
                       resultImg[iY_circle][iX_circle].r = (sift1Idx * 35 + 51) % 256;
                       resultImg[iY_circle][iX_circle].g = (sift1Idx * 10 + 51) % 256;
                       resultImg[iY_circle][iX_circle].b = (sift1Idx * 49 + 51) % 256;
                }
            }

            pX_s = siftVec2[match_arr[sift1Idx]].x;
            pY_s = siftVec2[match_arr[sift1Idx]].y +Img1.Row();

            //draw sample feature
            for(int angle = 0; angle <= 360; angle+= 1){

                    theta_rad = (double)ToRadian(angle);

                    dX_circle = (double)pX_s - (double)(radius * sin(theta_rad));
                    dY_circle = (double)pY_s - (double)(radius * cos(theta_rad));

                    iX_circle = (int)dX_circle; iY_circle = (int)dY_circle;

                    if(iX_circle > 0 && iY_circle > 0 && iX_circle < (int)resultImg.Col() && iY_circle < (int)resultImg.Row()){
                       resultImg[iY_circle][iX_circle].r = (sift1Idx * 35 + 51) % 256;
                       resultImg[iY_circle][iX_circle].g = (sift1Idx * 10 + 51) % 256;
                       resultImg[iY_circle][iX_circle].b = (sift1Idx * 49 + 51) % 256;
                }
            }

            double gx, gy, dist, ang_rad;
            gx = pX - pX_s;
            gy = pY - pY_s;
            dist = sqrt(pow(gx,2) + pow(gy,2));

            ang_rad = atan2(gx,gy);

            //Draw Direction
            double dX_dir,dY_dir;
            int iX_dir, iY_dir;
            for(int range = 0; range <= dist; range++){
                dX_dir = (double)pX - (double)(range * sin(ang_rad));
                dY_dir = (double)pY - (double)(range * cos(ang_rad));

                iX_dir = (int)dX_dir; iY_dir = (int)dY_dir;

                if(iX_dir > 0 && iY_dir > 0 && iX_dir < (int)resultImg.Col() && iY_dir < (int)resultImg.Row()){
                   resultImg[iY_dir][iX_dir].r = (sift1Idx * 35 + 51) % 256;
                   resultImg[iY_dir][iX_dir].g = (sift1Idx * 10 + 51) % 256;
                   resultImg[iY_dir][iX_dir].b = (sift1Idx * 49 + 51) % 256;
                }

            }
        }
    }

    delete[] match_arr;

    return resultImg;
}

// Input : Optical flow를 진행할 이미지 2개, iteration할 횟수
// Output : Edge 정보를 담고 있는 이미지
// Optical flow 수행
_EdgeImg taeyoungCV::OpticalFlow(KImageGray &igImg1, KImageGray &igImg2, int iter)
{
    int kernelSize = 5;
    int kernalH = kernelSize/2;

    int minSize = _MIN(igImg2.Row(), igImg2.Col());

    KImageColor resultImg;


    // 반복횟수로 인한 이미지 축소가 minsize 보다 크면 iter를 다시 정의한다.
    if(pow(2, iter-1) > minSize / kernelSize){
        iter = 0;
        int tmpValue = 1;

        while(1){

            iter++;
            tmpValue *= 2;

            if(tmpValue > minSize / kernelSize){
                iter--;
                break;
            }
        }
    }

    // iter + 1개의 이미지 피라미드 생성(원본의 이미지도 저장되기 때문에)
    ImgPyramid _imgPyramidSrc1(igImg1);
    _imgPyramidSrc1.Create(iter);
    ImgPyramid _imgPyramidSrc2(igImg2);
    _imgPyramidSrc2.Create(iter);

    ////lucas & kanade method 사용
    vector<_EdgeImg>* pyImgSrc1 = _imgPyramidSrc1.getPyImg();
    vector<_EdgeImg>* pyImgSrc2 = _imgPyramidSrc2.getPyImg();


    // 상위의 피라미드 이미지(작은 이미지)부터 차근 차근 구하기
    _JMAT srcMat1 = GetValMatrix((*pyImgSrc1)[iter]);
    _JMAT srcMat2 = GetValMatrix((*pyImgSrc2)[iter]);

    // lucas & kanade를 적용하기 위한 가중치 벡터 생성
    Eigen::Matrix<double, 25, 25> weightedMat5;   weightedMat5.fill(0.);

    for(int nRow = 0; nRow<kernelSize; nRow++){
        for(int nCol = 0; nCol<kernelSize; nCol++){
            weightedMat5(nRow*kernelSize + nCol,nRow*kernelSize + nCol) = gaussianVoting5[nRow][nCol];
        }
    }

    Eigen::Matrix<double, 25, 2> dxdy;
    Eigen::Matrix<double, 25, 1> dt;
    Eigen::Matrix<double, 2, 25> aTw;
    Eigen::Matrix<double, 2, 1> zeta;

    //dx, dy 찾기 - 맨 상단의 이미지에서 dx, dy 추출
    for(int nRow=kernalH+1; nRow < srcMat1.size()-kernalH-1; nRow++){
        for(int nCol=kernalH+1; nCol < srcMat1[0].size()-kernalH-1; nCol++){

                for(int kRow = nRow-kernalH, _i=0; kRow <= nRow+kernalH; kRow++, _i++){
                    for(int kCol = nCol-kernalH, _j=0; kCol <= nCol+kernalH; kCol++, _j++){

                        // 앞선 이미지의 크기는 1/2, 거리는 2배
                        double moveX = kCol + (*pyImgSrc2)[iter][nRow]->at(nCol).dx;
                        double moveY = kRow + (*pyImgSrc2)[iter][nRow]->at(nCol).dy;

                        if(moveX <0) moveX = 0; if(moveX > srcMat1[0].size()-1) moveX = srcMat1[0].size()-1;
                        if(moveY <0) moveY = 0; if(moveY > srcMat1.size()-1) moveY = srcMat1.size()-1;

                        dxdy.row(_i*kernelSize + _j) << srcMat1[kRow][kCol+1] - srcMat1[kRow][kCol-1], srcMat1[kRow+1][kCol] - srcMat1[kRow-1][kCol];
                        dt.row(_i*kernelSize + _j) << srcMat1[moveY][moveX] - srcMat2[kRow][kCol];

                    }
                }

                //역행렬을 통해 d값을 구하는 과정
                aTw = dxdy.transpose() * weightedMat5;
                zeta = (aTw * dxdy).inverse() * aTw * dt;

                (*pyImgSrc2)[iter][nRow]->at(nCol).dx += zeta(0,0);
                (*pyImgSrc2)[iter][nRow]->at(nCol).dy += zeta(1,0);
        }
    }

    for(int i = iter-1; i >= 0; i--){
        srcMat1 = GetValMatrix((*pyImgSrc1)[i]);
        srcMat2 = GetValMatrix((*pyImgSrc2)[i]);
        _EdgeImg refMat = (*pyImgSrc2)[i+1];    //상단 이미지(래퍼런스)의 dx,dy를 가져오기 위해

        // 커널을 옮겨가면서 dx, dy 찾기 - 맨 상단의 이미지에서 dx, dy 추출
        for(int nRow=kernalH+1; nRow < srcMat1.size()-kernalH-1; nRow++){
            for(int nCol=kernalH+1; nCol < srcMat1[0].size()-kernalH-1; nCol++){

                    // 커널안의 점들을 통해 lucas & kanade를 위한 행렬을 만듬
                    for(int kRow = nRow-kernalH, _i=0; kRow <= nRow+kernalH; kRow++, _i++){
                        for(int kCol = nCol-kernalH, _j=0; kCol <= nCol+kernalH; kCol++, _j++){
//                        qDebug() << i << ": "<< nRow <<", "<< nCol <<", "<< kRow <<", "<< nRow <<", "<< kCol <<", ";

                        // 앞선 이미지의 크기는 1/2, 거리는 2배
                        double moveX = kCol + refMat[nRow/2]->at(nCol/2).dx * 2 + (*pyImgSrc2)[i][nRow]->at(nCol).dx; //이문게 제
                        double moveY = kRow + refMat[nRow/2]->at(nCol/2).dy * 2 + (*pyImgSrc2)[i][nRow]->at(nCol).dy;
                        if(moveX <0) moveX = 0; if(moveX > srcMat1[0].size()-1) moveX = srcMat1[0].size()-1;
                        if(moveY <0) moveY = 0; if(moveY > srcMat1.size()-1) moveY = srcMat1.size()-1;


                        dxdy.row(_i*kernelSize + _j) << srcMat1[kRow][kCol+1] - srcMat1[kRow][kCol-1],
                                                      srcMat1[kRow+1][kCol] - srcMat1[kRow-1][kCol];

                        dt.row(_i*kernelSize + _j) << srcMat1[moveY][moveX] - srcMat2[kRow][kCol];

                        }
                    }

                    //역행렬을 통해 d값을 구하는 과정
                    aTw = dxdy.transpose() * weightedMat5;
                    zeta = (aTw * dxdy).inverse() * aTw * dt;

                    (*pyImgSrc2)[i][nRow]->at(nCol).dx += zeta(0,0);
                    (*pyImgSrc2)[i][nRow]->at(nCol).dy += zeta(1,0);

            }
        }
    }

    // 그냥 2번째 이미지를 컬러 이미지로 변환해서 저장함
    resultIcImg = igImg2.GrayToRGB();

    return (*pyImgSrc2)[0];
}

// Input : Edge정보가 들어있는 Matrix
// Output : 2차원 Double형 벡터
// Matrix의 Value를 계산
vector<vector<double> > taeyoungCV::GetValMatrix(const _EdgeImg &matrix)
{
    _JMAT resultMat; _JCOL tmp;
    tmp.assign(matrix[0]->size(), 0.);
    resultMat.assign(matrix.size(), tmp);

    for(int i=0; i<resultMat.size(); i++){
        resultMat[i].reserve(matrix[0]->size());
    }

    for(int nRow=0; nRow<resultMat.size(); nRow++){
        for(int nCol=0; nCol<resultMat[0].size(); nCol++){
            resultMat[nRow][nCol] = matrix[nRow]->at(nCol).val;
        }
    }

    return resultMat;
}


// Input : 만들 이미지 피라미드 갯수
// 이미지 피라미드 만들기
void ImgPyramid::Create(int num)
{
    int minSize = _MIN(_rowSize, _colSize);

    // 예외처리
    if(pow(2, num-1) > minSize)   return;

    // 이전의 데이터가 있었다면 삭제해준다. - 메모리 누수 방지
    if(!pyImg.empty()){
        for(int i=0; i< pyImg.size(); i++){
            for(int j=0; i< pyImg[i].size(); j++){
                delete pyImg[i][j];
            }
        }
        pyImg.clear();
    }

    // 이미지 하나 하나를 잠시 저장
    _EdgeImg tmpImg;

    // 미분데이터를 담을 이미지 container 생성
    vector<EdgeData> *colEdge;  // edge 데이터의 열 성분들

    for(int i=0; i < _igImg.Row(); i++){
        colEdge = new vector<EdgeData>(_igImg.Col());
        tmpImg.push_back(colEdge);
    }

    for(int nRow=0; nRow<_igImg.Row(); nRow++){
        for(int nCol=0; nCol<_igImg.Col(); nCol++){
            tmpImg[nRow]->at(nCol).val = _igImg[nRow][nCol];
        }
    }

    pyImg.push_back(tmpImg);

    //피라미드 이미지를 생성
    for(int i = 1; i <= num; i++){

        tmpImg.clear();

        for(int j=0; j < pyImg[i-1].size() / 2; j++){
            colEdge = new vector<EdgeData>(pyImg[i-1][0]->size() / 2);
            tmpImg.push_back(colEdge);
        }

        for(int nRow=0; nRow<pyImg[i-1].size() / 2; nRow++){
            for(int nCol=0; nCol<pyImg[i-1][0]->size() / 2; nCol++){
                // 제대로 하려면, 중간값을 넣든가 하는것이 좋을 듯...
                tmpImg[nRow]->at(nCol).val = pyImg[i-1][nRow*2]->at(nCol*2).val;
            }
        }

        pyImg.push_back(tmpImg);
    }
}
