/********************************************************************************
** Form generated from reading UI file 'imageform.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEFORM_H
#define UI_IMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageForm
{
public:

    void setupUi(QWidget *ImageForm)
    {
        if (ImageForm->objectName().isEmpty())
            ImageForm->setObjectName(QString::fromUtf8("ImageForm"));
        ImageForm->resize(368, 285);
        ImageForm->setFocusPolicy(Qt::ClickFocus);

        retranslateUi(ImageForm);

        QMetaObject::connectSlotsByName(ImageForm);
    } // setupUi

    void retranslateUi(QWidget *ImageForm)
    {
        ImageForm->setWindowTitle(QCoreApplication::translate("ImageForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageForm: public Ui_ImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEFORM_H
