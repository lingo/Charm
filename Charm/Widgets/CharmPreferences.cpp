/*
  CharmPreferences.cpp

  This file is part of Charm, a task-based time tracking application.

  Copyright (C) 2014-2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

  Author: Frank Osterfeld <frank.osterfeld@kdab.com>
  Author: Mathias Hasselmann <mathias.hasselmann@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CharmPreferences.h"
#include "ApplicationCore.h"
#include "MessageBox.h"

#include "Core/Configuration.h"
#include "Idle/IdleDetector.h"
#include "Lotsofcake/Configuration.h"

#include <QCheckBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>

CharmPreferences::CharmPreferences(const Configuration &config, QWidget *parent_)
    : QDialog(parent_)
{
    m_ui.setupUi(this);
    const bool haveIdleDetection = ApplicationCore::instance().idleDetector()->available();
    const bool haveCommandInterface = (ApplicationCore::instance().commandInterface() != nullptr);

    m_ui.cbIdleDetection->setEnabled(haveIdleDetection);
    m_ui.lbIdleDetection->setEnabled(haveIdleDetection);
    m_ui.cbIdleDetection->setChecked(config.detectIdling && m_ui.cbIdleDetection->isEnabled());
    m_ui.cbRequestEventComment->setChecked(config.requestEventComment);
    m_ui.lbCommandInterface->setVisible(haveCommandInterface);
    m_ui.cbEnableCommandInterface->setEnabled(haveCommandInterface);
    m_ui.cbEnableCommandInterface->setVisible(haveCommandInterface);
    m_ui.cbEnableCommandInterface->setChecked(haveCommandInterface
                                              && config.enableCommandInterface);

    // this would not need a switch, but i hate casting enums to int:
    switch (config.timeTrackerFontSize) {
    case Configuration::TimeTrackerFont_Small:
        m_ui.cbTimeTrackerFontSize->setCurrentIndex(0);
        break;
    case Configuration::TimeTrackerFont_Regular:
        m_ui.cbTimeTrackerFontSize->setCurrentIndex(1);
        break;
    case Configuration::TimeTrackerFont_Large:
        m_ui.cbTimeTrackerFontSize->setCurrentIndex(2);
        break;
    }

    switch (config.durationFormat) {
    case Configuration::Minutes:
        m_ui.cbDurationFormat->setCurrentIndex(0);
        break;
    case Configuration::Decimal:
        m_ui.cbDurationFormat->setCurrentIndex(1);
        break;
    }

    switch (config.toolButtonStyle) {
    case Qt::ToolButtonIconOnly:
        m_ui.cbToolButtonStyle->setCurrentIndex(0);
        break;
    case Qt::ToolButtonTextOnly:
        m_ui.cbToolButtonStyle->setCurrentIndex(1);
        break;
    case Qt::ToolButtonTextUnderIcon:
        m_ui.cbToolButtonStyle->setCurrentIndex(2);
        break;
    case Qt::ToolButtonTextBesideIcon:
        m_ui.cbToolButtonStyle->setCurrentIndex(3);
        break;
    case Qt::ToolButtonFollowStyle:
        m_ui.cbToolButtonStyle->setCurrentIndex(4);
        break;
    }

    m_ui.sbNumberOfTaskSelectorEntries->setValue(config.numberOfTaskSelectorEntries);

    // resize( minimumSize() );
}

CharmPreferences::~CharmPreferences()
{
}

bool CharmPreferences::detectIdling() const
{
    return m_ui.cbIdleDetection->isChecked();
}

bool CharmPreferences::requestEventComment() const
{
    return m_ui.cbRequestEventComment->isChecked();
}

bool CharmPreferences::enableCommandInterface() const
{
    return m_ui.cbEnableCommandInterface->isChecked();
}

int CharmPreferences::numberOfTaskSelectorEntries() const
{
    return m_ui.sbNumberOfTaskSelectorEntries->value();
}

Configuration::DurationFormat CharmPreferences::durationFormat() const
{
    switch (m_ui.cbDurationFormat->currentIndex()) {
    case 0:
        return Configuration::Minutes;
    case 1:
        return Configuration::Decimal;
    default:
        Q_ASSERT(!"Unexpected combobox item for DurationFormat");
    }
    return Configuration::Minutes;
}

Configuration::TimeTrackerFontSize CharmPreferences::timeTrackerFontSize() const
{
    switch (m_ui.cbTimeTrackerFontSize->currentIndex()) {
    case 0:
        return Configuration::TimeTrackerFont_Small;
        break;
    case 1:
        return Configuration::TimeTrackerFont_Regular;
        break;
    case 2:
        return Configuration::TimeTrackerFont_Large;
        break;
    default:
        Q_ASSERT(false);   // somebody added an item
    }
    // always return something, to avoid compiler warning:
    return Configuration::TimeTrackerFont_Regular;
}

const QString & CharmPreferences::timeTrackerFont() const
{
    return m_ui.edTimeTrackerFont->text();
}

const QString & CharmPreferences::eventWindowFont() const
{
    return m_ui.edEventWindowFont->text();
}

Qt::ToolButtonStyle CharmPreferences::toolButtonStyle() const
{
    switch (m_ui.cbToolButtonStyle->currentIndex()) {
    case 0:
        return Qt::ToolButtonIconOnly;
        break;
    case 1:
        return Qt::ToolButtonTextOnly;
        break;
    case 2:
        return Qt::ToolButtonTextUnderIcon;
        break;
    case 3:
        return Qt::ToolButtonTextBesideIcon;
        break;
    case 4:
        return Qt::ToolButtonFollowStyle;
        break;
    default:
        Q_ASSERT(false);   // somebody added an item
    }
    // always return something, to avoid compiler warning:
    return Qt::ToolButtonIconOnly;
}

