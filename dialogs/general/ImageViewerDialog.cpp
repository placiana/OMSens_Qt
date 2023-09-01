
#include "ImageViewerDialog.h"
#include <QLabel>
#include <QScrollArea>
#include <QGuiApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScreen>
#include <QDir>
#include <QMargins>

ImageViewerDialog::ImageViewerDialog(QString filePath, QWidget *parent)
   : QDialog(parent),
     imageLabel(new QLabel),
     scrollArea(new QScrollArea)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);

    loadFile(filePath);

    // New layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    // Assign table view to layout
    mainLayout->addWidget(scrollArea);
    // Set Dialog layout
    setLayout(mainLayout);

}


bool ImageViewerDialog::loadFile(const QString &fileName)
{
     QImageReader reader(fileName);
     //reader.setAutoTransform(true);
     const QImage newImage = reader.read();
     if (newImage.isNull()) {
         QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                  tr("Cannot load %1: %2")
                                  .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
         return false;
     }

     setImage(newImage);

     setWindowFilePath(fileName);

     resize(newImage.size().grownBy(*new QMargins(0,0, 30, 30)));

     return true;
}

void ImageViewerDialog::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scrollArea->setVisible(true);
    imageLabel->adjustSize();
}

QStringList ImageViewerDialog::compatibleMIMETypes()
{

// Static methods (class methods)
    // Get the valid MIME types compatible with ImageViewer
    QStringList mimeTypeFilters;
    const QList< QByteArray> supportedMimeTypes = QImageReader::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
//    if (acceptMode == QFileDialog::AcceptSave)
//        dialog.setDefaultSuffix("jpg");
    return mimeTypeFilters;

}
