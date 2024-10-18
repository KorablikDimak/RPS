#include "EditArrayWindow.h"
#include "ui_EditArrayWindow.h"
#include "Utility.h"

namespace RPS::Application
{
    EditArrayWindow::EditArrayWindow(const QString& editText, QWidget* parent) noexcept :
            QDialog(parent), _ui(new Ui::EditArrayWindow)
    {
        _ui->setupUi(this);
        _ui->ArrayEdit->setPlainText(editText);
        if (!connect(_ui->SaveButton, SIGNAL(clicked()), this, SLOT(SaveButtonClicked())))
            std::terminate();
        if (!connect(_ui->CancelButton, SIGNAL(clicked()), this, SLOT(CancelButtonClicked())))
            std::terminate();
        if (!connect(_ui->SortButton, SIGNAL(clicked()), this, SLOT(SortButtonClicked())))
            std::terminate();
        if (!connect(_ui->DeleteButton, SIGNAL(clicked()), this, SLOT(DeleteButtonClicked())))
            std::terminate();
    }

    EditArrayWindow::~EditArrayWindow()
    {
        delete _ui;
    }

    void EditArrayWindow::SaveButtonClicked() noexcept
    {
        if (Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString())))
            emit SaveClicked(_ui->ArrayEdit->toPlainText());
        this->close();
    }

    void EditArrayWindow::CancelButtonClicked() noexcept
    {
        this->close();
    }

    void EditArrayWindow::SortButtonClicked() noexcept
    {
        if (!_ui->ArrayEdit->toPlainText().isEmpty() &&
            Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString())))
        {
            emit SortClicked(_ui->ArrayEdit->toPlainText());
            this->setEnabled(false);
        }
    }

    void EditArrayWindow::DeleteButtonClicked() noexcept
    {
        emit SaveClicked("");
        this->close();
    }
}