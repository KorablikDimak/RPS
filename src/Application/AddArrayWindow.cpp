#include "AddArrayWindow.h"
#include "ui_AddArrayWindow.h"
#include "Utility.h"

namespace RPS::Application
{
    AddArrayWindow::AddArrayWindow(const Repository<Array<double>>& repository,
                                   QWidget* parent) noexcept :
            QDialog(parent), _ui(new Ui::AddArrayWindow), _repository(repository)
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
            Array<double> array;
            array.inner_array = Utility::ParseArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString()));
            _repository.Add(array);
            emit Updated();
        }

        this->close();
    }

    void AddArrayWindow::CancelButtonClicked() noexcept
    {
        this->close();
    }
}