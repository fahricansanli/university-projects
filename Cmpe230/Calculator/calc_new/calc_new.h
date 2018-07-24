#ifndef CALC_NEW_H
#define CALC_NEW_H

#include <QWidget>

class QLineEdit;
class Button;

class calc_new : public QWidget
{
    Q_OBJECT

public:
    calc_new(QWidget *parent = 0);
    ~calc_new();

private slots:
    void digitClicked();
    void hexDigitClicked();
    void clearAll();
    void divisionButtonClicked();
    void timesButtonClicked();
    void minusButtonClicked();
    void plusButtonClicked();
    void equalButtonClicked();
    void decButtonClicked();
    void hexButtonClicked();
    void handlePrevOperation();

private:
    Button *createButton(const QString &text, const char *member);

    bool error;
    int base;
    int display_value;
    int sum;
    bool hexMode;
    QLineEdit *display;

    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
    enum { HexDigitButtons = 6 };
    Button *hexDigitButtons[HexDigitButtons];

    enum Oper { div, mul, add, sub };
    Oper lastOperator;
    enum ButtonNames { digit, division, times, minus, plus, equal, reset };
    ButtonNames lastClicked;
};

#endif // CALC_NEW_H
