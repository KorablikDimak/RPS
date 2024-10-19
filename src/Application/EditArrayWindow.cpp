#include <ExtendedCpp/LINQ.h>

#include "EditArrayWindow.h"
#include "ui_EditArrayWindow.h"
#include "Utility.h"

namespace RPS::Application
{
    EditArrayWindow::EditArrayWindow(const Repository<Array<double>>& repository,
                                     const Array<double>& array, QWidget* parent) noexcept :
            QDialog(parent), _ui(new Ui::EditArrayWindow), _array(array), _repository(repository)
    {
        _ui->setupUi(this);

        QString arrayText = ExtendedCpp::LINQ::From(_array.inner_array)
                .Select([](double number){ return std::to_string(number); })
                .Aggregate<std::string>([](std::string result, const std::string& number)
                                        { result += number; return result; }).c_str();
        _ui->ArrayEdit->setPlainText(arrayText);

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
        if (_ui->ArrayEdit->toPlainText().isEmpty())
        {
            _repository.Delete(_array);
            emit Updated();
        }
        else if (Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString())))
        {
            _array.inner_array = Utility::ParseArray(Utility::SplitString(_ui->ArrayEdit->toPlainText().toStdString()));
            _repository.Update(_array);
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
            _array = _repository.Sort(_array);
            QString arrayText = ExtendedCpp::LINQ::From(_array.inner_array)
                    .Select([](double number){ return std::to_string(number); })
                    .Aggregate<std::string>([](std::string result, const std::string& number)
                                            { result += number; return result; }).c_str();
            _ui->ArrayEdit->setPlainText(arrayText);
            emit Updated();
        }
    }

    void EditArrayWindow::DeleteButtonClicked() noexcept
    {
        _repository.Delete(_array);
        emit Updated();
        this->close();
    }
}