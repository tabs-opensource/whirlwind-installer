// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_PARTMAN_LIBPARTED_UTIL_H
#define INSTALLER_PARTMAN_LIBPARTED_UTIL_H

#include <parted/parted.h>
#include <QString>

#include "partman/partition.h"

namespace installer {

// Commit changes to disk.
bool Commit(PedDisk* lp_disk);

// Commit kernel udev event queue and wait for |dev_path| exists.
bool CommitUdevEvent(const QString& dev_path);

// Create a new partition defined in |partition|.
bool CreatePartition(const Partition& partition);

// Create new partition |table| at |device_path|.
bool CreatePartitionTable(const QString& device_path, PartitionTableType table);

// Delete partition defined in |partition| from device.
bool DeletePartition(const Partition& partition);

// Destroy libparted-device object.
void DestroyDevice(PedDevice* lp_device);

// Destroy libparted-device and disk object.
void DestroyDeviceAndDisk(PedDevice*& lp_device, PedDisk*& lp_disk);

// Flush linux kernel caches. Ensure coherency between the caches of the whole
// disk device and the partition devices.
bool FlushDevice(PedDevice* lp_device);

// Get libparted-device and disk object at |path|.
// Call |DestroyDeviceAndDisk()| to release them.
bool GetDeviceAndDisk(const QString& device_path,
                      PedDevice*& lp_device,
                      PedDisk*& lp_disk);

// Get |partition| path, might be empty.
QString GetPartitionPath(PedPartition* lp_partition);

// Resize/Move partition specified with |partition|.
// If |partition| is NormalPartition or LogicalPartition, remember to re-format
// it.
bool ResizeMovePartition(const Partition& partition);

// Set/unset |flag| of |partition|.
bool SetPartitionFlag(const Partition& partition,
                      PedPartitionFlag flag,
                      bool is_set);
// Set/unset flags of |partition|
bool SetPartitionFlags(const Partition& partition);

// Update partition type defined in |partition|.
bool SetPartitionType(const Partition& partition);

// Refers: http://stackoverflow.com/questions/14127210/
// After the kernel boots, `udevd` is used to create device nodes for
// all detected devices. That is a relatively time consuming task that
// has to be completed for the boot process to continue, otherwise
// there is a risk of services failing due to missing device nodes.
// `udevadm settle` waits for udevd to process the device creation events
// for all hardware devices, thus ensuring that any device nodes
// have been created successfully before proceeding.
void SettleDevice(int timeout);

// Update partition number and path based on start_sector and end_secotr in
// |partition|.
// This partition number and path is read from real device.
bool UpdatePartitionNumber(Partition& partition);

}  // namespace installer

#endif  // INSTALLER_PARTMAN_LIBPARTED_UTIL_H
