// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/widgets/expanded_nav_button.h"

#include "base/file_util.h"

namespace ui {

ExpandedNavButton::ExpandedNavButton(const QString& text, QWidget* parent)
  : FlatButton(parent) {
  this->setObjectName(QStringLiteral("expanded_nav_button"));
  this->setText(text);
  this->setStyleSheet(
      base::ReadTextFileContent(":/styles/expanded_nav_button.css"));
}

}  // namespace ui