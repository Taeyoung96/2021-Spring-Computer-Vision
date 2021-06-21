/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFrame
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *buttonOpen;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *buttonDeleteContents;
    QSpacerItem *horizontalSpacer;
    QToolButton *buttonShowList;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QLabel *label_5;
    QSpinBox *spinHue;
    QLabel *label_6;
    QDoubleSpinBox *spinSaturation;
    QPushButton *buttonSepiaTone;
    QWidget *tab_3;
    QPushButton *setOtsuAlgorithm;
    QLabel *label;
    QLabel *label_2;
    QPushButton *setLabelingAlgorithm;
    QComboBox *comboBox;
    QLabel *label_3;
    QPushButton *Dilation;
    QPushButton *Erosion;
    QWidget *tab_4;
    QLabel *label_4;
    QPushButton *histogramEqualization;
    QLabel *label_7;
    QPushButton *selectSrcImage;
    QPushButton *selectTargetImage;
    QPushButton *histogramMatching;
    QWidget *tab;
    QLabel *label_8;
    QPushButton *gaussian;
    QPushButton *pepper_salt;
    QLabel *label_9;
    QLabel *label_10;
    QDoubleSpinBox *spinSigma;
    QLabel *label_12;
    QDoubleSpinBox *spinProbability;
    QLabel *label_13;
    QLabel *label_11;
    QPushButton *gaussianFilter;
    QDoubleSpinBox *spinSigmaFilter;
    QPushButton *medianFilter;
    QComboBox *comboBox_2;
    QPushButton *boxFilter;
    QComboBox *boxFilteringBox;
    QWidget *tab_5;
    QPushButton *cannyEdgeOperator;
    QLabel *label_14;
    QLabel *label_15;
    QDoubleSpinBox *spinSigmaFilter2;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QSpinBox *spinThreshold1;
    QSpinBox *spinThreshold2;
    QLabel *label_19;
    QWidget *tab_6;
    QLabel *label_20;
    QLabel *label_21;
    QSpinBox *spinRadius;
    QPushButton *houghCircleTransform;
    QLabel *label_22;
    QPushButton *selectTemplete;
    QSpinBox *spinThreshold;
    QLabel *label_23;
    QSpinBox *spinGeneralThreshold;
    QLabel *label_24;
    QPushButton *generalizedHoughTransform;
    QWidget *tab_7;
    QPushButton *getGaussianScaleImage;
    QLabel *label_25;
    QDoubleSpinBox *spinSigmaFilter_3;
    QLabel *label_26;
    QPushButton *getDOGScaleImage;
    QLabel *label_27;
    QPushButton *getKeyPointDetection;
    QLabel *label_28;
    QLabel *label_29;
    QPushButton *getKeyPointDescriptor;
    QLabel *label_30;
    QPushButton *getSIFTfeatureMatching;
    QPushButton *getFirstImage;
    QPushButton *getSecondImage;
    QWidget *tab_8;
    QPushButton *getImage;
    QPushButton *getImage_2;
    QPushButton *getOpticalFlow;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QListWidget *listWidget;

    void setupUi(QDialog *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->resize(819, 461);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainFrame->sizePolicy().hasHeightForWidth());
        MainFrame->setSizePolicy(sizePolicy);
        MainFrame->setMinimumSize(QSize(0, 461));
        MainFrame->setModal(false);
        verticalLayout = new QVBoxLayout(MainFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(MainFrame);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 41));
        frame->setMaximumSize(QSize(16777215, 41));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        buttonOpen = new QToolButton(frame);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));
        buttonOpen->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonOpen->sizePolicy().hasHeightForWidth());
        buttonOpen->setSizePolicy(sizePolicy2);
        buttonOpen->setMinimumSize(QSize(41, 41));
        buttonOpen->setMaximumSize(QSize(41, 41));
        buttonOpen->setLayoutDirection(Qt::LeftToRight);
        buttonOpen->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOpen->setIcon(icon);
        buttonOpen->setIconSize(QSize(41, 41));
        buttonOpen->setCheckable(false);
        buttonOpen->setAutoRepeat(false);
        buttonOpen->setAutoExclusive(false);
        buttonOpen->setPopupMode(QToolButton::DelayedPopup);
        buttonOpen->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonOpen->setAutoRaise(false);

        horizontalLayout_3->addWidget(buttonOpen);

        toolButton_2 = new QToolButton(frame);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        sizePolicy2.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy2);
        toolButton_2->setMinimumSize(QSize(41, 41));
        toolButton_2->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(frame);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        sizePolicy2.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy2);
        toolButton_3->setMinimumSize(QSize(41, 41));
        toolButton_3->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_3);

        buttonDeleteContents = new QToolButton(frame);
        buttonDeleteContents->setObjectName(QString::fromUtf8("buttonDeleteContents"));
        sizePolicy2.setHeightForWidth(buttonDeleteContents->sizePolicy().hasHeightForWidth());
        buttonDeleteContents->setSizePolicy(sizePolicy2);
        buttonDeleteContents->setMinimumSize(QSize(41, 41));
        buttonDeleteContents->setMaximumSize(QSize(41, 41));
        buttonDeleteContents->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/1-21.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDeleteContents->setIcon(icon1);
        buttonDeleteContents->setIconSize(QSize(41, 41));

        horizontalLayout_3->addWidget(buttonDeleteContents);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonShowList = new QToolButton(frame);
        buttonShowList->setObjectName(QString::fromUtf8("buttonShowList"));
        sizePolicy2.setHeightForWidth(buttonShowList->sizePolicy().hasHeightForWidth());
        buttonShowList->setSizePolicy(sizePolicy2);
        buttonShowList->setMinimumSize(QSize(41, 41));
        buttonShowList->setMaximumSize(QSize(41, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/2-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonShowList->setIcon(icon2);
        buttonShowList->setIconSize(QSize(82, 41));

        horizontalLayout_3->addWidget(buttonShowList);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, -1, -1, -1);
        tabWidget = new QTabWidget(MainFrame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setMinimumSize(QSize(299, 394));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush1(QColor(255, 85, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush1);
        tabWidget->setPalette(palette);
        tabWidget->setCursor(QCursor(Qt::ArrowCursor));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(31, 31));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 83, 31, 16));
        spinHue = new QSpinBox(tab_2);
        spinHue->setObjectName(QString::fromUtf8("spinHue"));
        spinHue->setGeometry(QRect(65, 80, 61, 22));
        spinHue->setAlignment(Qt::AlignCenter);
        spinHue->setMaximum(360);
        spinHue->setSingleStep(20);
        spinHue->setValue(250);
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(140, 83, 31, 16));
        spinSaturation = new QDoubleSpinBox(tab_2);
        spinSaturation->setObjectName(QString::fromUtf8("spinSaturation"));
        spinSaturation->setGeometry(QRect(163, 80, 62, 22));
        spinSaturation->setAlignment(Qt::AlignCenter);
        spinSaturation->setMaximum(1.000000000000000);
        spinSaturation->setSingleStep(0.100000000000000);
        spinSaturation->setValue(0.300000000000000);
        buttonSepiaTone = new QPushButton(tab_2);
        buttonSepiaTone->setObjectName(QString::fromUtf8("buttonSepiaTone"));
        buttonSepiaTone->setGeometry(QRect(30, 30, 201, 41));
        buttonSepiaTone->setAutoFillBackground(false);
        buttonSepiaTone->setIconSize(QSize(41, 41));
        buttonSepiaTone->setCheckable(false);
        buttonSepiaTone->setAutoRepeat(false);
        buttonSepiaTone->setAutoExclusive(false);
        buttonSepiaTone->setAutoDefault(true);
        buttonSepiaTone->setFlat(false);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        setOtsuAlgorithm = new QPushButton(tab_3);
        setOtsuAlgorithm->setObjectName(QString::fromUtf8("setOtsuAlgorithm"));
        setOtsuAlgorithm->setGeometry(QRect(60, 50, 171, 41));
        label = new QLabel(tab_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 201, 21));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 240, 191, 21));
        setLabelingAlgorithm = new QPushButton(tab_3);
        setLabelingAlgorithm->setObjectName(QString::fromUtf8("setLabelingAlgorithm"));
        setLabelingAlgorithm->setGeometry(QRect(60, 270, 171, 41));
        comboBox = new QComboBox(tab_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 140, 94, 22));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 110, 191, 21));
        Dilation = new QPushButton(tab_3);
        Dilation->setObjectName(QString::fromUtf8("Dilation"));
        Dilation->setGeometry(QRect(40, 190, 91, 31));
        Erosion = new QPushButton(tab_3);
        Erosion->setObjectName(QString::fromUtf8("Erosion"));
        Erosion->setGeometry(QRect(170, 190, 91, 31));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 20, 201, 16));
        histogramEqualization = new QPushButton(tab_4);
        histogramEqualization->setObjectName(QString::fromUtf8("histogramEqualization"));
        histogramEqualization->setGeometry(QRect(60, 50, 181, 41));
        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 120, 201, 16));
        selectSrcImage = new QPushButton(tab_4);
        selectSrcImage->setObjectName(QString::fromUtf8("selectSrcImage"));
        selectSrcImage->setGeometry(QRect(60, 160, 181, 28));
        selectTargetImage = new QPushButton(tab_4);
        selectTargetImage->setObjectName(QString::fromUtf8("selectTargetImage"));
        selectTargetImage->setGeometry(QRect(60, 200, 181, 28));
        histogramMatching = new QPushButton(tab_4);
        histogramMatching->setObjectName(QString::fromUtf8("histogramMatching"));
        histogramMatching->setGeometry(QRect(60, 250, 181, 41));
        tabWidget->addTab(tab_4, QString());
        histogramEqualization->raise();
        label_4->raise();
        label_7->raise();
        selectSrcImage->raise();
        selectTargetImage->raise();
        histogramMatching->raise();
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(40, 10, 211, 21));
        gaussian = new QPushButton(tab);
        gaussian->setObjectName(QString::fromUtf8("gaussian"));
        gaussian->setGeometry(QRect(150, 40, 121, 21));
        pepper_salt = new QPushButton(tab);
        pepper_salt->setObjectName(QString::fromUtf8("pepper_salt"));
        pepper_salt->setGeometry(QRect(70, 140, 161, 21));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(40, 200, 161, 31));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 40, 61, 21));
        spinSigma = new QDoubleSpinBox(tab);
        spinSigma->setObjectName(QString::fromUtf8("spinSigma"));
        spinSigma->setGeometry(QRect(70, 40, 64, 22));
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(40, 80, 221, 21));
        spinProbability = new QDoubleSpinBox(tab);
        spinProbability->setObjectName(QString::fromUtf8("spinProbability"));
        spinProbability->setGeometry(QRect(170, 110, 64, 21));
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(50, 110, 111, 21));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 280, 61, 21));
        gaussianFilter = new QPushButton(tab);
        gaussianFilter->setObjectName(QString::fromUtf8("gaussianFilter"));
        gaussianFilter->setGeometry(QRect(150, 280, 111, 21));
        spinSigmaFilter = new QDoubleSpinBox(tab);
        spinSigmaFilter->setObjectName(QString::fromUtf8("spinSigmaFilter"));
        spinSigmaFilter->setGeometry(QRect(60, 280, 64, 22));
        medianFilter = new QPushButton(tab);
        medianFilter->setObjectName(QString::fromUtf8("medianFilter"));
        medianFilter->setGeometry(QRect(150, 320, 111, 21));
        comboBox_2 = new QComboBox(tab);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(50, 320, 71, 21));
        boxFilter = new QPushButton(tab);
        boxFilter->setObjectName(QString::fromUtf8("boxFilter"));
        boxFilter->setGeometry(QRect(150, 240, 111, 21));
        boxFilteringBox = new QComboBox(tab);
        boxFilteringBox->addItem(QString());
        boxFilteringBox->addItem(QString());
        boxFilteringBox->setObjectName(QString::fromUtf8("boxFilteringBox"));
        boxFilteringBox->setGeometry(QRect(50, 240, 71, 21));
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        cannyEdgeOperator = new QPushButton(tab_5);
        cannyEdgeOperator->setObjectName(QString::fromUtf8("cannyEdgeOperator"));
        cannyEdgeOperator->setGeometry(QRect(50, 250, 201, 51));
        label_14 = new QLabel(tab_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 30, 201, 21));
        label_15 = new QLabel(tab_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(100, 60, 61, 21));
        spinSigmaFilter2 = new QDoubleSpinBox(tab_5);
        spinSigmaFilter2->setObjectName(QString::fromUtf8("spinSigmaFilter2"));
        spinSigmaFilter2->setGeometry(QRect(150, 60, 64, 22));
        label_16 = new QLabel(tab_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(40, 110, 221, 21));
        label_17 = new QLabel(tab_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(80, 170, 81, 21));
        label_18 = new QLabel(tab_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(80, 210, 81, 21));
        spinThreshold1 = new QSpinBox(tab_5);
        spinThreshold1->setObjectName(QString::fromUtf8("spinThreshold1"));
        spinThreshold1->setGeometry(QRect(170, 170, 43, 22));
        spinThreshold1->setMaximum(255);
        spinThreshold2 = new QSpinBox(tab_5);
        spinThreshold2->setObjectName(QString::fromUtf8("spinThreshold2"));
        spinThreshold2->setGeometry(QRect(170, 210, 43, 22));
        spinThreshold2->setMaximum(255);
        label_19 = new QLabel(tab_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(70, 130, 191, 31));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        label_20 = new QLabel(tab_6);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(50, 20, 191, 21));
        label_21 = new QLabel(tab_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(70, 50, 111, 21));
        spinRadius = new QSpinBox(tab_6);
        spinRadius->setObjectName(QString::fromUtf8("spinRadius"));
        spinRadius->setGeometry(QRect(180, 50, 49, 24));
        spinRadius->setMaximum(256);
        houghCircleTransform = new QPushButton(tab_6);
        houghCircleTransform->setObjectName(QString::fromUtf8("houghCircleTransform"));
        houghCircleTransform->setGeometry(QRect(50, 120, 201, 41));
        label_22 = new QLabel(tab_6);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(50, 170, 231, 41));
        selectTemplete = new QPushButton(tab_6);
        selectTemplete->setObjectName(QString::fromUtf8("selectTemplete"));
        selectTemplete->setGeometry(QRect(50, 210, 201, 31));
        spinThreshold = new QSpinBox(tab_6);
        spinThreshold->setObjectName(QString::fromUtf8("spinThreshold"));
        spinThreshold->setGeometry(QRect(180, 80, 49, 24));
        spinThreshold->setMaximum(256);
        label_23 = new QLabel(tab_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(40, 80, 141, 21));
        spinGeneralThreshold = new QSpinBox(tab_6);
        spinGeneralThreshold->setObjectName(QString::fromUtf8("spinGeneralThreshold"));
        spinGeneralThreshold->setGeometry(QRect(180, 260, 49, 21));
        spinGeneralThreshold->setMaximum(999);
        label_24 = new QLabel(tab_6);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(40, 260, 141, 21));
        generalizedHoughTransform = new QPushButton(tab_6);
        generalizedHoughTransform->setObjectName(QString::fromUtf8("generalizedHoughTransform"));
        generalizedHoughTransform->setGeometry(QRect(50, 290, 201, 41));
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        getGaussianScaleImage = new QPushButton(tab_7);
        getGaussianScaleImage->setObjectName(QString::fromUtf8("getGaussianScaleImage"));
        getGaussianScaleImage->setGeometry(QRect(50, 70, 201, 21));
        label_25 = new QLabel(tab_7);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(30, 10, 231, 21));
        spinSigmaFilter_3 = new QDoubleSpinBox(tab_7);
        spinSigmaFilter_3->setObjectName(QString::fromUtf8("spinSigmaFilter_3"));
        spinSigmaFilter_3->setGeometry(QRect(150, 40, 64, 22));
        label_26 = new QLabel(tab_7);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(100, 40, 61, 21));
        getDOGScaleImage = new QPushButton(tab_7);
        getDOGScaleImage->setObjectName(QString::fromUtf8("getDOGScaleImage"));
        getDOGScaleImage->setGeometry(QRect(50, 130, 201, 21));
        label_27 = new QLabel(tab_7);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(30, 100, 231, 21));
        getKeyPointDetection = new QPushButton(tab_7);
        getKeyPointDetection->setObjectName(QString::fromUtf8("getKeyPointDetection"));
        getKeyPointDetection->setGeometry(QRect(50, 190, 201, 21));
        label_28 = new QLabel(tab_7);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(30, 160, 231, 21));
        label_29 = new QLabel(tab_7);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(30, 220, 231, 21));
        getKeyPointDescriptor = new QPushButton(tab_7);
        getKeyPointDescriptor->setObjectName(QString::fromUtf8("getKeyPointDescriptor"));
        getKeyPointDescriptor->setGeometry(QRect(50, 250, 201, 21));
        label_30 = new QLabel(tab_7);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(30, 280, 231, 21));
        getSIFTfeatureMatching = new QPushButton(tab_7);
        getSIFTfeatureMatching->setObjectName(QString::fromUtf8("getSIFTfeatureMatching"));
        getSIFTfeatureMatching->setGeometry(QRect(50, 330, 201, 21));
        getFirstImage = new QPushButton(tab_7);
        getFirstImage->setObjectName(QString::fromUtf8("getFirstImage"));
        getFirstImage->setGeometry(QRect(50, 301, 91, 20));
        getSecondImage = new QPushButton(tab_7);
        getSecondImage->setObjectName(QString::fromUtf8("getSecondImage"));
        getSecondImage->setGeometry(QRect(160, 301, 91, 20));
        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        getImage = new QPushButton(tab_8);
        getImage->setObjectName(QString::fromUtf8("getImage"));
        getImage->setGeometry(QRect(60, 60, 171, 24));
        getImage_2 = new QPushButton(tab_8);
        getImage_2->setObjectName(QString::fromUtf8("getImage_2"));
        getImage_2->setGeometry(QRect(60, 130, 161, 24));
        getOpticalFlow = new QPushButton(tab_8);
        getOpticalFlow->setObjectName(QString::fromUtf8("getOpticalFlow"));
        getOpticalFlow->setGeometry(QRect(60, 200, 161, 24));
        label_31 = new QLabel(tab_8);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(60, 30, 171, 20));
        label_32 = new QLabel(tab_8);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(60, 100, 171, 20));
        label_33 = new QLabel(tab_8);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(60, 170, 171, 20));
        tabWidget->addTab(tab_8, QString());

        horizontalLayout->addWidget(tabWidget);

        listWidget = new QListWidget(MainFrame);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy4);
        listWidget->setMinimumSize(QSize(0, 394));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 127, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        QBrush brush6(QColor(120, 120, 120, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        QBrush brush7(QColor(240, 240, 240, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        listWidget->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(10);
        listWidget->setFont(font);

        horizontalLayout->addWidget(listWidget);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainFrame);

        tabWidget->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QDialog *MainFrame)
    {
        MainFrame->setWindowTitle(QCoreApplication::translate("MainFrame", "Homeworks", nullptr));
#if QT_CONFIG(tooltip)
        buttonOpen->setToolTip(QCoreApplication::translate("MainFrame", "open an image file", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonOpen->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("MainFrame", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainFrame", "...", nullptr));
#if QT_CONFIG(tooltip)
        buttonDeleteContents->setToolTip(QCoreApplication::translate("MainFrame", "close all forms", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonDeleteContents->setText(QString());
#if QT_CONFIG(tooltip)
        buttonShowList->setToolTip(QCoreApplication::translate("MainFrame", "show the list view", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonShowList->setText(QString());
        label_5->setText(QCoreApplication::translate("MainFrame", "Hue", nullptr));
        label_6->setText(QCoreApplication::translate("MainFrame", "Sat.", nullptr));
        buttonSepiaTone->setText(QCoreApplication::translate("MainFrame", "Sepia Tone", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainFrame", "1 ", nullptr));
        setOtsuAlgorithm->setText(QCoreApplication::translate("MainFrame", "Ostu Algorithm", nullptr));
        label->setText(QCoreApplication::translate("MainFrame", "1. Otsu Algorithm \354\240\201\354\232\251", nullptr));
        label_2->setText(QCoreApplication::translate("MainFrame", "3. Labeling \354\240\201\354\232\251", nullptr));
        setLabelingAlgorithm->setText(QCoreApplication::translate("MainFrame", "Labeling Algorithm", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainFrame", "3x3", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainFrame", "5x5", nullptr));

        label_3->setText(QCoreApplication::translate("MainFrame", "2. Dilation and Erosion \354\240\201\354\232\251", nullptr));
        Dilation->setText(QCoreApplication::translate("MainFrame", "Dilation", nullptr));
        Erosion->setText(QCoreApplication::translate("MainFrame", "Erosion", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainFrame", "2 ", nullptr));
        label_4->setText(QCoreApplication::translate("MainFrame", "1. Histogram Equalization", nullptr));
        histogramEqualization->setText(QCoreApplication::translate("MainFrame", "Histogram Equalization", nullptr));
        label_7->setText(QCoreApplication::translate("MainFrame", "2. Histogram Matching", nullptr));
        selectSrcImage->setText(QCoreApplication::translate("MainFrame", "Select source image", nullptr));
        selectTargetImage->setText(QCoreApplication::translate("MainFrame", "Select target image", nullptr));
        histogramMatching->setText(QCoreApplication::translate("MainFrame", "Histogram Matching", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainFrame", "3 ", nullptr));
        label_8->setText(QCoreApplication::translate("MainFrame", "1-1. Obtain a gaussian noise", nullptr));
        gaussian->setText(QCoreApplication::translate("MainFrame", "Gaussian Noise", nullptr));
        pepper_salt->setText(QCoreApplication::translate("MainFrame", "Pepper And Salt Noise", nullptr));
        label_9->setText(QCoreApplication::translate("MainFrame", "2. Apply a filter", nullptr));
        label_10->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        label_12->setText(QCoreApplication::translate("MainFrame", "1-2. Obtain Pepper & Salt nose", nullptr));
        label_13->setText(QCoreApplication::translate("MainFrame", "Probability (0~1)", nullptr));
        label_11->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        gaussianFilter->setText(QCoreApplication::translate("MainFrame", "Gaussian Filter", nullptr));
        medianFilter->setText(QCoreApplication::translate("MainFrame", "Median Filter", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainFrame", "3x3", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainFrame", "5x5", nullptr));

        boxFilter->setText(QCoreApplication::translate("MainFrame", "Box Filter", nullptr));
        boxFilteringBox->setItemText(0, QCoreApplication::translate("MainFrame", "3x3", nullptr));
        boxFilteringBox->setItemText(1, QCoreApplication::translate("MainFrame", "5x5", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainFrame", "4 ", nullptr));
        cannyEdgeOperator->setText(QCoreApplication::translate("MainFrame", "Canny Edge Operator", nullptr));
        label_14->setText(QCoreApplication::translate("MainFrame", "1. Gaussian Sigma ", nullptr));
        label_15->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        label_16->setText(QCoreApplication::translate("MainFrame", "2. Hysteresis based Threshold ", nullptr));
        label_17->setText(QCoreApplication::translate("MainFrame", "Threshold 1", nullptr));
        label_18->setText(QCoreApplication::translate("MainFrame", "Threshold 2", nullptr));
        label_19->setText(QCoreApplication::translate("MainFrame", "(Threshold 1 < Threshold 2)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainFrame", "5", nullptr));
        label_20->setText(QCoreApplication::translate("MainFrame", "1. Hough Circle Transform", nullptr));
        label_21->setText(QCoreApplication::translate("MainFrame", "Radius (pixel) :", nullptr));
        houghCircleTransform->setText(QCoreApplication::translate("MainFrame", "Hough Circle Transform", nullptr));
        label_22->setText(QCoreApplication::translate("MainFrame", "2. Generalized Hough Transform", nullptr));
        selectTemplete->setText(QCoreApplication::translate("MainFrame", "Select data file", nullptr));
        label_23->setText(QCoreApplication::translate("MainFrame", "Threshold (0~255) :", nullptr));
        label_24->setText(QCoreApplication::translate("MainFrame", "Threshold (0~255) :", nullptr));
        generalizedHoughTransform->setText(QCoreApplication::translate("MainFrame", "Generalized Hough Transform", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainFrame", "6", nullptr));
        getGaussianScaleImage->setText(QCoreApplication::translate("MainFrame", "Get Gaussian scale Image", nullptr));
        label_25->setText(QCoreApplication::translate("MainFrame", "1. Display Gaussian scale space", nullptr));
        label_26->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        getDOGScaleImage->setText(QCoreApplication::translate("MainFrame", "Get DOG scale Image", nullptr));
        label_27->setText(QCoreApplication::translate("MainFrame", "2. Display DOG scale space", nullptr));
        getKeyPointDetection->setText(QCoreApplication::translate("MainFrame", "Key point Detection", nullptr));
        label_28->setText(QCoreApplication::translate("MainFrame", "3. SIFT key point detection", nullptr));
        label_29->setText(QCoreApplication::translate("MainFrame", "4. SIFT Descriptor", nullptr));
        getKeyPointDescriptor->setText(QCoreApplication::translate("MainFrame", "SIFT Descriptor", nullptr));
        label_30->setText(QCoreApplication::translate("MainFrame", "5. SIFT feature matching", nullptr));
        getSIFTfeatureMatching->setText(QCoreApplication::translate("MainFrame", "SIFT feature matching", nullptr));
        getFirstImage->setText(QCoreApplication::translate("MainFrame", "1st Image", nullptr));
        getSecondImage->setText(QCoreApplication::translate("MainFrame", "2nd Image", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("MainFrame", "7", nullptr));
        getImage->setText(QCoreApplication::translate("MainFrame", "Get 1st Image", nullptr));
        getImage_2->setText(QCoreApplication::translate("MainFrame", "Get 2nd Image", nullptr));
        getOpticalFlow->setText(QCoreApplication::translate("MainFrame", "Optical Flow", nullptr));
        label_31->setText(QCoreApplication::translate("MainFrame", "1. Get First Image", nullptr));
        label_32->setText(QCoreApplication::translate("MainFrame", "2. Get Second Image", nullptr));
        label_33->setText(QCoreApplication::translate("MainFrame", "3. Optical Flow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QCoreApplication::translate("MainFrame", "8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
