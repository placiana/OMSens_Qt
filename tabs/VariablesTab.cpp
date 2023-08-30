#include "VariablesTab.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>
#include <iostream>


// Constructors
VariablesTab::VariablesTab(QList<VariableInclusion> vars_inclusion, QWidget *parent) : QWidget(parent)
{
    mpVariablesTable = new QTableWidget(0, 2);
    const QList<QString> tableHeaders( QList<QString>()
                                     << "Variable"
                                     << "analyze?"
                                     );
    mpVariablesTable->setHorizontalHeaderLabels(tableHeaders);

    foreach (VariableInclusion var_include, vars_inclusion)
    {
        // Add a row
        // Row index to add row to
        const int rowNum = mpVariablesTable->rowCount();
        // Add "blank" row
        mpVariablesTable->insertRow(rowNum);
        // Fill blank row with values corresponding to this variable
        // Set variable name
        QLabel *varNameWidget = new QLabel(var_include.name);
        mpVariablesTable->setCellWidget(rowNum,varColPos, varNameWidget);
        // Set checkbox
        // Wrap the checkbox in a generic QWidget so we can set a layout to center it in the cell
        QCheckBox *includeCheckBox = new QCheckBox;
        includeCheckBox->setChecked(var_include.include);

        mpVariablesTable->setCellWidget(rowNum,cboxColPos,includeCheckBox);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mpVariablesTable);

    // toggle selection
    QCheckBox *selectAllCheckBox = new QCheckBox("Select/deselect all");
    selectAllCheckBox->setChecked(Qt::Checked);
    connect(selectAllCheckBox    , &QCheckBox::stateChanged, this, &VariablesTab::toggleSelectAll);
    mainLayout->addWidget(selectAllCheckBox);

    setLayout(mainLayout);
}

// Methods
QTableWidget *VariablesTab::getVariablesTable() const
{
    return mpVariablesTable;
}

void VariablesTab::toggleSelectAll(int checkState)
{
    for (int i=0; i< mpVariablesTable->rowCount();++i) {
        QCheckBox *currentCb = (QCheckBox*) mpVariablesTable->cellWidget(i, cboxColPos);
        currentCb->setChecked(checkState);
    }

    return;
}

