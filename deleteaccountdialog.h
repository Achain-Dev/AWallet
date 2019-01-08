#ifndef DELETEACCOUNTDIALOG_H
#define DELETEACCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteAccountDialog;
}

class WaitingPage;

class DeleteAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteAccountDialog(QString name, QWidget *parent = 0);
    ~DeleteAccountDialog();

    bool pop();

private:
	void onCheckPasswordCallback(const QString &result);
	void onAccountDeleteCallback(const QString &result);
	
private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_pwdLineEdit_textChanged(const QString &arg1);

    void on_pwdLineEdit_returnPressed();

private:
    Ui::DeleteAccountDialog *ui;
	WaitingPage* waitingPage;
    QString accountName;
    bool yesOrNo;
};

#endif // DELETEACCOUNTDIALOG_H