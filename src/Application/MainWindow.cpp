#include <QPushButton>
#include <ExtendedCpp/LINQ.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "EditArrayWindow.h"
#include "AddArrayWindow.h"

namespace RPS::Application
{
    MainWindow::MainWindow(const Repository<Array<double>>* repository, QWidget* parent) noexcept :
            QWidget(parent), _ui(new Ui::MainWindow), _repository(repository)
    {
        _ui->setupUi(this);
        if (!connect(_ui->ArrayList, &QListWidget::itemDoubleClicked, this, &MainWindow::ListWidgetItemClicked))
            std::terminate();
        if (!connect(_ui->AddArrayButton, &QPushButton::clicked, this, &MainWindow::AddArrayButtonClicked))
            std::terminate();
        UpdateWindow();
    }

    MainWindow::~MainWindow()
    {
        delete _ui;
    }

    void MainWindow::UpdateWindow() noexcept
    {
        std::vector<Array<double>> arrays = _repository->Get();
        _arrays.clear();
        _ui->ArrayList->clear();

        int count = 0;
        for (const auto& array : arrays)
        {
            std::ostringstream stream;
            for (const auto number : array.inner_array)
                stream << number << " ";
            _ui->ArrayList->addItem(stream.str().c_str());
            _arrays.insert(std::make_pair(count, array));
            ++count;
        }
    }

    void MainWindow::ListWidgetItemClicked(QListWidgetItem* arrayItem) noexcept
    {
        auto* editArrayWindow = new EditArrayWindow(_repository, _arrays.at(_ui->ArrayList->row(arrayItem)));
        if (!connect(editArrayWindow, &EditArrayWindow::Updated, this, &MainWindow::UpdateWindow))
            std::terminate();
        editArrayWindow->show();
    }

    void MainWindow::AddArrayButtonClicked() noexcept
    {
        auto* addArrayWindow = new AddArrayWindow(_repository);
        if (!connect(addArrayWindow, &AddArrayWindow::Updated, this, &MainWindow::UpdateWindow))
            std::terminate();
        addArrayWindow->show();
    }
}