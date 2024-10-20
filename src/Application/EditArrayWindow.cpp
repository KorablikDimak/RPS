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

        QPalette redText;
        redText.setColor(QPalette::WindowText, Qt::red);
        _ui->ErrorLabel->setPalette(redText);
        _ui->ErrorLabel->setVisible(false);

        std::ostringstream stream;
        for (const auto number : _array.inner_array)
            stream << number << " ";
        _ui->ArrayEdit->setText(stream.str().c_str());

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
        if (_ui->ArrayEdit->text().isEmpty())
        {
            _repository->Delete(_array);
            emit Updated();
            this->close();
        }
        else if (Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->text().toStdString())))
        {
            _array.inner_array = Utility::ParseArray(Utility::SplitString(_ui->ArrayEdit->text().toStdString()));
            _repository->Update(_array);
            emit Updated();
            this->close();
        }
        else
        {
            _ui->ErrorLabel->setVisible(true);
        }
    }

    void EditArrayWindow::CancelButtonClicked() noexcept
    {
        this->close();
    }

    void EditArrayWindow::SortButtonClicked() noexcept
    {
        if (!_ui->ArrayEdit->text().isEmpty() &&
            Utility::IsNumberArray(Utility::SplitString(_ui->ArrayEdit->text().toStdString())))
        {
            _ui->ErrorLabel->setVisible(false);
            _array.inner_array = Utility::ParseArray(Utility::SplitString(_ui->ArrayEdit->text().toStdString()));
            _array = _repository->Sort(_array);
            std::ostringstream stream;
            for (const auto number : _array.inner_array)
                stream << number << " ";
            _ui->ArrayEdit->setText(stream.str().c_str());
            emit Updated();
        }
        else
        {
            _ui->ErrorLabel->setVisible(true);
        }
    }

    void EditArrayWindow::DeleteButtonClicked() noexcept
    {
        _repository->Delete(_array);
        emit Updated();
        this->close();
    }
}