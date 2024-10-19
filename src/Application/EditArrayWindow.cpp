#include <sstream>

#include <QPushButton>

#include "EditArrayWindow.h"
#include "ui_EditArrayWindow.h"
#include "Utility.h"

namespace RPS::Application
{
    EditArrayWindow::EditArrayWindow(const Repository<Array<double>>* repository,
                                     const Array<double>& array, QWidget* parent) noexcept :
            QDialog(parent), _ui(new Ui::EditArrayWindow), _array(array), _repository(repository)
    {
        _ui->setupUi(this);

        std::ostringstream stream;
        for (const auto number : _array.inner_array)
            stream << number << " ";
        _ui->ArrayEdit->setPlainText(stream.str().c_str());

        if (!connect(_ui->SaveButton, &QPushButton::clicked, this, &EditArrayWindow::SaveButtonClicked))
            std::terminate();
        if (!connect(_ui->CancelButton, &QPushButton::clicked, this, &EditArrayWindow::CancelButtonClicked))
            std::terminate();
        if (!connect(_ui->SortButton, &QPushButton::clicked, this, &EditArrayWindow::SortButtonClicked))
            std::terminate();
        if (!connect(_ui->DeleteButton, &QPushButton::clicked, this, &EditArrayWindow::DeleteButtonClicked))
            std::terminate();
    }

    EditArrayWindow::~EditArrayWindow()
    {
        delete _ui;
    }

    void EditArrayWindow::SaveButtonClicked() noexcept
    {
        if (_ui->ArrayEdit->toPlainText().isEmpty())
        {
            _repository->Delete(_array);
            emit Updated();
        }
        else if (Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString())))
        {
            _array.inner_array = Utility::ParseArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString()));
            _repository->Update(_array);
            emit Updated();
        }

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
            _array.inner_array = Utility::ParseArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString()));
            _array = _repository->Sort(_array);
            std::ostringstream stream;
            for (const auto number : _array.inner_array)
                stream << number << " ";
            _ui->ArrayEdit->setPlainText(stream.str().c_str());
            emit Updated();
        }
    }

    void EditArrayWindow::DeleteButtonClicked() noexcept
    {
        _repository->Delete(_array);
        emit Updated();
        this->close();
    }
}