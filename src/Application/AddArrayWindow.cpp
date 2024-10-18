#include "AddArrayWindow.h"
#include "ui_AddArrayWindow.h"
#include "Utility.h"

namespace RPS::Application
{
    AddArrayWindow::AddArrayWindow(QWidget* parent) noexcept :
            QDialog(parent), _ui(new Ui::AddArrayWindow)
    {
        _ui->setupUi(this);
        if (!connect(_ui->SaveButton, SIGNAL(clicked()), this, SLOT(SaveButtonClicked())))
            std::terminate();
        if (!connect(_ui->CancelButton, SIGNAL(clicked()), this, SLOT(CancelButtonClicked())))
            std::terminate();
    }

    AddArrayWindow::~AddArrayWindow()
    {
        delete _ui;
    }

    void AddArrayWindow::SaveButtonClicked() noexcept
    {
        if (!_ui->ArrayEdit->toPlainText().isEmpty() &&
            Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString())))
        {
            emit SaveClicked(_ui->ArrayEdit->toPlainText());
        }

        this->close();
    }

    void AddArrayWindow::CancelButtonClicked() noexcept
    {
        this->close();
    }
}