// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/widgets/simple_partition_button.h"

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include "base/file_util.h"
#include "ui/delegates/partition_util.h"
#include "ui/widgets/partition_usage_bar.h"

namespace installer {

namespace {

const int kButtonWidth = 220;
const int kButtonHeight = 220;
const int kOsIconWidth = 120;
const int kOsIconHeight = 120;

QString GetImageByOsType(OsType os_type) {
  switch (os_type) {
    case OsType::Empty: {
      return QStringLiteral(":/images/driver_128.png");
    }
    case OsType::Linux: {
      return QStringLiteral(":/images/driver_linux_128.png");
    }
    case OsType::Mac: {
      return QStringLiteral(":/images/driver_mac_128.png");
    }
    case OsType::Unknown: {
      return QStringLiteral(":/images/driver_128.png");
    }
    case OsType::Windows: {
      return QStringLiteral(":/images/driver_windows_128.png");
    }
    default: {
      return QString();
    }
  }
}

}  // namespace

SimplePartitionButton::SimplePartitionButton(const Partition& partition,
                                             QWidget* parent)
    : PointerButton(parent),
      partition_(partition) {
  this->setObjectName(QStringLiteral("simple_partition_button"));
  this->setFixedSize(kButtonWidth, kButtonHeight);
  this->setCheckable(true);
  this->initUI();
  this->initConnections();
}

void SimplePartitionButton::initConnections() {
  connect(this, &QPushButton::toggled,
          this, &SimplePartitionButton::onButtonToggled);
}

void SimplePartitionButton::initUI() {
  os_label_ = new QLabel();
  os_label_->setObjectName(QStringLiteral("fs_label"));
  os_label_->setFixedSize(kOsIconWidth, kOsIconHeight);
  const QPixmap os_icon(GetImageByOsType(partition_.os));
  os_label_->setPixmap(os_icon);

  QLabel* path_label = new QLabel();
  if (partition_.label.isEmpty()) {
    path_label->setText(partition_.path);
  } else {
    // TODO(xushaohua): trim text.
    path_label->setText(
        QString("%1(%2)").arg(partition_.label).arg(partition_.path));
  }
  path_label->setObjectName(QStringLiteral("path_label"));
  path_label->setAlignment(Qt::AlignCenter);

  QLabel* usage_label = new QLabel();
  usage_label->setText(
      GetPartitionUsage(partition_.freespace, partition_.length));
  usage_label->setObjectName(QStringLiteral("usage_label"));
  usage_label->setAlignment(Qt::AlignCenter);

  PartitionUsageBar* usage_bar =
      new PartitionUsageBar(partition_.freespace, partition_.length);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addStretch();
  layout->addWidget(os_label_, 0, Qt::AlignHCenter);
  layout->addWidget(path_label, 0, Qt::AlignHCenter);
  layout->addWidget(usage_label, 0, Qt::AlignHCenter);
  layout->addWidget(usage_bar, 0, Qt::AlignHCenter);
  layout->addStretch();

  this->setLayout(layout);

  this->setStyleSheet(
      ReadTextFileContent(":/styles/simple_partition_button.css"));
  this->setCheckable(true);
  this->setFixedSize(kButtonWidth, kButtonHeight);
}

void SimplePartitionButton::onButtonToggled() {
  if (this->isChecked()) {
    const QPixmap pixmap(":/images/driver_install_128.png");
    os_label_->setPixmap(pixmap);
  } else {
    QPixmap pixmap(GetImageByOsType(partition_.os));
    os_label_->setPixmap(pixmap);
  }
}

}  // namespace installer
