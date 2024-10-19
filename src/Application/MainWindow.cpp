#include <ExtendedCpp/LINQ.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "EditArrayWindow.h"
#include "AddArrayWindow.h"

namespace RPS::Application
{
    MainWindow::MainWindow(const Repository<Array<double>>& repository, QWidget* parent) noexcept :
            QWidget(parent), _ui(new Ui::MainWindow), _repository(repository)
    {
        _ui->setupUi(this);
        if (!connect(_ui->ArrayList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,
                     SLOT(ListWidgetItemClicked(QListWidgetItem*))))
            std::terminate();
        if (!connect(_ui->AddArrayButton, SIGNAL(clicked()), this,
                     SLOT(AddArrayButtonClicked())))
            std::terminate();
    }

    MainWindow::~MainWindow()
    {
        delete _ui;
    }

    void MainWindow::UpdateWindow() noexcept
    {
        std::vector<Array<double>> arrays = _repository.Get();
        _ui->ArrayList->clear();

        int count = 0;
        for (const auto& array : arrays)
        {
            QString arrayText = ExtendedCpp::LINQ::From(array.inner_array)
                    .Select([](double number){ return std::to_string(number); })
                    .Aggregate<std::string>([](std::string result, const std::string& number)
                                            { result += number; return result; }).c_str();
            _ui->ArrayList->addItem(arrayText);
            _arrays.insert(std::make_pair(count, array));
            ++count;
        }
    }

    void MainWindow::ListWidgetItemClicked(QListWidgetItem* arrayItem) noexcept
    {
        auto* editArrayWindow = new EditArrayWindow(_repository,
                                                    _arrays.at(_ui->ArrayList->row(arrayItem)));
        editArrayWindow->show();
    }

    void MainWindow::AddArrayButtonClicked() noexcept
    {
        auto* addArrayWindow = new AddArrayWindow(_repository);
        addArrayWindow->show();
    }
}