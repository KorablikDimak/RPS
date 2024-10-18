#ifndef RPS_Application_MainWindow_H
#define RPS_Application_MainWindow_H

#include <QWidget>
#include <QListWidgetItem>

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
        explicit MainWindow(QWidget* parent = nullptr) noexcept;
        ~MainWindow() override;

    private:
        Ui::MainWindow* _ui;

    private slots:
        void ListWidgetItemClicked(QListWidgetItem* arrayItem) noexcept;
        void AddArrayButtonClicked() noexcept;
        void UpdateItem(const QString& arrayText, int row) noexcept;
        void AddNewItem(const QString& arrayText) noexcept;
    };
}

#endif