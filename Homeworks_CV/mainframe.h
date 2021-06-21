#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include "kfc.h"
#include <QDebug> // debug를 위한 헤더 파일
#include "taeyoungcv.h"
#include "imageform.h"

namespace Ui {
class MainFrame;

}

class ImageForm;
class KVoronoiDgm;
class KPotentialField;

class MainFrame : public QDialog
{
    Q_OBJECT

private:
    Ui::MainFrame *ui;

    KPtrList<ImageForm*>*   _plpImageForm;
    ImageForm*              _q_pFormFocused;
    int                     kernal_size = 3;
    QString                 templeteFile;

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void            ImageFormFocused(ImageForm* q_pImageForm)
                    {   _q_pFormFocused  = q_pImageForm;   //활성화된 창의 포인터를 저장함
                        UpdateUI();                        //UI 활성화 갱신
                    }
    void            UpdateUI();
    void            CloseImageForm(ImageForm* pForm);

public:
    void            OnMousePos(const int& nX, const int& nY, ImageForm* q_pForm);

private slots:
    void on_buttonOpen_clicked();
    void on_buttonDeleteContents_clicked();

    // cv1
    void on_buttonSepiaTone_clicked();
    void on_buttonShowList_clicked();
    void on_spinSaturation_textChanged(const QString &arg1);
    void on_spinHue_textChanged(const QString &arg1);

    // cv2
    void on_setOtsuAlgorithm_clicked();
    void on_setLabelingAlgorithm_clicked();
    void on_comboBox_activated(int index);
    void on_Dilation_clicked();
    void on_Erosion_clicked();

    // cv3
    void on_histogramEqualization_clicked();
    void on_selectSrcImage_clicked();
    void on_selectTargetImage_clicked();
    void on_histogramMatching_clicked();

    // cv4
    void on_gaussian_clicked();
    void on_pepper_salt_clicked();
    void on_gaussianFilter_clicked();
    void on_comboBox_2_activated(int index);
    void on_medianFilter_clicked();
    void on_boxFilter_clicked();
    void on_boxFilteringBox_activated(int index);

    // cv5
    void on_cannyEdgeOperator_clicked();

    // cv6
    void on_houghCircleTransform_clicked();
    void on_selectTemplete_clicked();
    void on_generalizedHoughTransform_clicked();

    // cv7
    void on_getGaussianScaleImage_clicked();
    void on_getDOGScaleImage_clicked();
    void on_getKeyPointDetection_clicked();
    void on_getKeyPointDescriptor_clicked();
    void on_getSIFTfeatureMatching_clicked();
    void on_getFirstImage_clicked();
    void on_getSecondImage_clicked();

    // cv8
    void on_getImage_clicked();
    void on_getImage_2_clicked();
    void on_getOpticalFlow_clicked();

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINFRAME_H
