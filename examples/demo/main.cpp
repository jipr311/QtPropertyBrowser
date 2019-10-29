/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of a Qt Solutions component.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#include <QApplication>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QMap>
#include <QDebug>

#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget* mainWidget = new QWidget();
    mainWidget->setWindowTitle("mini demo");

    QtBoolPropertyManager* boolManager = new QtBoolPropertyManager(mainWidget);
    QtIntPropertyManager* intManager = new QtIntPropertyManager(mainWidget);
    QtStringPropertyManager* stringManager = new QtStringPropertyManager(mainWidget);
    QtSizePropertyManager* sizeManager = new QtSizePropertyManager(mainWidget);
    QtRectPropertyManager* rectManager = new QtRectPropertyManager(mainWidget);
    QtSizePolicyPropertyManager* sizePolicyManager = new QtSizePolicyPropertyManager(mainWidget);
    QtEnumPropertyManager* enumManager = new QtEnumPropertyManager(mainWidget);
    QtGroupPropertyManager* groupManager = new QtGroupPropertyManager(mainWidget);

    // BEGIN keys
    QtProperty* item0 = groupManager->addProperty("QObject");
    QtProperty* item1 = stringManager->addProperty("1-objectName");
    item0->addSubProperty(item1);
    QtProperty* item2 = boolManager->addProperty("2-enabled");
    item0->addSubProperty(item2);
    QtProperty* item3 = rectManager->addProperty("3-geometry");
    item0->addSubProperty(item3);
    QtProperty* item4 = sizePolicyManager->addProperty("4-sizePolicy");
    item0->addSubProperty(item4);
    QtProperty* item5 = sizeManager->addProperty("5-sizeIncrement");
    item0->addSubProperty(item5);
    QtProperty* item6 = boolManager->addProperty("6-mouseTracking");
    item0->addSubProperty(item6);
    QtProperty* item7 = enumManager->addProperty("7-laser driver");
    // END keys

    QStringList enumNames;
    enumNames << "Sick" << "pepper&fuchs" << "Onrom" << "Left";
    enumManager->setEnumNames(item7, enumNames);
    QMap<int, QIcon> enumIcons;
    enumIcons[0] = QIcon(":/demo/images/up.png");
    enumIcons[1] = QIcon(":/demo/images/right.png");
    enumIcons[2] = QIcon(":/demo/images/down.png");
    enumIcons[3] = QIcon(":/demo/images/left.png");
    enumManager->setEnumIcons(item7, enumIcons);
    item0->addSubProperty(item7);

    QtProperty* item8 = intManager->addProperty("8-valueii");
    intManager->setRange(item8, -100, 100);
    item0->addSubProperty(item8);

    QtCheckBoxFactory* checkBoxFactory = new QtCheckBoxFactory(mainWidget);
    QtSpinBoxFactory* spinBoxFactory = new QtSpinBoxFactory(mainWidget);
    QtLineEditFactory* lineEditFactory = new QtLineEditFactory(mainWidget);
    QtEnumEditorFactory* comboBoxFactory = new QtEnumEditorFactory(mainWidget);

    QtAbstractPropertyBrowser* editor1 = new QtTreePropertyBrowser();
    editor1->setFactoryForManager(boolManager, checkBoxFactory);
    editor1->setFactoryForManager(intManager, spinBoxFactory);
    editor1->setFactoryForManager(stringManager, lineEditFactory);
    editor1->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    editor1->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    editor1->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    editor1->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    editor1->setFactoryForManager(enumManager, comboBoxFactory);

    editor1->addProperty(item0);

    QGridLayout* layout = new QGridLayout(mainWidget);
    QPushButton* b = new QPushButton("!", mainWidget);
    QObject::connect(b, &QPushButton::pressed, []()
    {
        qDebug() << "on Click!!";
    });

    layout->addWidget(editor1, 0, 0);
    layout->addWidget(b, 1, 0);

    mainWidget->show();

    int ret = app.exec();
    delete mainWidget;
    return ret;
}
