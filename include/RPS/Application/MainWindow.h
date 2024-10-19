#ifndef RPS_Application_MainWindow_H
#define RPS_Application_MainWindow_H

#include <QWidget>
#include <QListWidgetItem>

#include "Repository.h"
#include "Array.h"

namespace RPS::Application
{
    QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class MainWindow;
    }
    QT_END_NAMESPACE

    class MainWindow : public QWidget
    {
    Q_OBJECT

    public:
        explicit MainWindow(const Repository<Array<double>>* repository,
                            QWidget* parent = nullptr) noexcept;
        ~MainWindow() override;

    private:
        Ui::MainWindow* _ui;
        const Repository<Array<double>>* _repository;
        std::map<int, Array<double>> _arrays;

    public slots:
        void UpdateWindow() noexcept;

    private slots:
        void ListWidgetItemClicked(QListWidgetItem* arrayItem) noexcept;
        void AddArrayButtonClicked() noexcept;
    };
}

#endif