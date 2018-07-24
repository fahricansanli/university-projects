#include "calc_new.h"
#include "button.h"
#include <QtWidgets>
#include <iostream>

using namespace std;

calc_new::calc_new(QWidget *parent)
    : QWidget(parent)
{
    // instantiate variables
    error = false;
    lastOperator = add;
    lastClicked = reset;
    hexMode = false;
    sum = 0;
    base = 10;
    display_value = 0;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i) {
        QString name = QString::number(i);
        digitButtons[i] = createButton(name, SLOT(digitClicked()));
        digitButtons[i]->value = i;
    }

    for(int i = 0; i < HexDigitButtons; ++i) {
        QString name = QString(char(i+'A'));
        hexDigitButtons[i] = createButton(name, SLOT(hexDigitClicked()));
        hexDigitButtons[i]->value = 10 + i;
    }

    Button *clearAllButton = createButton(tr("Clr"), SLOT(clearAll()));
    Button *divisionButton = createButton(tr("/"), SLOT(divisionButtonClicked()));
    Button *timesButton = createButton(tr("*"), SLOT(timesButtonClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(minusButtonClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(plusButtonClicked()));
    Button *decButton = createButton(tr("Dec"), SLOT(decButtonClicked()));
    Button *hexButton = createButton(tr("Hex"), SLOT(hexButtonClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalButtonClicked()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 5);

    mainLayout->addWidget(clearAllButton, 2, 3);

    for (int i = 0; i < NumDigitButtons + HexDigitButtons; ++i) {
        int row = (3 + (i/4));
        int column = i%4;
        if(i < NumDigitButtons)
            mainLayout->addWidget(digitButtons[i], row, column);
        else
            mainLayout->addWidget(hexDigitButtons[i-10], row, column);
    }

    mainLayout->addWidget(hexButton, 1, 2);
    mainLayout->addWidget(decButton, 1, 3);

    mainLayout->addWidget(divisionButton, 1, 1);
    mainLayout->addWidget(timesButton, 1, 0);
    mainLayout->addWidget(minusButton, 2, 1);
    mainLayout->addWidget(plusButton, 2, 0);
    mainLayout->addWidget(equalButton, 2, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));

}

void calc_new::digitClicked() {
    if(error)
        return;

    Button *clickedButton = qobject_cast<Button *>(sender());

    if(lastClicked == equal) {
        clearAll();
    }

    // if last clicked button is not a digit
    if(lastClicked != digit) {
        display->setText("");
        display_value = clickedButton->value;
    }
    else
        display_value = display_value * base + clickedButton->value;

    display->setText(display->text() + clickedButton->text());

    lastClicked = digit;
}

void calc_new::hexDigitClicked() {
    if(!hexMode || error)
        return;

    if(lastClicked == equal) {
        clearAll();
    }

    Button *clickedButton = qobject_cast<Button *>(sender());

    // if last clicked button is not a digit
    if(lastClicked != digit) {
        display->setText("");
        display_value = clickedButton->value;
    }
    else
        display_value = display_value * base + clickedButton->value;

    display->setText(display->text() + clickedButton->text());

    lastClicked = digit;
}

void calc_new::clearAll() {

    base = (hexMode) ? 16 : 10;

    error = false;
    sum = 0;
    display_value = 0;
    display->setText("0");
    lastOperator = add;
    lastClicked = reset;
}

void calc_new::divisionButtonClicked() {
    if(error)
        return;

    if(lastClicked == digit) {
        handlePrevOperation();
    }
    lastOperator = div;
    lastClicked = division;
}

void calc_new::timesButtonClicked() {
    if(error)
        return;

    if(lastClicked == digit) {
        handlePrevOperation();
    }
    lastOperator = mul;
    lastClicked = times;
}

void calc_new::minusButtonClicked() {
    if(error)
        return;

    if(lastClicked == digit) {
        handlePrevOperation();
    }
    lastOperator = sub;
    lastClicked = minus;
}

void calc_new::plusButtonClicked() {
    if(error)
        return;

    if(lastClicked == digit) {
        handlePrevOperation();
    }
    lastOperator = add;
    lastClicked = plus;
}

void calc_new::equalButtonClicked() {
    if(error)
        return;

    if(lastClicked == digit) {
        handlePrevOperation();
    }
    lastClicked = equal;
}

void calc_new::handlePrevOperation() {

    switch(lastOperator) {
        case add:
            sum += display_value;
            break;
        case sub:
            sum -= display_value;
            break;
        case mul:
            sum *= display_value;
            break;
        case div:
            // division by zero
            if(display_value == 0) {
                display->setText("ERROR");
                error = true;
                return;
            }
            sum /= display_value;
            break;
    }

    display_value = sum;
    if(hexMode) {
        QString hexa;
        hexa.setNum(sum, 16);
        hexa = hexa.toUpper();
        display->setText(hexa);
    }
    else {
        display->setText(QString::number(sum));
    }
}

void calc_new::decButtonClicked() {
    // do nothing if calculator is in dec mode
    if(!hexMode)
        return;

    // turn hexMode off and clear all
    hexMode = false;
    clearAll();
}

void calc_new::hexButtonClicked() {
    // do nothing if calculator is in hex mode
    if(hexMode)
        return;

    // turn hexMode on and clear all
    hexMode = true;
    clearAll();
}

Button *calc_new::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

