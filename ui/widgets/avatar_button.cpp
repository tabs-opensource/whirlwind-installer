// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/widgets/avatar_button.h"

#include <QPainter>
#include <QPaintEvent>

#include "base/file_util.h"

namespace installer {

namespace {

const int kIconSize = 100;

}  // namespace

AvatarButton::AvatarButton(QWidget* parent) : AvatarButton("", parent) { }

AvatarButton::AvatarButton(const QString& icon, QWidget* parent)
    : FlatButton(parent),
      icon_(icon) {
  this->setObjectName("avatar_button");

  this->setFixedSize(kIconSize, kIconSize);
  this->setStyleSheet(ReadFile(":/styles/avatar_button.css"));
}

void AvatarButton::updateIcon(const QString& icon) {
  icon_ = icon;
  this->update();
}

void AvatarButton::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);

  const QRect ellipse_rect((width() - kIconSize) / 2, (height() - kIconSize) /2,
                           kIconSize, kIconSize);
  QPainterPath path;
  path.addEllipse(ellipse_rect);
  painter.setRenderHint(QPainter::Antialiasing);
  // Scale image.
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.setClipPath(path);

  const QImage image(icon_);
  painter.drawImage(ellipse_rect, image);

  painter.end();
}

}  // namespace installer