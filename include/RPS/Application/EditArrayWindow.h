#ifndef RPS_Application_EditArrayWindow_H
#define RPS_Application_EditArrayWindow_H

#include <QDialog>

namespace RPS::Application
{
    QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class EditArrayWindow;
    }
    QT_END_NAMESPACE

    class EditArrayWindow : public QDialog
    {
    Q_OBJECT

    public:
        explicit EditArrayWindow(const QString& editText, QWidget* parent = nullptr) noexcept;
        ~EditArrayWindow() override;

    signals:
        void SaveClicked(const QString& arrayText);
        void SortClicked(const QString& arrayText);

    private:
        Ui::EditArrayWindow* _ui;

    private slots:
        void SaveButtonClicked() noexcept;
        void CancelButtonClicked() noexcept;
        void SortButtonClicked() noexcept;
        void DeleteButtonClicked() noexcept;
    };
}

#endif