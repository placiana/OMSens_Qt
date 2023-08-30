#include "ParametersSimpleTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHeaderView>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>

ParametersSimpleTab::ParametersSimpleTab(QList<ParameterInclusion> params_inclusion, QString quickExplanation, QWidget *parent) : QWidget(parent)
{
  paramColPos = 0;
  cboxColPos  = 1;
  // Initialize label with brief description of the analysis
  mpBriefDescriptionLabel = new QLabel(quickExplanation,this);


  //Initialize table header
  mpParametersTable = new QTableWidget(0, 2);
  const QList<QString> tableHeaders( QList<QString>()
                                     << "Parameter"
                                     << "Perturb?"
                                     );
  mpParametersTable->setHorizontalHeaderLabels(tableHeaders);
  // Declare the QPair outside the foreach because the commas are ambigous for Qt's macro
  foreach (ParameterInclusion param_include, params_inclusion)
  {
    // Add a row
    // Row index to add row to
    const int rowNum = mpParametersTable->rowCount();
    // Add "blank" row
    mpParametersTable->insertRow(rowNum);
    // Fill blank row with values corresponding to this variable
    // Set parameter name
    QLabel *paramNameWidget = new QLabel(param_include.name);
    mpParametersTable->setCellWidget(rowNum,paramColPos, paramNameWidget);
    // Set checkbox
    QCheckBox *includeCheckBox = new QCheckBox;
    includeCheckBox->setChecked(param_include.include);
    mpParametersTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
  }
  // Set table settings
  // Resize columns to contents
  mpParametersTable->resizeColumnsToContents();

  // toggle selection
  QCheckBox *selectAllCheckBox = new QCheckBox("Select/deselect all");
  selectAllCheckBox->setChecked(Qt::Checked);
  connect(selectAllCheckBox, &QCheckBox::stateChanged, this, &ParametersSimpleTab::toggleSelectAll);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  // Parameters table/list
  mainLayout->addWidget(mpParametersTable);

  mainLayout->addWidget(selectAllCheckBox);
  // Description
  mainLayout->addWidget(mpBriefDescriptionLabel);
  setLayout(mainLayout);
}

QTableWidget *ParametersSimpleTab::getParametersTable() const
{
  return mpParametersTable;
}

void ParametersSimpleTab::toggleSelectAll(int checkState)
{
    for (int i=0; i< mpParametersTable->rowCount();++i) {
        QCheckBox *currentCb = (QCheckBox*) mpParametersTable->cellWidget(i, cboxColPos);
        currentCb->setChecked(checkState);
    }

    return;
}

