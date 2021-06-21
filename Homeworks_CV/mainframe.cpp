#include <QFileDialog>
#include <QPainter>
#include <iostream>

#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"

MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _plpImageForm       = new KPtrList<ImageForm*>(10,false,false);
    _q_pFormFocused     = 0;

    //객체 맴버의 초기화

    //get a current directory
    char st[100];
    GetCurrentDirectoryA(100,st);

    //리스트 출력창을 안보이게
    ui->listWidget->setVisible(false);
    this->adjustSize();

    //UI 활성화 갱신
    UpdateUI();
}

MainFrame::~MainFrame()
{ 
    delete ui;         
    delete _plpImageForm;


}

void MainFrame::CloseImageForm(ImageForm *pForm)
{
    //ImageForm 포인터 삭제
    _plpImageForm->Remove(pForm);

    //활성화 ImageForm 초기화
    _q_pFormFocused     = 0;

    //관련 객체 삭제

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::UpdateUI()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        ui->buttonSepiaTone->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );    

    }
    else if(ui->tabWidget->currentIndex() == 1)
    {

    }
    else if(ui->tabWidget->currentIndex() == 2)
    {

    }    
}

void MainFrame::OnMousePos(const int &nX, const int &nY, ImageForm* q_pForm)
{

    UpdateUI();
}

void MainFrame::closeEvent(QCloseEvent* event)
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}


void MainFrame::on_buttonOpen_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성    
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "OPEN", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonDeleteContents_clicked()
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}

void MainFrame::on_buttonSepiaTone_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    //hue, saturation 값 가져오기
    double dHue = ui->spinHue->value();
    double dSat = ui->spinSaturation->value(); // 위와 같은 식으로

    // 결과 이미지 생성
    KImageColor sepia;
    KImageGray val,sat,hue;

    taeyoungCV ty;
    sepia = ty.get_sepiatone_image(icMain,dHue,dSat);
    sat = ty.get_saturation_image(icMain);
    val = ty.get_value_image(icMain);
    hue = ty.get_hue_image(icMain);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(sepia, "Sepia Tone", this);
    ImageForm*  q_pForm2 = new ImageForm(val, "Value image", this);
    ImageForm*  q_pForm3 = new ImageForm(sat, "Saturation image", this);
    ImageForm*  q_pForm4 = new ImageForm(hue, "Hue image", this);

    _plpImageForm->Add(q_pForm);
    _plpImageForm->Add(q_pForm2);
    _plpImageForm->Add(q_pForm3);
    _plpImageForm->Add(q_pForm4);

    q_pForm->show();
    q_pForm2->show();
    q_pForm3->show();
    q_pForm4->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_buttonShowList_clicked()
{
    static int nWidthOld = ui->tabWidget->width();

    if(ui->listWidget->isVisible())
    {
        nWidthOld = ui->listWidget->width();
        ui->listWidget->hide();
        this->adjustSize();
    }
    else
    {        
        ui->listWidget->show();
        QRect q_rcWin = this->geometry();

        this->setGeometry(q_rcWin.left(), q_rcWin.top(), q_rcWin.width()+nWidthOld, q_rcWin.height());
    }
}

void MainFrame::on_spinSaturation_textChanged(const QString &arg1)
{

    ImageForm * q_firstForm = (*_plpImageForm)[0];
    KImageColor icMain = q_firstForm->ImageColor();

    KImageColor sepia_update;

    //hue, saturation 값 가져오기
    double dHue = ui->spinHue->value();
    double dSat = ui->spinSaturation->value(); // 위와 같은 식으로

    taeyoungCV ty;
    sepia_update = ty.get_sepiatone_image(icMain,dHue,dSat);

    ImageForm * q_pForm = 0;
    for(int i = 0; i<_plpImageForm->Count();i++){
       if((*_plpImageForm)[i]->ID() == "Sepia Tone" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
           q_pForm = (*_plpImageForm)[i];
           break;
       }
    }


    if(q_pForm){
        q_pForm->Update(sepia_update);
    }
    else {
        q_pForm = new ImageForm(sepia_update, "Sepia Tone",this);
        q_pForm->show();
        _plpImageForm->Add(q_pForm);
    }

}

void MainFrame::on_spinHue_textChanged(const QString &arg1)
{
    ImageForm * q_firstForm = (*_plpImageForm)[0];
    KImageColor icMain = q_firstForm->ImageColor();

    KImageColor sepia_update;

    //hue, saturation 값 가져오기
    double dHue = ui->spinHue->value();
    double dSat = ui->spinSaturation->value(); // 위와 같은 식으로

    taeyoungCV ty;
    sepia_update = ty.get_sepiatone_image(icMain,dHue,dSat);

    ImageForm * q_pForm = 0;
    for(int i = 0; i<_plpImageForm->Count();i++){
       if((*_plpImageForm)[i]->ID() == "Sepia Tone" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
           q_pForm = (*_plpImageForm)[i];
           break;
       }
    }


    if(q_pForm){
        q_pForm->Update(sepia_update);
    }
    else {
        q_pForm = new ImageForm(sepia_update, "Sepia Tone",this);
        q_pForm->show();
        _plpImageForm->Add(q_pForm);
    }
}

void MainFrame::on_setOtsuAlgorithm_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    KImageGray binray_image;

    taeyoungCV::get_Binarization_image(igMain,binray_image);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(binray_image, "Binarization Image", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_setLabelingAlgorithm_clicked()
{

    ImageForm * q_pForm = 0;
    for(int i = 0; i<_plpImageForm->Count();i++){
       if((*_plpImageForm)[i]->ID() == "Binarization Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
           q_pForm = (*_plpImageForm)[i];
           break;
       }
    }

    KImageGray src = q_pForm->ImageGray();
    KImageColor labelingImage;

    taeyoungCV::get_Labeling_image(src,labelingImage);  // labeling algorithm

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm_result = new ImageForm(labelingImage, "Labeling Image", this);
    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_comboBox_activated(int index)
{
    if(index == 0){
        kernal_size = 3;
    }
    else {
        kernal_size = 5;
    }
}

void MainFrame::on_Dilation_clicked()
{
    // 띄워져 있는 이미지를 찾아서 초기화
    ImageForm * q_pForm = 0;
    for(int i = 0; i<_plpImageForm->Count();i++){
       if((*_plpImageForm)[i]->ID() == "Binarization Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
           q_pForm = (*_plpImageForm)[i];
           break;
       }
    }

    KImageGray src = q_pForm->ImageGray();
    KImageGray dilation;
    if((kernal_size == 3) || (kernal_size == 5))
        taeyoungCV::get_dilation_image(src,dilation,kernal_size);   //dilation algorithm
    else
        qDebug() << "Select Kernal Size!";



    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm_result = new ImageForm(dilation, "Dilation Image", this);
    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_Erosion_clicked()
{
    // 띄워져 있는 이미지를 찾아서 초기화
    ImageForm * q_pForm = 0;
    for(int i = 0; i<_plpImageForm->Count();i++){
       if((*_plpImageForm)[i]->ID() == "Binarization Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
           q_pForm = (*_plpImageForm)[i];
           break;
       }
    }

    KImageGray src = q_pForm->ImageGray();
    KImageGray erosion;
    if((kernal_size == 3) || (kernal_size == 5))
        taeyoungCV::get_erosion_image(src,erosion,kernal_size); // erosion algortihm
    else
        qDebug() << "Select Kernal Size!";



    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm_result = new ImageForm(erosion, "Erosion Image", this);
    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_histogramEqualization_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor heqResult;
    taeyoungCV::histogram_equalization(icMain,heqResult);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(heqResult, "Histogram Equalization", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();

}

void MainFrame::on_selectSrcImage_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "Source Image", this);

    KImageColor src = q_pForm->ImageColor();


    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(src, "Source Image", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_selectTargetImage_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "Source Image", this);


    KImageColor target = q_pForm->ImageColor();

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(target, "Target Image", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_histogramMatching_clicked()
{
    // Source Image로 KImageColor 초기화
    ImageForm * q_pForm_s = 0;

    if(_plpImageForm->Count() != 0) // 0인지 아닌지 먼저 확인
        for(int i = 0; i<_plpImageForm->Count();i++){
           if((*_plpImageForm)[i]->ID() == "Source Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
               q_pForm_s = (*_plpImageForm)[i];
               break;
           }
        }
    else
        return;

    KImageColor src = q_pForm_s->ImageColor();

    // Target Image로 KImageColor 초기화
    ImageForm * q_pForm_t = 0;

    if(_plpImageForm->Count() != 0)
        for(int i = 0; i<_plpImageForm->Count();i++){
           if((*_plpImageForm)[i]->ID() == "Target Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
               q_pForm_t = (*_plpImageForm)[i];
               break;
           }
        }
    else
        return;

    KImageColor target = q_pForm_t->ImageColor();


    // Histogram matching 적용
    taeyoungCV::histogram_matching(src,target);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(src, "Histogram Matching", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_gaussian_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor gaussianDst;

    // UI에서 sigma값을 받아온다.
    double sigma = ui->spinSigma->value();

    // 가우시안 노이즈 적용
    taeyoungCV::getGaussianNoise(icMain,gaussianDst,sigma);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(gaussianDst, "Gaussian Noise", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_pepper_salt_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor impulseDst;

    // UI에서 noise의 probability를 받아온다.
    double probability = ui->spinProbability->value();

    // Salt and pepper 노이즈 적용
    taeyoungCV::getImpulseNoise(icMain,impulseDst,probability);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(impulseDst, "Salt and Pepper Noise", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_gaussianFilter_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address())
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor gaussianFilterDst;

    // UI에서 sigma값을 받아온다.
    double dSigma = ui->spinSigmaFilter->value();

    // Gaussian Filtering 적용
    taeyoungCV::gaussianFilter(icMain,gaussianFilterDst,dSigma);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(gaussianFilterDst, "Gaussian Filtering", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_comboBox_2_activated(int index)
{
    if(index == 0){
        kernal_size = 3;
    }
    else {
        kernal_size = 5;
    }
}

void MainFrame::on_medianFilter_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address())
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor medianDst;

    // median filter 적용
    taeyoungCV::medianFilter(icMain,medianDst,kernal_size);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(medianDst, "Median Filtering", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_boxFilter_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address())
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    KImageColor boxDst;

    // box filter 적용
    taeyoungCV::boxFilter(icMain,boxDst,kernal_size);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(boxDst, "Box Filtering", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_boxFilteringBox_activated(int index)
{
    if(index == 0){
        kernal_size = 3;
    }
    else {
        kernal_size = 5;
    }
}

void MainFrame::on_cannyEdgeOperator_clicked()
{

    // UI에서 sigma값을 받아온다.
    double dSigma = ui->spinSigmaFilter2->value();

    // UI에서 threshold 값을 받아온다.
    int ith1 = ui->spinThreshold1->value();
    int ith2 = ui->spinThreshold2->value();

    // 만약 th1 이 th2보다 크다면
    if(ith1 > ith2){
        return;
    }

    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;


    KImageGray FDGImage;
    KImageGray cannyImage;
    taeyoungCV cv;

    // FDG 적용
    cv.FDG(icMain,FDGImage,dSigma);
    cv.cannyEdge(FDGImage,cannyImage,ith1,ith2,dSigma);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(cannyImage, "Canny Edge Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();

}



void MainFrame::on_houghCircleTransform_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;

    int radius = ui->spinRadius->value();
    int threshold = ui->spinThreshold->value();

    KImageColor dst;

    taeyoungCV cv;  // Hough Transform 적용
    cv.circleHoughTransform(icMain,dst,radius,threshold);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(dst, "Hough Circle Transform Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_selectTemplete_clicked()
{
    //txt 파일 선택
   QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
   QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a txt File"),  "./data", "txt Files(*.txt)",0, q_Options);

   templeteFile = q_stFile;
}


void MainFrame::on_generalizedHoughTransform_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;

    int threshold = ui->spinGeneralThreshold->value();

    KImageColor result;

    taeyoungCV cv;  // Generanlized Hough Transform 적용
    cv.generalizedHoughTransform(icMain,result,templeteFile.toUtf8().constData(),threshold);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(result, "Generalized Hough Transform Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();


}


void MainFrame::on_getGaussianScaleImage_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;

    double sigma = ui->spinSigmaFilter_3->value();

    //scaleSpaceVector.clear();   // 만약 값이 저장되어 있을 경우, 초기화

    taeyoungCV cv;
    KImageGray half = icMain.HalfSize();    // Visualize를 위해 일부러 이미지의 크기를 반으로 줄였다.
    _OctaveSpace scaleSpaceVector = cv.getOctaveSpace(half,sigma);   // OctaveSpace를 얻어내는 함수

    KImageGray tmp = cv.getMergeOctaveSpace(scaleSpaceVector);  // 모든 Image를 Merge하는 함수

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(tmp, "Guassian Sacle Image Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_getDOGScaleImage_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;

    double sigma = ui->spinSigmaFilter_3->value();

    //scaleSpaceVector.clear();   // 만약 값이 저장되어 있을 경우, 초기화

    taeyoungCV cv;
    KImageGray half = icMain.HalfSize();    // Visualize를 위해 일부러 이미지의 크기를 반으로 줄였다.
    _OctaveSpace scaleSpaceVector = cv.getDOG_OctaveSpace(half,sigma);   // OctaveSpace를 얻어내는 함수

    KImageGray tmp = cv.getMergeOctaveSpace(scaleSpaceVector);  // 모든 Image를 Merge하는 함수

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(tmp, "DOG Sacle Image Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_getKeyPointDetection_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;

    double sigma = ui->spinSigmaFilter_3->value();

    taeyoungCV cv;
    KImageColor result;

    _OctaveSpace scaleSpaceVector = cv.getDOG_OctaveSpace(icMain,sigma);   // OctaveSpace를 얻어내는 함수
    result = cv.getVisualizeKeyPointDetection(icMain,scaleSpaceVector,sigma);       // Keypoint를 찾아내는 함수

    ImageForm*  q_pForm = new ImageForm(result, "Key point detection Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();

}

void MainFrame::on_getKeyPointDescriptor_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        icMain = _q_pFormFocused->ImageGray();
    else
        return;

    double sigma = ui->spinSigmaFilter_3->value();

    taeyoungCV cv;
    _ScaleSpace scaleSpace = cv.getGaussianScaleImage(icMain,sigma);       // ScaleSpace 이미지를 얻는 함수
    _OctaveSpace scaleSpaceVector = cv.getDOG_OctaveSpace(icMain,sigma);   // OctaveSpace를 얻어내는 함수
    _KeypointInfo keypointInfo = cv.getKeyPointDetection(scaleSpaceVector); // Keypoint detection을 하는 함수
    _KeyPointVec resultVec = cv.getKeyPointOrientation(keypointInfo,scaleSpace);  // Keypoint orientation을 하는 함수
    KImageColor resultImg = cv.getVisualizePointOrientation(resultVec,icMain);  // Visualize를 위한 함수
    _SIFTVec  descriptorVec = cv.getSIFTdescriptor(keypointInfo,scaleSpace);    // Descriptor를 찾기 위한 함수

    ImageForm*  q_pForm = new ImageForm(resultImg, "SIFT Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_getSIFTfeatureMatching_clicked()
{
    // Source Image로 KImageColor 초기화
    ImageForm * q_pForm_s = 0;

    if(_plpImageForm->Count() != 0) // 0인지 아닌지 먼저 확인
        for(int i = 0; i<_plpImageForm->Count();i++){
           if((*_plpImageForm)[i]->ID() == "1st Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
               q_pForm_s = (*_plpImageForm)[i];
               break;
           }
        }
    else
        return;

    KImageGray Image1 = q_pForm_s->ImageGray();

    // Target Image로 KImageColor 초기화
    ImageForm * q_pForm_t = 0;

    if(_plpImageForm->Count() != 0)
        for(int i = 0; i<_plpImageForm->Count();i++){
           if((*_plpImageForm)[i]->ID() == "2nd Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
               q_pForm_t = (*_plpImageForm)[i];
               break;
           }
        }
    else
        return;

    KImageGray Image2 = q_pForm_t->ImageGray();

    double sigma = ui->spinSigmaFilter_3->value();


    taeyoungCV cv;
    // 첫번째 이미지 SIFT
    _ScaleSpace scaleSpace1 = cv.getGaussianScaleImage(Image1,sigma);       // ScaleSpace 이미지를 얻는 함수
    _OctaveSpace scaleSpaceVector1 = cv.getDOG_OctaveSpace(Image1,sigma);   // OctaveSpace를 얻어내는 함수
    _KeypointInfo keypointInfo1 = cv.getKeyPointDetection(scaleSpaceVector1); // Keypoint detection을 하는 함수
    _KeyPointVec resultVec1 = cv.getKeyPointOrientation(keypointInfo1,scaleSpace1);  // Keypoint orientation을 하는 함수
    _SIFTVec  descriptorVec1 = cv.getSIFTdescriptor(keypointInfo1,scaleSpace1);    // Descriptor를 찾기 위한 함수

    // 두번째 이미지 SIFT
    _ScaleSpace scaleSpace2 = cv.getGaussianScaleImage(Image2,sigma);       // ScaleSpace 이미지를 얻는 함수
    _OctaveSpace scaleSpaceVector2 = cv.getDOG_OctaveSpace(Image2,sigma);   // OctaveSpace를 얻어내는 함수
    _KeypointInfo keypointInfo2 = cv.getKeyPointDetection(scaleSpaceVector2); // Keypoint detection을 하는 함수
    _KeyPointVec resultVec2 = cv.getKeyPointOrientation(keypointInfo2,scaleSpace2);  // Keypoint orientation을 하는 함수
    _SIFTVec  descriptorVec2 = cv.getSIFTdescriptor(keypointInfo2,scaleSpace2);    // Descriptor를 찾기 위한 함수

    KImageColor resultImg = cv.getFeatureMatching(Image1,descriptorVec1,Image2,descriptorVec2);

    ImageForm*  q_pForm = new ImageForm(resultImg, "SIFT feature matching Result", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();


}

void MainFrame::on_getFirstImage_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "1st Image", this);

    KImageGray src = q_pForm->ImageGray();

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(src, "1st Image", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_getSecondImage_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "2nd Image", this);


    KImageGray target = q_pForm->ImageGray();

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(target, "2nd Image", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_getImage_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "1st source Image", this);

    KImageGray src = q_pForm->ImageGray();

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(src, "1st source Image", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_getImage_2_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "2nd source Image", this);


    KImageGray target = q_pForm->ImageGray();

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm1 = new ImageForm(target, "2nd source Image", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_getOpticalFlow_clicked()
{// Source Image로 KImageColor 초기화
    ImageForm * q_pForm_s = 0;

    if(_plpImageForm->Count() != 0) // 0인지 아닌지 먼저 확인
        for(int i = 0; i<_plpImageForm->Count();i++){
           if((*_plpImageForm)[i]->ID() == "1st source Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
               q_pForm_s = (*_plpImageForm)[i];
               break;
           }
        }
    else
        return;

    KImageGray Image1 = q_pForm_s->ImageGray();

    // Target Image로 KImageColor 초기화
    ImageForm * q_pForm_t = 0;

    if(_plpImageForm->Count() != 0)
        for(int i = 0; i<_plpImageForm->Count();i++){
           if((*_plpImageForm)[i]->ID() == "2nd source Image" && ((*_plpImageForm)[i]->size() == _q_pFormFocused->size())){
               q_pForm_t = (*_plpImageForm)[i];
               break;
           }
        }
    else
        return;

    KImageGray Image2 = q_pForm_t->ImageGray();

    KImageColor icMain;
    _EdgeImg    edgeImg;

    vector<vector<double>> a;
    vector<double> tmp;
    tmp.assign(2, 0.);
    a.assign(2, tmp);

    vector<vector<double>> b;
    b.assign(2, tmp);

    for(int nRow=0; nRow < 2; nRow++){
        for(int nCol=0; nCol < 2; nCol++){
           a[nRow][nCol] = nCol + nRow*2;
           b[nRow][nCol] = nCol + nRow*2;
        }
    }

    taeyoungCV cv;
    edgeImg = cv.OpticalFlow(Image1, Image2);
    icMain = cv.GetResultIcImg();

    ImageForm*  q_pFormRes = new ImageForm(icMain, "Optical Flow Image", this);

    int nScale = 8;

    for(int nRow = 0; nRow < icMain.Row()/nScale; nRow++){
        for(int nCol=0; nCol < icMain.Col()/nScale; nCol++){
            int nDx = edgeImg[nRow*nScale]->at(nCol*nScale).dx;
            int nDy = edgeImg[nRow*nScale]->at(nCol*nScale).dy;

            q_pFormRes->DrawLine(nCol*nScale, nRow*nScale, nCol*nScale+nDx, nRow*nScale+nDy,
                                 QColor(255, 255, 0), 1);
        }
    }

    _plpImageForm->Add(q_pFormRes);
    q_pFormRes->show();


    //UI 활성화 갱신
    UpdateUI();

    qDebug() << b.size();
}
