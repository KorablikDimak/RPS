#include <sstream>

#include <ExtendedCpp/LINQ.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "EditArrayWindow.h"
#include "AddArrayWindow.h"

namespace RPS::Application
{
    MainWindow::MainWindow(const Api& api, QWidget* parent) noexcept :
            QWidget(parent), _ui(new Ui::MainWindow), _api(api)
    {
        _ui->setupUi(this);
        if (!connect(_ui->ArrayList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,
                     SLOT(ListWidgetItemClicked(QListWidgetItem*))))
            std::terminate();
        if (!connect(_ui->AddArrayButton, SIGNAL(clicked()), this, SLOT(AddArrayButtonClicked())))
            std::terminate();
    }

    MainWindow::~MainWindow()
    {
        delete _ui;
    }

    void MainWindow::UpdateWindow() noexcept
    {
        std::vector<Array<double>> arrays = _api.GetArrays();
        _ui->ArrayList->clear();
        _arrays.clear();

        for (const auto& stringArray : arrays)
        {
            QString array = ExtendedCpp::LINQ::From(stringArray.inner_array)
                    .Select([](double number){ return std::to_string(number); })
                    .Aggregate<std::string>([](std::string result, const std::string& array)
                                            { result += array; return result; }).c_str();

            // TODO add item
        }
    }

    void MainWindow::ListWidgetItemClicked(QListWidgetItem* arrayItem) noexcept
    {
        auto* editArrayWindow = new EditArrayWindow(arrayItem->text());
        if (!connect(editArrayWindow, &EditArrayWindow::SaveClicked, this,
                     [this, arrayItem](const QString& arrayText){ UpdateItem(arrayText, _ui->ArrayList->row(arrayItem)); }))
            std::terminate();
        if (!connect(editArrayWindow, &EditArrayWindow::SortClicked, this,
                     [this, arrayItem](const QString& arrayText)
                     { UpdateItem(arrayText, _ui->ArrayList->row(arrayItem));
                       SortArray(_ui->ArrayList->row(arrayItem)); }))
            std::terminate();
        editArrayWindow->show();
    }

    void MainWindow::AddArrayButtonClicked() noexcept
    {
        auto* addArrayWindow = new AddArrayWindow();
        if (!connect(addArrayWindow, SIGNAL(SaveClicked(QString)), this, SLOT(AddNewItem(QString))))
            std::terminate();
        addArrayWindow->show();
    }

    void MainWindow::UpdateItem(const QString &arrayText, const int row) noexcept
    {
        if (arrayText.isEmpty())
        {
            _ui->ArrayList->removeItemWidget(_ui->ArrayList->item(row));
            delete _ui->ArrayList->item(row);
        }
        else
            _ui->ArrayList->item(row)->setText(arrayText);
    }

    void MainWindow::AddNewItem(const QString& arrayText) noexcept
    {
        _ui->ArrayList->addItem(arrayText);
        _ui->ArrayList->item(_ui->ArrayList->count() - 1)
            ->setSizeHint(QSize(_ui->ArrayList->item(0)->sizeHint().width(), 40));

        QFont font = _ui->ArrayList->item(0)->font();
        font.setPointSize(14);
        _ui->ArrayList->item(_ui->ArrayList->count() - 1)->setFont(font);
    }

    void MainWindow::SortArray([[maybe_unused]] const int row) noexcept
    {

    }
}