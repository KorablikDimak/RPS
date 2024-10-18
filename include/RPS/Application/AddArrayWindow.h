#ifndef RPS_Application_AddArrayWindow_H
#define RPS_Application_AddArrayWindow_H

#include <QDialog>

namespace RPS::Application
{
    QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class AddArrayWindow;
    }
    QT_END_NAMESPACE

    class AddArrayWindow : public QDialog
    {
    Q_OBJECT

    public:
        explicit AddArrayWindow(QWidget* parent = nullptr) noexcept;
        ~AddArrayWindow() override;

    signals:
        void SaveClicked(const QString& arrayText);

    private:
        Ui::AddArrayWindow* _ui;

    private slots:
        void SaveButtonClicked() noexcept;
        void CancelButtonClicked() noexcept;
    };
}

#endif