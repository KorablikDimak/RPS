#ifndef RPS_Application_AddArrayWindow_H
#define RPS_Application_AddArrayWindow_H

#include <QDialog>

#include "Repository.h"
#include "Array.h"

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
        explicit AddArrayWindow(const Repository<Array<double>>& repository,
                                QWidget* parent = nullptr) noexcept;
        ~AddArrayWindow() override;

    signals:
        void Updated() const;

    private:
        Ui::AddArrayWindow* _ui;
        Repository<Array<double>> _repository;

    private slots:
        void SaveButtonClicked() noexcept;
        void CancelButtonClicked() noexcept;
    };
}

#endif